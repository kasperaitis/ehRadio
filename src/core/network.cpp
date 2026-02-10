#include "options.h"
#include <ESPmDNS.h>
#include "time.h"
#include "rtcsupport.h"
#include "network.h"
#include "display.h"
#include "config.h"
#include "telnet.h"
#include "netserver.h"
#include "player.h"
#include "mqtt.h"
#include "../pluginsManager/pluginsManager.h"
#include <DNSServer.h>
#include "../displays/tools/l10n.h"
#include <ImprovWiFiLibrary.h>

#ifndef WIFI_ATTEMPTS
  #define WIFI_ATTEMPTS  16
#endif

MyNetwork network;

TaskHandle_t syncTaskHandle;
TaskHandle_t streamRetryTaskHandle = NULL;

bool getWeather(char *wstr);
void doSync(void * pvParameters);
void retryStreamConnection(void * pvParameters);
static bool onImprovCustomConnect(const char* ssid, const char* password);

void ticks() {
  if(!display.ready()) return; //waiting for SD is ready
  pm.on_ticker();
  static const uint16_t weatherSyncInterval=1800;
  //static const uint16_t weatherSyncIntervalFail=10;
#if RTCSUPPORTED
  static const uint32_t timeSyncInterval=86400;
  static uint32_t timeSyncTicks = 0;
#else
  static const uint16_t timeSyncInterval=3600;
  static uint16_t timeSyncTicks = 0;
#endif
  static uint16_t weatherSyncTicks = 0;
  static bool divrssi;
  timeSyncTicks++;
  weatherSyncTicks++;
  divrssi = !divrssi;
  if(network.status == CONNECTED){
    if(network.forceTimeSync || network.forceWeather){
      xTaskCreatePinnedToCore(doSync, "doSync", 1024 * 4, NULL, 0, &syncTaskHandle, 0);
    }
    // check at :01s mark (fix network clock not matching system clock after Daylight Savings Time changes)
    if (network.timeinfo.tm_sec == 1) {
      time_t now = time(NULL);
      struct tm localNow;
      localtime_r(&now, &localNow);
      if ((network.timeinfo.tm_min != localNow.tm_min) || (network.timeinfo.tm_hour != localNow.tm_hour)) {
        timeSyncTicks = 0;
        network.forceTimeSync = true;
      }
    }
    if(timeSyncTicks >= timeSyncInterval){
      timeSyncTicks=0;
      network.forceTimeSync = true;
    }
    if(weatherSyncTicks >= weatherSyncInterval){
      weatherSyncTicks=0;
      network.forceWeather = true;
    }
  }
#ifndef DSP_LCD
  if(config.store.screensaverEnabled && display.mode()==PLAYER && !player.isRunning()){
    config.screensaverTicks++;
    if(config.screensaverTicks > config.store.screensaverTimeout+SCREENSAVERSTARTUPDELAY){
      if(config.store.screensaverBlank){
        display.putRequest(NEWMODE, SCREENBLANK);
      }else{
        display.putRequest(NEWMODE, SCREENSAVER);
      }
    }
  }
  if(config.store.screensaverPlayingEnabled && display.mode()==PLAYER && player.isRunning()){
    config.screensaverPlayingTicks++;
    if(config.screensaverPlayingTicks > config.store.screensaverPlayingTimeout*60+SCREENSAVERSTARTUPDELAY){
      if(config.store.screensaverPlayingBlank){
        display.putRequest(NEWMODE, SCREENBLANK);
      }else{
        display.putRequest(NEWMODE, SCREENSAVER);
      }
    }
  }
#endif
#if RTCSUPPORTED
  if(config.isRTCFound()){
    rtc.getTime(&network.timeinfo);
    mktime(&network.timeinfo);
    display.putRequest(CLOCK);
  }
#else
  if(network.timeinfo.tm_year>100 || network.status == SDREADY) {
    network.timeinfo.tm_sec++;
    mktime(&network.timeinfo);
    display.putRequest(CLOCK);
  }
#endif
  if(player.isRunning() && config.getMode()==PM_SDCARD) netserver.requestOnChange(SDPOS, 0);
  if(divrssi) {
    if(network.status == CONNECTED){
      netserver.setRSSI(WiFi.RSSI());
      netserver.requestOnChange(NRSSI, 0);
      display.putRequest(DSPRSSI, netserver.getRSSI());
    }
#ifdef USE_SD
    if(display.mode()!=SDCHANGE) player.sendCommand({PR_CHECKSD, 0});
#endif
    player.sendCommand({PR_VUTONUS, 0});
  }
}

void retryStreamConnection(void * pvParameters) {
  const uint8_t maxAttempts = 40;  // 40 attempts * 15 seconds = 10 minutes
  uint8_t attemptCount = 0;
  while (attemptCount < maxAttempts) {
    delay(15000);  // Wait 15 seconds between attempts
    // Check if we should still be retrying
    if (network.lostPlaying && WiFi.status() == WL_CONNECTED && !player.isRunning()) {
      attemptCount++;
      Serial.printf("Stream reconnect attempt %d/%d\n", attemptCount, maxAttempts);
      player.sendCommand({PR_PLAY, config.lastStation()});
      delay(3000);  // Give it a moment to try connecting
      // Check if it worked
      if (player.isRunning()) {
        Serial.println("Stream reconnected successfully!");
        network.lostPlaying = false;
        streamRetryTaskHandle = NULL;
        vTaskDelete(NULL);
        return;
      }
    } else {
      // Conditions changed (user pressed stop, or already playing, or WiFi lost again)
      if (!network.lostPlaying || player.isRunning()) {
        network.lostPlaying = false;
      }
      streamRetryTaskHandle = NULL;
      vTaskDelete(NULL);
      return;
    }
  }
  // Max attempts reached - give up
  Serial.println("Stream reconnection failed after 10 minutes. User intervention required.");
  network.lostPlaying = false;
  streamRetryTaskHandle = NULL;
  vTaskDelete(NULL);
}

void MyNetwork::WiFiReconnected(WiFiEvent_t event, WiFiEventInfo_t info){
  network.beginReconnect = false;
  player.lockOutput = false;
  delay(100);
  display.putRequest(NEWMODE, PLAYER);
  if(config.getMode()==PM_SDCARD) {
    network.status=CONNECTED;
    display.putRequest(NEWIP, 0);
  }else{
    display.putRequest(NEWMODE, PLAYER);
    if (network.lostPlaying) {
      player.sendCommand({PR_PLAY, config.lastStation()});
      // Launch retry task if not already running
      if (streamRetryTaskHandle == NULL) {
        xTaskCreatePinnedToCore(retryStreamConnection, "streamRetry", 1024 * 4, NULL, 1, &streamRetryTaskHandle, 0);
      }
    }
  }
  #ifdef MQTT_ENABLE
    if (config.store.mqttenable) connectToMqtt();
  #endif
}

void MyNetwork::WiFiLostConnection(WiFiEvent_t event, WiFiEventInfo_t info){
  if(!network.beginReconnect){
    Serial.printf("WiFiLost: %lu ms, event=%d, SSID=%s, RSSI=%d\n", millis(), (int)event, config.ssids[config.store.lastSSID-1].ssid, WiFi.RSSI());
    if(config.getMode()==PM_SDCARD) {
      network.status=SDREADY;
      display.putRequest(NEWIP, 0);
    }else{
      network.lostPlaying = player.isRunning();
      if (network.lostPlaying) { player.lockOutput = true; player.sendCommand({PR_STOP, 0}); }
      display.putRequest(NEWMODE, LOST);
    }
  }
  network.beginReconnect = true;
  WiFi.reconnect();
}

bool MyNetwork::wifiBegin(bool silent){
  uint8_t ls = (config.store.lastSSID == 0 || config.store.lastSSID > config.ssidsCount) ? 0 : config.store.lastSSID - 1;
  uint8_t startedls = ls;
  uint8_t errcnt = 0;
  WiFi.mode(WIFI_STA);
  struct MatchedNetwork {
    uint8_t configIndex;
    int scanIndex;
    int32_t rssi;
    uint8_t channel;
    uint8_t bssid[6];
  };
  MatchedNetwork matches[20];  // Max 20 matches (reasonable limit)
  int matchCount = 0;
  if (config.store.wifiscanbest && !silent) BOOTLOG("Scanning for best available network...");
  int n = WiFi.scanNetworks();

  if (config.store.wifiscanbest) {
    if (!silent) BOOTLOG("Scan complete: %d networks found", n);
    if (n > 0) {
      // Find all matching networks and build sorted list
      for (int i = 0; i < n; i++) {
        String scannedSSID = WiFi.SSID(i);
        if (scannedSSID.length() == 0) continue;
        for (uint8_t j = 0; j < config.ssidsCount; j++) {
          if (strcmp(scannedSSID.c_str(), config.ssids[j].ssid) == 0) {
            // Found a match - add to array if there's space
            if (matchCount < 20) {
              matches[matchCount].configIndex = j;
              matches[matchCount].scanIndex = i;
              matches[matchCount].rssi = WiFi.RSSI(i);
              matches[matchCount].channel = WiFi.channel(i);
              uint8_t* bssid = WiFi.BSSID(i);
              memcpy(matches[matchCount].bssid, bssid, 6);
              matchCount++;
            }
            break;
          }
        }
      }
      // Sort matches by RSSI (strongest first) using bubble sort
      for (int i = 0; i < matchCount - 1; i++) {
        for (int j = 0; j < matchCount - i - 1; j++) {
          if (matches[j].rssi < matches[j + 1].rssi) {
            MatchedNetwork temp = matches[j];
            matches[j] = matches[j + 1];
            matches[j + 1] = temp;
          }
        }
      }
      // Log all matches
      if (!silent && matchCount > 0) {
        BOOTLOG("Available networks from your saved list (sorted by strength):");
        for (int i = 0; i < matchCount; i++) {
          BOOTLOG("  %d. %s | MAC: %02X:%02X:%02X:%02X:%02X:%02X | RSSI: %d dBm | Ch: %d", 
                  i+1, config.ssids[matches[i].configIndex].ssid,
                  matches[i].bssid[0], matches[i].bssid[1], matches[i].bssid[2],
                  matches[i].bssid[3], matches[i].bssid[4], matches[i].bssid[5],
                  matches[i].rssi, matches[i].channel);
        }
      }
    }
    // Try each matched network in RSSI order
    for (int attempt = 0; attempt < matchCount; attempt++) {
      uint8_t configIdx = matches[attempt].configIndex;
      if (!silent) {
        BOOTLOG("Attempt %d: connecting to %s | MAC: %02X:%02X:%02X:%02X:%02X:%02X (RSSI: %d dBm)", 
                attempt + 1, config.ssids[configIdx].ssid,
                matches[attempt].bssid[0], matches[attempt].bssid[1], matches[attempt].bssid[2],
                matches[attempt].bssid[3], matches[attempt].bssid[4], matches[attempt].bssid[5],
                matches[attempt].rssi);
        Serial.print("##[BOOT]#\t");
        display.putRequest(BOOTSTRING, configIdx);
      }
      WiFi.begin(config.ssids[configIdx].ssid, config.ssids[configIdx].password, 
                 matches[attempt].channel, matches[attempt].bssid); // Connect to specific AP by BSSID
      errcnt = 0;
      while (WiFi.status() != WL_CONNECTED) {
        if (!silent) Serial.print(".");
        delay(500);
        if (REAL_LEDBUILTIN!=255 && !silent) digitalWrite(REAL_LEDBUILTIN, !digitalRead(REAL_LEDBUILTIN));
        errcnt++;
        if (errcnt > WIFI_ATTEMPTS) {
          if(!silent) Serial.println();
          break;  // Failed, try next match
        }
      }
      if (WiFi.status() == WL_CONNECTED) {
        WiFi.scanDelete();
        config.setLastSSID(configIdx + 1);
        return true;
      }
    }

    // All scanned matches failed, clean up
    WiFi.scanDelete();
    if (!silent) BOOTLOG("All scanned networks failed, falling back to sequential try");
    ls = startedls;
  }
  
  // Fallback: try all configured SSIDs sequentially (original behavior)
  while (true) {
    if (!silent) {
      BOOTLOG("Attempt to connect to %s", config.ssids[ls].ssid);
      Serial.print("##[BOOT]#\t");
      display.putRequest(BOOTSTRING, ls);
    }
    WiFi.begin(config.ssids[ls].ssid, config.ssids[ls].password);
    
    while (WiFi.status() != WL_CONNECTED) {
      if (!silent) Serial.print(".");
      delay(500);
      if (REAL_LEDBUILTIN!=255 && !silent) digitalWrite(REAL_LEDBUILTIN, !digitalRead(REAL_LEDBUILTIN));
      errcnt++;
      if (errcnt > WIFI_ATTEMPTS) {
        errcnt = 0;
        ls++;
        if (ls > config.ssidsCount - 1) ls = 0;
        if(!silent) Serial.println();
        break;
      }
    }
    if (WiFi.status() != WL_CONNECTED && ls == startedls) {
      return false; break;
    }
    if (WiFi.status() == WL_CONNECTED) {
      config.setLastSSID(ls + 1);
      return true; break;
    }
  }
  return false;
}

void searchWiFi(void * pvParameters){
  if(!network.wifiBegin(true)){
    delay(10000);
    xTaskCreatePinnedToCore(searchWiFi, "searchWiFi", 1024 * 4, NULL, 0, NULL, 0);
  }else{
    network.status = CONNECTED;
    netserver.begin(true);
    telnet.begin(true);
    network.setWifiParams();
    display.putRequest(NEWIP, 0);
  }
  vTaskDelete( NULL );
}

#define DBGAP false

void MyNetwork::begin() {
  BOOTLOG("network.begin");
  
  // Initialize Improv early if not already done, so it's always available via Serial
  if (!improv) {
    improv = new ImprovWiFi(&Serial);
#if defined(CONFIG_IDF_TARGET_ESP32S3)
    ImprovTypes::ChipFamily chip = ImprovTypes::ChipFamily::CF_ESP32_S3;
#elif defined(CONFIG_IDF_TARGET_ESP32C3)
    ImprovTypes::ChipFamily chip = ImprovTypes::ChipFamily::CF_ESP32_C3;
#else
    ImprovTypes::ChipFamily chip = ImprovTypes::ChipFamily::CF_ESP32;
#endif
    char deviceUrl[64];
    strlcpy(deviceUrl, "http://{LOCAL_IPV4}/", sizeof(deviceUrl));
    improv->setDeviceInfo(chip, "ehRadio", RADIOVERSION, "ehRadio", deviceUrl);
    improv->setCustomConnectWiFi(onImprovCustomConnect);
  }

  config.initNetwork();
  ctimer.detach();
  if (config.ssidsCount == 0 || DBGAP) {
    raiseSoftAP();
    return;
  }
  if(config.getMode()!=PM_SDCARD){
    if(!wifiBegin()){
      raiseSoftAP();
      Serial.println("##[BOOT]#\tdone");
      return;
    }
    Serial.println(".");
    status = CONNECTED;
    setWifiParams();
  }else{
    status = SDREADY;
    xTaskCreatePinnedToCore(searchWiFi, "searchWiFi", 1024 * 4, NULL, 0, NULL, 0);
  }
  
  Serial.println("##[BOOT]#\tdone");
  if(REAL_LEDBUILTIN!=255) digitalWrite(REAL_LEDBUILTIN, LOW);
  
#if RTCSUPPORTED
  if(config.isRTCFound()){
    rtc.getTime(&network.timeinfo);
    mktime(&network.timeinfo);
    display.putRequest(CLOCK);
  }
#endif
  ctimer.attach(1, ticks);
  if (network_on_connect) network_on_connect();
  pm.on_connect();
}

void MyNetwork::loopImprov() {
  if (!improv) return;
  improv->handleSerial();
  
  unsigned long now = millis();
  if (now - lastImprovBroadcast > 2000) {
    lastImprovBroadcast = now;
    // Send state 0x02 (Authorized/Ready) when in SoftAP
    uint8_t heartbeat[] = {'I', 'M', 'P', 'R', 'O', 'V', 0x01, 0x01, 0x01, 0x02, 0x00};
    uint8_t checksum = 0;
    for (int i = 0; i < 10; i++) checksum += heartbeat[i];
    heartbeat[10] = checksum;
    Serial.write(heartbeat, sizeof(heartbeat));
  }
}

static Ticker improvRebootTicker;

static void triggerImprovReboot() {
  ESP.restart();
}

static bool onImprovCustomConnect(const char* ssid, const char* password) {
  // Try to connect briefly to verify if credentials work before saving
  WiFi.begin(ssid, password);
  unsigned long start = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - start < 10000) {
    delay(100);
    network.loopImprov();
  }

  if (WiFi.status() != WL_CONNECTED) {
    // Revert to AP if we were in AP mode, or just return false to signal error to browser
    // This will notify the user in the browser that connection failed
    return false;
  }

  // CONNECTION SUCCESSFUL - Proceed with saving logic
  
  // Check if this SSID already exists in our list
  int slot = -1;
  for (int i = 0; i < config.ssidsCount; i++) {
    if (strcmp(config.ssids[i].ssid, ssid) == 0) {
      slot = i;
      break;
    }
  }
  
  // If not found, use next available slot
  if (slot == -1) {
    slot = (config.ssidsCount < 5) ? config.ssidsCount : 4;
    if (slot == config.ssidsCount && config.ssidsCount < 5) {
      config.ssidsCount++;
    }
  }
  
  strlcpy(config.ssids[slot].ssid, ssid, sizeof(config.ssids[slot].ssid));
  strlcpy(config.ssids[slot].password, password, sizeof(config.ssids[slot].password));
  config.setLastSSID(slot + 1);

  // Update the URL immediately before returning success to browser
  IPAddress ip = WiFi.localIP();
  char deviceUrl[64];
  snprintf(deviceUrl, sizeof(deviceUrl), "http://%d.%d.%d.%d/", ip[0], ip[1], ip[2], ip[3]);
#if defined(CONFIG_IDF_TARGET_ESP32S3)
  ImprovTypes::ChipFamily chip = ImprovTypes::ChipFamily::CF_ESP32_S3;
#elif defined(CONFIG_IDF_TARGET_ESP32C3)
  ImprovTypes::ChipFamily chip = ImprovTypes::ChipFamily::CF_ESP32_C3;
#else
  ImprovTypes::ChipFamily chip = ImprovTypes::ChipFamily::CF_ESP32;
#endif
  if (network.improv) network.improv->setDeviceInfo(chip, "ehRadio", RADIOVERSION, "ehRadio", deviceUrl);
  
  // Save to SPIFFS temporary file
  File wifiFile = SPIFFS.open(TMP_PATH, "w");
  if (wifiFile) {
    for (int i = 0; i < config.ssidsCount; i++) {
      if (strlen(config.ssids[i].ssid) > 0) {
        wifiFile.printf("%s\t%s\n", config.ssids[i].ssid, config.ssids[i].password);
      }
    }
    wifiFile.close();
    
    // Finalize the save: Rename TMP to SSIDS_PATH
    if (SPIFFS.exists(TMP_PATH)) {
       SPIFFS.remove(SSIDS_PATH);
       if (SPIFFS.rename(TMP_PATH, SSIDS_PATH)) {
         improvRebootTicker.once(3, triggerImprovReboot);
         return true;
       }
    }
  }
  return false;
}

void MyNetwork::setWifiParams(){
  WiFi.setSleep(false);
  WiFi.onEvent(WiFiReconnected, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_GOT_IP);
  WiFi.onEvent(WiFiLostConnection, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_DISCONNECTED);
  weatherBuf=NULL;
  trueWeather = false;
  #if (DSP_MODEL!=DSP_DUMMY || defined(USE_NEXTION)) && !defined(HIDE_WEATHER)
    weatherBuf = (char *) malloc(sizeof(char) * WEATHER_STRING_L);
    memset(weatherBuf, 0, WEATHER_STRING_L);
  #endif
  if(strlen(config.store.sntp1)>0 && strlen(config.store.sntp2)>0){
    configTzTime(config.store.tzposix, config.store.sntp1, config.store.sntp2);
  }else if(strlen(config.store.sntp1)>0){
    configTzTime(config.store.tzposix, config.store.sntp1);
  }
}

void MyNetwork::requestTimeSync(bool withTelnetOutput, uint8_t clientId) {
  if (withTelnetOutput) {
    if (strlen(config.store.sntp1) > 0 && strlen(config.store.sntp2) > 0)
      configTzTime(config.store.tzposix, config.store.sntp1, config.store.sntp2);
    else if (strlen(config.store.sntp1) > 0)
      configTzTime(config.store.tzposix, config.store.sntp1);
    char timeStringBuff[50];
    strftime(timeStringBuff, sizeof(timeStringBuff), "%Y-%m-%dT%H:%M:%S", &timeinfo);
    telnet.printf(clientId, "##SYS.DATE#: %s (%s)\r\n> ", timeStringBuff, config.store.tzposix);
    telnet.printf(clientId, "##SYS.TZNAME#: %s\r\n> ", config.store.tz_name);
    telnet.printf(clientId, "##SYS.TZPOSIX#: %s\r\n> ", config.store.tzposix);
  }
}

void rebootTime() {
  ESP.restart();
}

void MyNetwork::raiseSoftAP() {
  WiFi.mode(WIFI_AP);
  #ifdef AP_PASSWORD
    WiFi.softAP(AP_SSID, AP_PASSWORD);
  #else
    WiFi.softAP(AP_SSID);
  #endif
  dnsServer = new DNSServer();
  dnsServer->start(53, "*", WiFi.softAPIP());
  Serial.println("##[BOOT]#");
  BOOTLOG("************************************************");
  BOOTLOG("Running in AP mode");
  #ifdef AP_PASSWORD
    BOOTLOG("Connect to AP %s with password %s", AP_SSID, AP_PASSWORD);
  #else
    BOOTLOG("Connect to AP %s with no password", AP_SSID);
  #endif
  BOOTLOG("and go to http://192.168.4.1/ to configure");
  BOOTLOG("Improv WiFi provisioning available via serial");
  BOOTLOG("************************************************");
  
  status = SOFT_AP;
  if(config.store.softapdelay>0)
    rtimer.once(config.store.softapdelay*60, rebootTime);
}

void MyNetwork::requestWeatherSync(){
  display.putRequest(NEWWEATHER);
}


void doSync( void * pvParameters ) {
  static uint8_t tsFailCnt = 0;
  //static uint8_t wsFailCnt = 0;
  if(network.forceTimeSync){
    network.forceTimeSync = false;
    if(getLocalTime(&network.timeinfo)){
      tsFailCnt = 0;
      network.forceTimeSync = false;
      mktime(&network.timeinfo);
      display.putRequest(CLOCK);
      network.requestTimeSync(true);
      #if RTCSUPPORTED
        if (config.isRTCFound()) rtc.setTime(&network.timeinfo);
      #endif
    }else{
      if(tsFailCnt<4){
        network.forceTimeSync = true;
        tsFailCnt++;
      }else{
        network.forceTimeSync = false;
        tsFailCnt=0;
      }
    }
  }
  if(network.weatherBuf && (strlen(config.store.weatherkey)!=0 && config.store.showweather) && network.forceWeather){
    network.forceWeather = false;
    network.trueWeather=getWeather(network.weatherBuf);
  }
  vTaskDelete( NULL );
}

bool getWeather(char *wstr) {
#if (DSP_MODEL!=DSP_DUMMY || defined(USE_NEXTION)) && !defined(HIDE_WEATHER)
  WiFiClient client;
  const char* host  = "api.openweathermap.org";
  
  if (!client.connect(host, 80)) {
    Serial.println("##WEATHER###: connection  failed");
    return false;
  }
  char httpget[250] = {0};
  sprintf(httpget, "GET /data/2.5/weather?lat=%s&lon=%s&units=%s&lang=%s&appid=%s HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n", config.store.weatherlat, config.store.weatherlon, LANG::weatherUnits, LANG::weatherLang, config.store.weatherkey, host);
  client.print(httpget);
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 2000UL) {
      Serial.println("##WEATHER###: client available timeout !");
      client.stop();
      return false;
    }
  }
  timeout = millis();
  String line = "";
  if (client.connected()) {
    while (client.available())
    {
      line = client.readStringUntil('\n');
      if (strstr(line.c_str(), "\"temp\"") != NULL) {
        client.stop();
        break;
      }
      if ((millis() - timeout) > 500)
      {
        client.stop();
        Serial.println("##WEATHER###: client read timeout !");
        return false;
      }
    }
  }
  if (strstr(line.c_str(), "\"temp\"") == NULL) {
    Serial.println("##WEATHER###: weather not found !");
    return false;
  }
  char *tmpe;
  char *tmps;
  char *tmpc;
  const char* cursor = line.c_str();
  char desc[120], temp[20], hum[20], press[20], icon[5];

  tmps = strstr(cursor, "\"description\":\"");
  if (tmps == NULL) { Serial.println("##WEATHER###: description not found !"); return false;}
  tmps += 15;
  tmpe = strstr(tmps, "\",\"");
  if (tmpe == NULL) { Serial.println("##WEATHER###: description not found !"); return false;}
  strlcpy(desc, tmps, tmpe - tmps + 1);
  cursor = tmpe + 2;
  
  // "ясно","icon":"01d"}],
  tmps = strstr(cursor, "\"icon\":\"");
  if (tmps == NULL) { Serial.println("##WEATHER###: icon not found !"); return false;}
  tmps += 8;
  tmpe = strstr(tmps, "\"}");
  if (tmpe == NULL) { Serial.println("##WEATHER###: icon not found !"); return false;}
  strlcpy(icon, tmps, tmpe - tmps + 1);
  cursor = tmpe + 2;
  
  tmps = strstr(cursor, "\"temp\":");
  if (tmps == NULL) { Serial.println("##WEATHER###: temp not found !"); return false;}
  tmps += 7;
  tmpe = strstr(tmps, ",\"");
  if (tmpe == NULL) { Serial.println("##WEATHER###: temp not found !"); return false;}
  strlcpy(temp, tmps, tmpe - tmps + 1);
  cursor = tmpe + 1;
  float tempf = atof(temp);

  tmps = strstr(cursor, "\"feels_like\":");
  if (tmps == NULL) { Serial.println("##WEATHER###: feels_like not found !"); return false;}
  tmps += 13;
  tmpe = strstr(tmps, ",\"");
  if (tmpe == NULL) { Serial.println("##WEATHER###: feels_like not found !"); return false;}
  strlcpy(temp, tmps, tmpe - tmps + 1);
  cursor = tmpe + 2;
  float tempfl = atof(temp); (void)tempfl;

  tmps = strstr(cursor, "\"pressure\":");
  if (tmps == NULL) { Serial.println("##WEATHER###: pressure not found !"); return false;}
  tmps += 11;
  tmpe = strstr(tmps, ",\"");
  if (tmpe == NULL) { Serial.println("##WEATHER###: pressure not found !"); return false;}
  strlcpy(press, tmps, tmpe - tmps + 1);
  cursor = tmpe + 2;
  int pressi = (float)atoi(press) / 1.333;
  
  tmps = strstr(cursor, "humidity\":");
  if (tmps == NULL) { Serial.println("##WEATHER###: humidity not found !"); return false;}
  tmps += 10;
  tmpe = strstr(tmps, ",\"");
  tmpc = strstr(tmps, "}");
  if (tmpe == NULL) { Serial.println("##WEATHER###: humidity not found !"); return false;}
  strlcpy(hum, tmps, tmpe - tmps + (tmpc>tmpe?1:0));
  
  tmps = strstr(cursor, "\"grnd_level\":");
  bool grnd_level_pr = (tmps != NULL);
  if(grnd_level_pr){
    tmps += 13;
    tmpe = strstr(tmps, ",\"");
    if (tmpe == NULL) { Serial.println("##WEATHER###: grnd_level not found !"); return false;}
    strlcpy(press, tmps, tmpe - tmps + 1);
    cursor = tmpe + 2;
    pressi = (float)atoi(press) / 1.333;
  }
  
  tmps = strstr(cursor, "\"speed\":");
  if (tmps == NULL) { Serial.println("##WEATHER###: wind speed not found !"); return false;}
  tmps += 8;
  tmpe = strstr(tmps, ",\"");
  if (tmpe == NULL) { Serial.println("##WEATHER###: wind speed not found !"); return false;}
  strlcpy(temp, tmps, tmpe - tmps + 1);
  cursor = tmpe + 1;
  float wind_speed = atof(temp); (void)wind_speed;
  
  tmps = strstr(cursor, "\"deg\":");
  if (tmps == NULL) { Serial.println("##WEATHER###: wind deg not found !"); return false;}
  tmps += 6;
  tmpe = strstr(tmps, ",\"");
  if (tmpe == NULL) { Serial.println("##WEATHER###: wind deg not found !"); return false;}
  strlcpy(temp, tmps, tmpe - tmps + 1);
  cursor = tmpe + 1;
  int wind_deg = atof(temp)/22.5;
  if(wind_deg<0) wind_deg = 16+wind_deg;
  
  
  #ifdef USE_NEXTION
    nextion.putcmdf("press_txt.txt=\"%dmm\"", pressi);
    nextion.putcmdf("hum_txt.txt=\"%d%%\"", atoi(hum));
    char cmd[30];
    snprintf(cmd, sizeof(cmd)-1,"temp_txt.txt=\"%.1f\"", tempf);
    nextion.putcmd(cmd);
    int iconofset;
    if(strstr(icon,"01")!=NULL)      iconofset = 0;
    else if(strstr(icon,"02")!=NULL) iconofset = 1;
    else if(strstr(icon,"03")!=NULL) iconofset = 2;
    else if(strstr(icon,"04")!=NULL) iconofset = 3;
    else if(strstr(icon,"09")!=NULL) iconofset = 4;
    else if(strstr(icon,"10")!=NULL) iconofset = 5;
    else if(strstr(icon,"11")!=NULL) iconofset = 6;
    else if(strstr(icon,"13")!=NULL) iconofset = 7;
    else if(strstr(icon,"50")!=NULL) iconofset = 8;
    else                             iconofset = 9;
    nextion.putcmd("cond_img.pic", 50+iconofset);
    nextion.weatherVisible(1);
  #endif
  
  Serial.printf("##WEATHER###: description: %s, temp:%.1f C, pressure:%dmmHg, humidity:%s%%\n", desc, tempf, pressi, hum);
  #ifdef WEATHER_FMT_SHORT
  sprintf(wstr, LANG::weatherFmt, tempf, pressi, hum);
  #else
    #if EXT_WEATHER
      sprintf(wstr, LANG::weatherFmt, desc, tempf, tempfl, pressi, hum, wind_speed, LANG::wind[wind_deg]);
    #else
      sprintf(wstr, LANG::weatherFmt, desc, tempf, pressi, hum);
    #endif
  #endif
  network.requestWeatherSync();
  return true;
#endif // if (DSP_MODEL!=DSP_DUMMY || defined(USE_NEXTION)) && !defined(HIDE_WEATHER)
  return false;
}
