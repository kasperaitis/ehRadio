#include "options.h"
#include "config.h"

#include "display.h"
#include "player.h"
#include "network.h"
#include "netserver.h"
#include "controls.h"
#include "telnet.h"
#include "rtcsupport.h"
#include "../displays/tools/l10n.h"
#ifdef USE_SD
  #include "sdmanager.h"
#endif
#ifdef USE_NEXTION
  #include "../displays/nextion.h"
#endif
#include <cstddef>
#include <ESPFileUpdater.h>
#include <nvs_flash.h>
#if DSP_MODEL==DSP_DUMMY
  #define DUMMYDISPLAY
#endif


// List of required web asset files
static const char* wwwFiles[] = {"curated.js", "dragpl.js", "ir.js", "options.js", "playstation.js", "script.js", "search.js", "updform.js",
                                 "logo.svg", "icon.png", "rb_srvrs.json", "timezones.json",
                                 "style.css", "theme.css", "curated.html", "irrecord.html", "options.html", "search.html", "updform.html",
                                 "player.html"}; // keep main page at end
static const size_t wwwFilesCount = sizeof(wwwFiles) / sizeof(wwwFiles[0]);

// List of optional data files
static const char* dataFiles[] = {"playlist.csv", "wifi.csv"};
static const size_t dataFilesCount = sizeof(dataFiles) / sizeof(dataFiles[0]);

Config config;

bool wasUpdated(ESPFileUpdater::UpdateStatus status) { return status == ESPFileUpdater::UPDATED; }

void u8fix(char *src) {
  char last = src[strlen(src)-1]; 
  if ((uint8_t)last >= 0xC2) src[strlen(src)-1]='\0';
}

bool Config::_wwwFilesExist() {
  char fullpath[64];
  for (size_t i = 0; i < wwwFilesCount; i++) {
    sprintf(fullpath, "/www/%s", wwwFiles[i]);
    String gzPath = String(fullpath) + ".gz";
    bool plainExists = SPIFFS.exists(fullpath);
    bool gzExists = SPIFFS.exists(gzPath);
    if (gzExists && plainExists) SPIFFS.remove(fullpath);
    if (!plainExists && !gzExists) return false;
  }
  return true;
}

void Config::init() {
  loadPreferences();
  bootInfo();
  #if RTCSUPPORTED
    BOOTLOG("RTC begin(SDA=%d,SCL=%d)", RTC_SDA, RTC_SCL);
    if (rtc.init()) {
      BOOTLOG("done");
      _rtcFound = true;
    } else {
      BOOTLOG("[ERROR] - Couldn't find RTC");
    }
  #endif
  #if defined(SD_SPIPINS) || SD_HSPI
    #if !defined(SD_SPIPINS)
      SDSPI.begin();
    #else
      SDSPI.begin(SD_SPIPINS); // SCK, MISO, MOSI
    #endif
  #endif
  if (store.config_set != 4262) {
    setDefaults();
  }
  store.play_mode = store.play_mode & 0b11;
  if (store.play_mode>1) store.play_mode=PM_WEB;
  _initHW();
  if (!SPIFFS.begin(true)) {
    Serial.println("##[ERROR]#\tSPIFFS Mount Failed");
    return;
  }
  BOOTLOG("SPIFFS mounted");
  
  // Check version file and determine if files need updating
  const char* versionPath = "/data/ehradio.ver";
  String storedVersion = "";
  if (SPIFFS.exists(versionPath)) {
    File verFile = SPIFFS.open(versionPath, "r");
    if (verFile) {
      storedVersion = verFile.readStringUntil('\n');
      storedVersion.trim();
      verFile.close();
    }
  }
  // if version is correct or file doesn't exist (which may indiciate SPIFFS files installed via flash), check files
  if (storedVersion == String(RADIOVERSION)) {
    wwwFilesExist = _wwwFilesExist();
  } else if (!SPIFFS.exists(versionPath)) {
    BOOTLOG("New install detected.");
    wwwFilesExist = _wwwFilesExist();
  } else {
    BOOTLOG("Version mismatch detected (stored: %s, current: %s)", storedVersion.c_str(), RADIOVERSION);
    wwwFilesExist =  false;
  }
  // if version is incorrect or version file doesn't exist, need to clean SPIFFS and make the version file
  if (!wwwFilesExist || !SPIFFS.exists(versionPath)) {
    purgeUnwantedFiles();
    File verFile = SPIFFS.open(versionPath, "w");
    if (verFile) {
        verFile.println(RADIOVERSION);
        verFile.close();
        BOOTLOG("Version file updated to %s", RADIOVERSION);
    }
  }
  if (!wwwFilesExist) {
    deleteMainwwwFile(); // Forces update process or (kind of) makes SPIFFS unusable
    #ifndef UPDATEURL
      BOOTLOG("SPIFFS is missing files!");
    #else
      BOOTLOG("SPIFFS is missing files.  Will attempt to get files from online...");
    #endif
  }

  #ifdef USE_SD
    _SDplaylistFS = getMode()==PM_SDCARD?&sdman:(true?&SPIFFS:_SDplaylistFS);
  #else
    _SDplaylistFS = &SPIFFS;
  #endif
}

void Config::loadPreferences() {
  prefs.begin("ehradio", false);
  // Check config_set first
  uint16_t configSetValue = 0;
  size_t configSetRead = prefs.getBytes("cfgset", &configSetValue, sizeof(configSetValue));
  if (configSetRead != sizeof(configSetValue)) {
    // Preferences is empty, save config_set and version
    Serial.println("[Prefs] Empty NVS detected, initializing config_set...\n");
    saveValue(&store.config_set, store.config_set);
  } else if (configSetValue != 4262) {
    // config_set present but not valid, reset config
    Serial.printf("[Prefs] Invalid config_set (%u), resetting config...\n", configSetValue);
    prefs.end();
    reset();
    return;
  }
  // Load all fields in keyMap
  for (size_t i = 0; keyMap[i].key != nullptr; ++i) {
    uint8_t* field = (uint8_t*)&store + keyMap[i].fieldOffset;
    size_t sz = keyMap[i].size;
    size_t read = prefs.getBytes(keyMap[i].key, field, sz);
  }
  deleteOldKeys();
  prefs.end();
}

void Config::changeMode(int newmode) {
  #ifdef USE_SD
    bool pir = player.isRunning();
    if (SDC_CS==255) return;
    if (getMode()==PM_SDCARD) {
      sdResumePos = player.getFilePos();
    }
    if (network.status==SOFT_AP || display.mode()==LOST) {
      saveValue(&store.play_mode, static_cast<uint8_t>(PM_SDCARD));
      delay(50);
      ESP.restart();
    }
    if (!sdman.ready && newmode!=PM_WEB) {
      if (!sdman.start()) {
        Serial.println("##[ERROR]#\tSD Not Found");
        netserver.requestOnChange(GETPLAYERMODE, 0);
        sdman.stop();
        return;
      }
    }
    if (newmode<0||newmode>MAX_PLAY_MODE) {
      store.play_mode++;
      if (getMode() > MAX_PLAY_MODE) store.play_mode=0;
    } else {
      store.play_mode=(playMode_e)newmode;
    }
    saveValue(&store.play_mode, store.play_mode, true, true);
    _SDplaylistFS = getMode()==PM_SDCARD?&sdman:(true?&SPIFFS:_SDplaylistFS);
    if (getMode()==PM_SDCARD) {
      if (pir) player.sendCommand({PR_STOP, 0});
      display.putRequest(NEWMODE, SDCHANGE);
      while(display.mode()!=SDCHANGE)
        delay(10);
      delay(50);
    }
    if (getMode()==PM_WEB) {
      if (network.status==SDREADY) ESP.restart();
      sdman.stop();
    }
    if (!_bootDone) return;
    initPlaylistMode();
    if (pir) player.sendCommand({PR_PLAY, getMode()==PM_WEB?store.lastStation:store.lastSdStation});
    netserver.resetQueue();
    //netserver.requestOnChange(GETPLAYERMODE, 0);
    netserver.requestOnChange(GETINDEX, 0);
    //netserver.requestOnChange(GETMODE, 0);
    // netserver.requestOnChange(CHANGEMODE, 0);
    display.resetQueue();
    display.putRequest(NEWMODE, PLAYER);
    display.putRequest(NEWSTATION);
  #endif //#ifdef USE_SD
}


void Config::initSDPlaylist() {
  #ifdef USE_SD
    //store.countStation = 0;
    bool doIndex = !sdman.exists(INDEX_SD_PATH);
    if (doIndex) sdman.indexSDPlaylist();
    if (SDPLFS()->exists(INDEX_SD_PATH)) {
      File index = SDPLFS()->open(INDEX_SD_PATH, "r");
      //store.countStation = index.size() / 4;
      if (doIndex) {
        lastStation(_randomStation());
        sdResumePos = 0;
      }
      index.close();
      //saveValue(&store.countStation, store.countStation, true, true);
    }
  #endif //#ifdef USE_SD
}

bool Config::spiffsCleanup() {
  bool ret = (SPIFFS.exists(PLAYLIST_SD_PATH)) || (SPIFFS.exists(INDEX_SD_PATH)) || (SPIFFS.exists(INDEX_PATH));
  if (SPIFFS.exists(PLAYLIST_SD_PATH)) SPIFFS.remove(PLAYLIST_SD_PATH);
  if (SPIFFS.exists(INDEX_SD_PATH)) SPIFFS.remove(INDEX_SD_PATH);
  if (SPIFFS.exists(INDEX_PATH)) SPIFFS.remove(INDEX_PATH);
  return ret;
}

char * Config::ipToStr(IPAddress ip) {
  snprintf(ipBuf, 16, "%u.%u.%u.%u", ip[0], ip[1], ip[2], ip[3]);
  return ipBuf;
}

void Config::initPlaylistMode() {
  uint16_t _lastStation = 0;
  uint16_t cs = playlistLength();
  #ifdef USE_SD
    if (getMode()==PM_SDCARD) {
      if (!sdman.start()) {
        store.play_mode=PM_WEB;
        Serial.println("SD Mount Failed");
        changeMode(PM_WEB);
        _lastStation = store.lastStation;
      } else {
        if (_bootDone) Serial.println("SD Mounted"); else BOOTLOG("SD Mounted");
          if (_bootDone) Serial.println("Waiting for SD card indexing..."); else BOOTLOG("Waiting for SD card indexing...");
          initSDPlaylist();
          if (_bootDone) Serial.println("done"); else BOOTLOG("done");
          _lastStation = store.lastSdStation;
          
          if (_lastStation>cs && cs>0) {
            _lastStation=1;
          }
          if (_lastStation==0) {
            _lastStation = _randomStation();
          }
      }
    } else {
      Serial.println("done");
      _lastStation = store.lastStation;
    }
  #else
    store.play_mode=PM_WEB;
    _lastStation = store.lastStation;
  #endif //ifdef USE_SD
  if (getMode()==PM_WEB && _wwwFilesExist()) initPlaylist();
  log_i("%d" ,_lastStation);
  // Validate station number is within range
  if (cs == 0) {
    _lastStation = 0;  // No playlist, no valid station
  } else if (_lastStation > cs) {
    _lastStation = 1;  // Station out of range, reset to first
  } else if (_lastStation == 0) {
    _lastStation = getMode()==PM_WEB?1:_randomStation();  // No station selected, pick first
  }
  lastStation(_lastStation);
  saveValue(&store.play_mode, store.play_mode, true, true);
  _bootDone = true;
  loadStation(_lastStation);
}

void Config::_initHW() {
  loadTheme();
  #if IR_PIN!=255
    prefs.begin("ehradio", false);
    memset(&ircodes, 0, sizeof(ircodes));
    size_t read = prefs.getBytes("ircodes", &ircodes, sizeof(ircodes));
    if (read != sizeof(ircodes) || ircodes.ir_set != 4224) {
      Serial.println("[_initHW] ircodes not initialized or corrupt, resetting...");
      prefs.remove("ircodes");
      memset(ircodes.irVals, 0, sizeof(ircodes.irVals));
    }
    prefs.end();
  #endif
  #if BRIGHTNESS_PIN!=255
    pinMode(BRIGHTNESS_PIN, OUTPUT);
    setBrightness(false);
  #endif
}

uint16_t Config::color565(uint8_t r, uint8_t g, uint8_t b)
{
  return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

void Config::loadTheme() {
  theme.background    = color565(COLOR_BACKGROUND);
  theme.meta          = color565(COLOR_STATION_NAME);
  theme.metabg        = color565(COLOR_STATION_BG);
  theme.metafill      = color565(COLOR_STATION_FILL);
  theme.title1        = color565(COLOR_SNG_TITLE_1);
  theme.title2        = color565(COLOR_SNG_TITLE_2);
  theme.digit         = color565(COLOR_DIGITS);
  theme.div           = color565(COLOR_DIVIDER);
  theme.weather       = color565(COLOR_WEATHER);
  theme.vumax         = color565(COLOR_VU_MAX);
  theme.vumin         = color565(COLOR_VU_MIN);
  theme.clock         = color565(COLOR_CLOCK);
  theme.clockbg       = color565(COLOR_CLOCK_BG);
  theme.seconds       = color565(COLOR_SECONDS);
  theme.dow           = color565(COLOR_DAY_OF_W);
  theme.date          = color565(COLOR_DATE);
  theme.heap          = color565(COLOR_HEAP);
  theme.buffer        = color565(COLOR_BUFFER);
  theme.ip            = color565(COLOR_IP);
  theme.vol           = color565(COLOR_VOLUME_VALUE);
  theme.rssi          = color565(COLOR_RSSI);
  theme.bitrate       = color565(COLOR_BITRATE);
  theme.volbarout     = color565(COLOR_VOLBAR_OUT);
  theme.volbarin      = color565(COLOR_VOLBAR_IN);
  theme.plcurrent     = color565(COLOR_PL_CURRENT);
  theme.plcurrentbg   = color565(COLOR_PL_CURRENT_BG);
  theme.plcurrentfill = color565(COLOR_PL_CURRENT_FILL);
  theme.playlist[0]   = color565(COLOR_PLAYLIST_0);
  theme.playlist[1]   = color565(COLOR_PLAYLIST_1);
  theme.playlist[2]   = color565(COLOR_PLAYLIST_2);
  theme.playlist[3]   = color565(COLOR_PLAYLIST_3);
  theme.playlist[4]   = color565(COLOR_PLAYLIST_4);
  #include "../displays/tools/tftinverttitle.h"
}

void Config::reset() {
  Serial.print("[Prefs] Reset requested, resetting config...\n");
  nvs_flash_erase();
  nvs_flash_init();
  //prefs.begin("ehradio", false);
  //prefs.clear();
  //prefs.end();
  setDefaults();
  delay(500);
  ESP.restart();
}
void Config::enableScreensaver(bool val) {
  saveValue(&store.screensaverEnabled, val);
  #ifndef DSP_LCD
    display.putRequest(NEWMODE, PLAYER);
  #endif
}
void Config::setScreensaverTimeout(uint16_t val) {
  val=constrain(val,5,65520);
  saveValue(&store.screensaverTimeout, val);
  #ifndef DSP_LCD
    display.putRequest(NEWMODE, PLAYER);
  #endif
}
void Config::setScreensaverBlank(bool val) {
  saveValue(&store.screensaverBlank, val);
  #ifndef DSP_LCD
    display.putRequest(NEWMODE, PLAYER);
  #endif
}
void Config::setScreensaverPlayingEnabled(bool val) {
  saveValue(&store.screensaverPlayingEnabled, val);
  #ifndef DSP_LCD
    display.putRequest(NEWMODE, PLAYER);
  #endif
}
void Config::setScreensaverPlayingTimeout(uint16_t val) {
  val=constrain(val,1,1080);
  config.saveValue(&config.store.screensaverPlayingTimeout, val);
  #ifndef DSP_LCD
    display.putRequest(NEWMODE, PLAYER);
  #endif
}
void Config::setScreensaverPlayingBlank(bool val) {
  saveValue(&store.screensaverPlayingBlank, val);
  #ifndef DSP_LCD
    display.putRequest(NEWMODE, PLAYER);
  #endif
}

void Config::setShowweather(bool val) {
  config.saveValue(&config.store.showweather, val);
  network.trueWeather=false;
  network.forceWeather = true;
  display.putRequest(SHOWWEATHER);
}
void Config::setWeatherKey(const char *val) {
  saveValue(store.weatherkey, val, WEATHERKEY_LENGTH);
  network.trueWeather=false;
  display.putRequest(NEWMODE, CLEAR);
  display.putRequest(NEWMODE, PLAYER);
}
void Config::setSDpos(uint32_t val) {
  if (getMode()==PM_SDCARD) {
    sdResumePos = 0;
    if (!player.isRunning()) {
      player.setResumeFilePos(val-player.sd_min);
      player.sendCommand({PR_PLAY, config.store.lastSdStation});
    } else {
      player.setFilePos(val-player.sd_min);
    }
  }
}

void Config::setIrBtn(int val) {
  #if IR_PIN!=255
    irindex = val;
    netserver.irRecordEnable = (irindex >= 0);
    irchck = 0;
    netserver.irValsToWs();
    if (irindex < 0) saveIR();
  #endif
}

void Config::resetSystem(const char *val, uint8_t clientId) {
  if (strcmp(val, "system") == 0) {
    saveValue(&store.smartstart, SMART_START, false);
    saveValue(&store.audioinfo, SHOW_AUDIO_INFO, false);
    saveValue(&store.vumeter, SHOW_VU_METER, false);
    saveValue(&store.wifiscanbest, WIFI_SCAN_BEST_RSSI, false);
    saveValue(&store.softapdelay, (uint8_t)SOFTAP_REBOOT_DELAY, false);
    snprintf(store.mdnsname, MDNS_LENGTH, "ehradio-%x", getChipId());
    saveValue(store.mdnsname, store.mdnsname, MDNS_LENGTH, true, true);
    display.putRequest(NEWMODE, CLEAR); display.putRequest(NEWMODE, PLAYER);
    netserver.requestOnChange(GETSYSTEM, clientId);
    return;
  }
  if (strcmp(val, "screen") == 0) {
    saveValue(&store.flipscreen, SCREEN_FLIP, false);
    saveValue(&store.volumepage, VOLUME_PAGE);
    saveValue(&store.clock12, CLOCK_TWELVE);
    display.flip();
    saveValue(&store.invertdisplay, SCREEN_INVERT, false);
    display.invert();
    saveValue(&store.dspon, true, false);
    store.brightness = SCREEN_BRIGHTNESS;
    setBrightness(false);
    saveValue(&store.contrast, (uint8_t)SCREEN_CONTRAST, false);
    display.setContrast();
    saveValue(&store.numplaylist, NUMBERED_PLAYLIST);
    saveValue(&store.screensaverEnabled, SS_NOTPLAYING);
    saveValue(&store.screensaverTimeout, (uint16_t)SS_NOTPLAYING_TIME);
    saveValue(&store.screensaverBlank, SS_NOTPLAYING_BLANK);
    saveValue(&store.screensaverPlayingEnabled, SS_PLAYING);
    saveValue(&store.screensaverPlayingTimeout, (uint16_t)SS_PLAYING_TIME);
    saveValue(&store.screensaverPlayingBlank, SS_PLAYING_BLANK);
    display.putRequest(NEWMODE, CLEAR); display.putRequest(NEWMODE, PLAYER);
    netserver.requestOnChange(GETSCREEN, clientId);
    return;
  }
  if (strcmp(val, "timezone") == 0) {
    saveValue(store.tz_name, TIMEZONE_NAME, sizeof(store.tz_name), false);
    saveValue(store.tzposix, TIMEZONE_POSIX, sizeof(store.tzposix), false);
    saveValue(store.sntp1, SNTP_1, sizeof(store.sntp1), false);
    saveValue(store.sntp2, SNTP_2, sizeof(store.sntp2));
    network.forceTimeSync = true;
    network.requestTimeSync(true);
    network.forceTimeSync = true;
    netserver.requestOnChange(GETTIMEZONE, clientId);
    return;
  }
  if (strcmp(val, "weather") == 0) {
    saveValue(&store.showweather, false, false);
    saveValue(store.weatherlat, WEATHER_LAT, sizeof(store.weatherlat), false);
    saveValue(store.weatherlon, WEATHER_LON, sizeof(store.weatherlon), false);
    saveValue(store.weatherkey, "", WEATHERKEY_LENGTH);
    network.trueWeather=false;
    display.putRequest(NEWMODE, CLEAR); display.putRequest(NEWMODE, PLAYER);
    netserver.requestOnChange(GETWEATHER, clientId);
    return;
  }
  if (strcmp(val, "mqtt") == 0) {
    saveValue(&store.mqttenable, false, false);
    saveValue(store.mqtthost, MQTT_HOST, sizeof(store.mqtthost), false);
    saveValue(&store.mqttport, (uint16_t)MQTT_PORT);
    saveValue(store.mqttuser, MQTT_USER, sizeof(store.mqttuser), false);
    saveValue(store.mqttpass, MQTT_PASS, sizeof(store.mqttpass), false);
    saveValue(store.mqtttopic, MQTT_TOPIC, sizeof(store.mqtttopic), false);
    netserver.requestOnChange(GETMQTT, clientId);
    return;
  }
  if (strcmp(val, "controls") == 0) {
    saveValue(&store.volsteps, (uint8_t)VOLUME_STEPS, false);
    saveValue(&store.fliptouch, TOUCH_FLIP, false);
    saveValue(&store.dbgtouch, TOUCH_DEBUG, false);
    saveValue(&store.skipPlaylistUpDown, ONE_CLICK_SWITCH);
    setEncAcceleration(ROTARY_ACCEL);
    setIRTolerance(IR_TOLERANCE);
    netserver.requestOnChange(GETCONTROLS, clientId);
    return;
  }
  if (strcmp(val, "1") == 0) {
    config.reset();
    return;
  }
}



void Config::setDefaults() {
  // defaults set byt struct, except one
  Serial.println("[setDefaults] called");
  snprintf(store.mdnsname, MDNS_LENGTH, "ehradio-%x", getChipId());
}

void Config::setShuffle(bool sn) {
  saveValue(&store.sdshuffle, sn);
  if (store.sdshuffle) player.next();
}

void Config::saveIR() {
  #if IR_PIN!=255
    ircodes.ir_set = 4224;
    prefs.begin("ehradio", false);
    size_t written = prefs.putBytes("ircodes", &ircodes, sizeof(ircodes));
    prefs.end();
  #endif
}

void Config::saveVolume() {
  saveValue(&store.volume, store.volume, true, true);
}

uint8_t Config::setVolume(uint8_t val) {
  store.volume = val;
  display.putRequest(DRAWVOL);
  netserver.requestOnChange(VOLUME, 0);
  return store.volume;
}

void Config::setTone(int8_t bass, int8_t middle, int8_t treble) {
  saveValue(&store.bass, bass, false);
  saveValue(&store.middle, middle, false);
  saveValue(&store.treble, treble);
  player.setTone(store.bass, store.middle, store.treble);
  netserver.requestOnChange(EQUALIZER, 0);
}

void Config::setSmartStart(bool ss) {
  saveValue(&store.smartstart, ss);
}

void Config::setBalance(int8_t balance) {
  saveValue(&store.balance, balance);
  player.setBalance(store.balance);
  netserver.requestOnChange(BALANCE, 0);
}

uint8_t Config::setLastStation(uint16_t val) {
  lastStation(val);
  return store.lastStation;
}

uint8_t Config::setCountStation(uint16_t val) {
  saveValue(&store.countStation, val);
  return store.countStation;
}

uint8_t Config::setLastSSID(uint8_t val) {
  saveValue(&store.lastSSID, val);
  return store.lastSSID;
}

void Config::setTitle(const char* title) {
  vuThreshold = 0;
  memset(config.station.title, 0, BUFLEN);
  strlcpy(config.station.title, title, BUFLEN);
  u8fix(config.station.title);
  netserver.requestOnChange(TITLE, 0);
  netserver.loop();
  display.putRequest(NEWTITLE);
}

void Config::setStation(const char* station) {
  memset(config.station.name, 0, BUFLEN);
  strlcpy(config.station.name, station, BUFLEN);
  u8fix(config.station.title);
}

void Config::indexPlaylist() {
  File playlist = SPIFFS.open(PLAYLIST_PATH, "r");
  if (!playlist) {
    return;
  }
  char sName[BUFLEN], sUrl[BUFLEN];
  int sOvol;
  File index = SPIFFS.open(INDEX_PATH, "w");
  while (playlist.available()) {
    uint32_t pos = playlist.position();
    if (parseCSV(playlist.readStringUntil('\n').c_str(), sName, sUrl, sOvol)) {
      index.write((uint8_t *) &pos, 4);
    }
  }
  index.close();
  playlist.close();
}

void Config::initPlaylist() {
  //store.countStation = 0;
  if (!SPIFFS.exists(INDEX_PATH)) indexPlaylist();

  /*if (SPIFFS.exists(INDEX_PATH)) {
    File index = SPIFFS.open(INDEX_PATH, "r");
    store.countStation = index.size() / 4;
    index.close();
    saveValue(&store.countStation, store.countStation, true, true);
  }*/
}
uint16_t Config::playlistLength() {
  uint16_t out = 0;
  if (SDPLFS()->exists(REAL_INDEX)) {
    File index = SDPLFS()->open(REAL_INDEX, "r");
    out = index.size() / 4;
    index.close();
  }
  return out;
}
bool Config::loadStation(uint16_t ls) {
  char sName[BUFLEN], sUrl[BUFLEN];
  int sOvol;
  uint16_t cs = playlistLength();
  if (cs == 0) {
    memset(station.url, 0, BUFLEN);
    memset(station.name, 0, BUFLEN);
    strncpy(station.name, "ehRadio", BUFLEN);
    station.ovol = 0;
    return false;
  }
  if (ls > playlistLength()) {
    ls = 1;
  }
  File playlist = SDPLFS()->open(REAL_PLAYL, "r");
  File index = SDPLFS()->open(REAL_INDEX, "r");
  index.seek((ls - 1) * 4, SeekSet);
  uint32_t pos;
  index.readBytes((char *) &pos, 4);
  index.close();
  playlist.seek(pos, SeekSet);
  if (parseCSV(playlist.readStringUntil('\n').c_str(), sName, sUrl, sOvol)) {
    memset(station.url, 0, BUFLEN);
    memset(station.name, 0, BUFLEN);
    strncpy(station.name, sName, BUFLEN);
    strncpy(station.url, sUrl, BUFLEN);
    station.ovol = sOvol;
    setLastStation(ls);
  }
  playlist.close();
  return true;
}

char * Config::stationByNum(uint16_t num) {
  File playlist = SDPLFS()->open(REAL_PLAYL, "r");
  File index = SDPLFS()->open(REAL_INDEX, "r");
  index.seek((num - 1) * 4, SeekSet);
  uint32_t pos;
  memset(_stationBuf, 0, BUFLEN/2);
  index.readBytes((char *) &pos, 4);
  index.close();
  playlist.seek(pos, SeekSet);
  strncpy(_stationBuf, playlist.readStringUntil('\t').c_str(), BUFLEN/2);
  playlist.close();
  return _stationBuf;
}

void Config::escapeQuotes(const char* input, char* output, size_t maxLen) {
  size_t j = 0;
  for (size_t i = 0; input[i] != '\0' && j < maxLen - 1; ++i) {
    if (input[i] == '"' && j < maxLen - 2) {
      output[j++] = '\\';
      output[j++] = '"';
    } else {
      output[j++] = input[i];
    }
  }
  output[j] = '\0';
}

bool Config::parseCSV(const char* line, char* name, char* url, int &ovol) {
  char *tmpe;
  const char* cursor = line;
  char buf[5];
  tmpe = strstr(cursor, "\t");
  if (tmpe == NULL) return false;
  strlcpy(name, cursor, tmpe - cursor + 1);
  if (strlen(name) == 0) return false;
  cursor = tmpe + 1;
  tmpe = strstr(cursor, "\t");
  if (tmpe == NULL) return false;
  strlcpy(url, cursor, tmpe - cursor + 1);
  if (strlen(url) == 0) return false;
  cursor = tmpe + 1;
  if (strlen(cursor) == 0) return false;
  strlcpy(buf, cursor, 4);
  ovol = atoi(buf);
  return true;
}

bool Config::parseCSVimport(const char* line, char* name, char* url, int &ovol) {
  // Reset outputs
  if (name) name[0] = 0;
  if (url) url[0] = 0;
  ovol = 0;

  // Copy line to a buffer for tokenization
  char buf[BUFLEN * 2];
  strncpy(buf, line, sizeof(buf) - 1);
  buf[sizeof(buf) - 1] = 0;

  // Detect delimiter: prefer tab, then space
  char delim = 0;
  if (strchr(buf, '\t')) delim = '\t';
  else delim = ' ';

  // Tokenize by detected delimiter only
  char* tokens[32];
  int t = 0;
  char* p = strtok(buf, (delim == '\t') ? "\t" : " ");
  while (p && t < 32) {
    tokens[t++] = p;
    p = strtok(nullptr, (delim == '\t') ? "\t" : " ");
  }

  // --- TAB-DELIMITED LOGIC ---
  if (delim == '\t') {
    if (t == 1) {
      // 1 field: URL only
      if (strstr(tokens[0], ".") && (strstr(tokens[0], "/") || strstr(tokens[0], "://"))) {
        if (url) {
          if (strncmp(tokens[0], "http://", 7) != 0 && strncmp(tokens[0], "https://", 8) != 0) {
            snprintf(url, BUFLEN, "http://%s", tokens[0]);
          } else {
            strlcpy(url, tokens[0], BUFLEN);
          }
        }
        if (name) {
          urlToName(url, name, BUFLEN);
        }
        ovol = 0;
        return true;
      } else {
        return false;
      }
    } else if (t == 2) {
      // 2 fields: one is URL, one is name (order does not matter)
      int urlIdx = -1, nameIdx = -1;
      for (int i = 0; i < 2; ++i) {
        if (strstr(tokens[i], ".") && (strstr(tokens[i], "/") || strstr(tokens[i], "://"))) urlIdx = i;
        else nameIdx = i;
      }
      if (urlIdx == -1 || nameIdx == -1) return false;
      if (url) {
        if (strncmp(tokens[urlIdx], "http://", 7) != 0 && strncmp(tokens[urlIdx], "https://", 8) != 0) {
          snprintf(url, BUFLEN, "http://%s", tokens[urlIdx]);
        } else {
          strlcpy(url, tokens[urlIdx], BUFLEN);
        }
      }
      if (name) {
        strlcpy(name, tokens[nameIdx], BUFLEN);
      }
      ovol = 0;
      return true;
    } else if (t >= 3) {
      // 3+ fields: Find URL (required), ovol (optional), and name from remaining fields
      int urlIdx = -1;
      for (int i = 0; i < t; ++i) {
        if (strstr(tokens[i], ".") && (strstr(tokens[i], "/") || strstr(tokens[i], "://"))) {
          urlIdx = i;
          break;
        }
      }
      if (urlIdx == -1) return false; // No URL found
      
      // Find ovol (optional) - numeric value between -64 and 64
      int ovolIdx = -1;
      for (int i = 0; i < t; ++i) {
        if (i == urlIdx) continue; // Skip URL field
        char* endptr = nullptr;
        long val = strtol(tokens[i], &endptr, 10);
        if (endptr && *endptr == '\0' && val >= -64 && val <= 64) {
          ovolIdx = i;
          // Clamp to -30 to 30
          if (val < -30) val = -30;
          if (val > 30) val = 30;
          ovol = (int)val;
          break; // Use the first matching ovol
        }
      }
      
      // Extract URL
      if (url) {
        if (strncmp(tokens[urlIdx], "http://", 7) != 0 && strncmp(tokens[urlIdx], "https://", 8) != 0) {
          snprintf(url, BUFLEN, "http://%s", tokens[urlIdx]);
        } else {
          strlcpy(url, tokens[urlIdx], BUFLEN);
        }
      }
      
      // Name is FIRST field only (not all non-URL fields)
      if (name) {
        name[0] = 0;
        if (urlIdx > 0) {
          // URL not first, so name is first token
          strlcpy(name, tokens[0], BUFLEN);
        } else if (urlIdx == 0 && t > 1) {
          // URL is first, name is second token (if not ovol)
          if (ovolIdx == 1 && t == 2) {
            // No name, only url and ovol
            name[0] = 0;
          } else {
            strlcpy(name, tokens[1], BUFLEN);
          }
        }
      }
      
      if (ovolIdx == -1) ovol = 0;
      return true;
    }
  }

  // --- SPACE-DELIMITED LOGIC ---
  // Find URL token (must contain dot and slash or ://)
  int urlIdx = -1;
  for (int i = 0; i < t; ++i) {
    if (strstr(tokens[i], ".") && (strstr(tokens[i], "/") || strstr(tokens[i], "://"))) {
      urlIdx = i;
      break;
    }
  }
  if (urlIdx == -1) return false; // URL is required

  // Name is FIRST field only
  if (name) {
    name[0] = 0;
    if (urlIdx > 0) {
      // URL not first, so name is first token
      strlcpy(name, tokens[0], BUFLEN);
      // Check if LAST token is ovol (must be at end)
      const char* lastToken = tokens[t-1];
      char* endptr = nullptr;
      long val = strtol(lastToken, &endptr, 10);
      if (endptr && *endptr == '\0' && val >= -64 && val <= 64 && t >= 2) {
        if (val < -30) val = -30;
        if (val > 30) val = 30;
        ovol = (int)val;
      } else {
        ovol = 0;
      }
    } else {
      // URL is first: everything after URL is the name (no ovol)
      for (int i = urlIdx + 1; i < t; ++i) {
        if (strlen(name) > 0) strlcat(name, " ", BUFLEN);
        strlcat(name, tokens[i], BUFLEN);
      }
      ovol = 0;
    }
  }

  // Extract URL
    if (url) {
      if (strncmp(tokens[urlIdx], "http://", 7) != 0 && strncmp(tokens[urlIdx], "https://", 8) != 0) {
        snprintf(url, BUFLEN, "http://%s", tokens[urlIdx]);
      } else {
        strlcpy(url, tokens[urlIdx], BUFLEN);
      }
    }
  
  // If name is missing or empty, generate from URL
  if ((name == nullptr || strlen(name) == 0) && url && strlen(url) > 0) {
    urlToName(url, name, BUFLEN);
  }
  
  if (!url || strlen(url) == 0) return false;
  return true;
}

bool Config::parseJSON(const char* line, char* name, char* url, int &ovol) {
  // Helper lambda to extract a value by key (key must be quoted, e.g. "name")
  // Handles both string and numeric values
  auto extract = [](const char* src, const char* key, char* out, size_t outlen) -> bool {
    const char* k = strstr(src, key);
    if (!k) return false;
    k += strlen(key);
    // Skip whitespace and colon
    while (*k && (*k == ' ' || *k == '\t')) k++;
    if (*k != ':') return false;
    k++;
    while (*k && (*k == ' ' || *k == '\t')) k++;
    if (*k == '"') {
      // String value
      k++;
      const char* end = strchr(k, '"');
      if (!end) return false;
      size_t len = end - k;
      if (len >= outlen) len = outlen - 1;
      strncpy(out, k, len);
      out[len] = 0;
      return true;
    } else {
      // Numeric value (int, float, etc.)
      const char* end = k;
      while (*end && ((*end >= '0' && *end <= '9') || *end == '-' || *end == '+')) end++;
      size_t len = end - k;
      if (len == 0 || len >= outlen) return false;
      strncpy(out, k, len);
      out[len] = 0;
      return true;
    }
  };

  // If the line starts with '[', treat as JSON array and extract the first object
  const char* obj = line;
  if (line[0] == '[') {
    // Find the first '{' and the matching '}'
    const char* start = strchr(line, '{');
    if (!start) return false;
    int brace = 1;
    const char* end = start + 1;
    while (*end && brace > 0) {
      if (*end == '{') brace++;
      else if (*end == '}') brace--;
      end++;
    }
    if (brace != 0) return false;
    static char objbuf[512];
    size_t len = end - start;
    if (len >= sizeof(objbuf)) len = sizeof(objbuf) - 1;
    strncpy(objbuf, start, len);
    objbuf[len] = 0;
    obj = objbuf;
  } else if (line[0] == '{') {
    // Single JSON object (JSONL/NDJSON format) - use as-is
    obj = line;
  } else {
    // Try to parse as simple key-value format
    return false;
  }

  char buf[256];
  // 1. Extract name (optional)
  if (!extract(obj, "\"name\"", name, BUFLEN)) {
    if (!extract(obj, "\"title\"", name, BUFLEN)) {
      if (name) name[0] = 0; // Name is optional
    }
  }

  // 2. Try url_resolved, then url, then host+file+port
  bool gotUrl = false;
  if (extract(obj, "\"url_resolved\"", buf, sizeof(buf))) {
    strncpy(url, buf, BUFLEN);
    gotUrl = true;
  } else if (extract(obj, "\"url\"", buf, sizeof(buf))) {
    strncpy(url, buf, BUFLEN);
    gotUrl = true;
  } else {
    char host[246] = {0}, file[254] = {0}, portStr[16] = {0};
    bool gotHost = extract(obj, "\"host\"", host, sizeof(host));
    bool gotFile = extract(obj, "\"file\"", file, sizeof(file));
    bool gotPort = extract(obj, "\"port\"", portStr, sizeof(portStr));
    int port = gotPort ? atoi(portStr) : 80;
    
    if (gotHost) {
      // Determine protocol based on port
      const char* protocol = (port == 443) ? "https://" : "http://";
      
      // Only add port if non-default for the protocol
      bool addPort = (strcmp(protocol, "http://") == 0 && port != 80) || 
                     (strcmp(protocol, "https://") == 0 && port != 443);
      
      if (gotFile && strlen(file) > 0) {
        if (addPort) {
          snprintf(url, BUFLEN, "%s%s:%d%s", protocol, host, port, file[0] == '/' ? file : "/");
        } else {
          snprintf(url, BUFLEN, "%s%s%s", protocol, host, file[0] == '/' ? file : "/");
        }
      } else {
        if (addPort) {
          snprintf(url, BUFLEN, "%s%s:%d", protocol, host, port);
        } else {
          snprintf(url, BUFLEN, "%s%s", protocol, host);
        }
      }
      gotUrl = true;
    }
  }
  if (!gotUrl || strlen(url) == 0) {
    return false;
  }

  // 3. Try ovol, default to 0 if not found, clamp to -30/+30
  char ovolbuf[16] = {0};
  if (extract(obj, "\"ovol\"", ovolbuf, sizeof(ovolbuf))) {
    ovol = atoi(ovolbuf);
    if (ovol < -30) ovol = -30;
    if (ovol > 30) ovol = 30;
  } else {
    ovol = 0;
  }
  
  // 4. If name is missing or empty, generate from URL
  if ((name == nullptr || strlen(name) == 0) && url && strlen(url) > 0) {
    urlToName(url, name, BUFLEN);
  }
  
  return true;
}


void Config::urlToName(const char* url, char* name, size_t maxLen) {
  // Convert URL to readable name: drop protocol, port, convert special chars to hyphens
  const char* start = url;
  // Skip protocol
  if (strncmp(start, "http://", 7) == 0) start += 7;
  else if (strncmp(start, "https://", 8) == 0) start += 8;
  
  size_t j = 0;
  for (size_t i = 0; start[i] != '\0' && j < maxLen - 1; ++i) {
    char c = start[i];
    // Skip port numbers (":1234")
    if (c == ':' && start[i+1] >= '0' && start[i+1] <= '9') {
      // Skip until end of port number or next path segment
      while (start[i] != '\0' && start[i] != '/') i++;
      if (start[i] == '\0') break;
      c = start[i];
    }
    // Convert special chars to hyphens
    if (c == '/' || c == '=' || c == '&' || c == '?') {
      // Don't add hyphen if previous char was already a hyphen
      if (j > 0 && name[j-1] != '-') {
        name[j++] = '-';
      }
    } else {
      name[j++] = c;
    }
  }
  // Trim trailing hyphens
  while (j > 0 && name[j-1] == '-') j--;
  name[j] = '\0';
}

bool Config::parseWsCommand(const char* line, char* cmd, char* val, uint8_t cSize) {
  char *tmpe;
  tmpe = strstr(line, "=");
  if (tmpe == NULL) return false;
  memset(cmd, 0, cSize);
  strlcpy(cmd, line, tmpe - line + 1);
  //if (strlen(tmpe + 1) == 0) return false;
  memset(val, 0, cSize);
  strlcpy(val, tmpe + 1, strlen(line) - strlen(cmd) + 1);
  return true;
}

bool Config::parseSsid(const char* line, char* ssid, char* pass) {
  char *tmpe;
  tmpe = strstr(line, "\t");
  if (tmpe == NULL) return false;
  uint16_t pos = tmpe - line;
  if (pos >= sizeof(ssids[0].ssid)) return false;
  if (strlen(line + pos + 1) >= sizeof(ssids[0].password)) return false;
  memset(ssid, 0, sizeof(ssids[0].ssid));
  strlcpy(ssid, line, pos + 1);
  memset(pass, 0, sizeof(ssids[0].password));
  strlcpy(pass, line + pos + 1, sizeof(ssids[0].password));
  return true;
}

bool Config::saveWifi(const char* post) {
  char ssidval[sizeof(ssids[0].ssid)], passval[sizeof(ssids[0].password)];
  if (parseSsid(post, ssidval, passval)) {
    if (addSsid(ssidval, passval)) {
      ESP.restart();
      return true;
    }
  }
  return false;
}

bool Config::addSsid(const char* ssid, const char* password) {
  int slot = -1;
  for (int i = 0; i < ssidsCount; i++) {
    if (strcmp(ssids[i].ssid, ssid) == 0) {
      slot = i;
      break;
    }
  }
  
  if (slot == -1) {
    slot = (ssidsCount < 5) ? ssidsCount : 4;
    if (slot == ssidsCount && ssidsCount < 5) {
      ssidsCount++;
    }
  }
  
  strlcpy(ssids[slot].ssid, ssid, sizeof(ssids[0].ssid));
  strlcpy(ssids[slot].password, password, sizeof(ssids[0].password));
  setLastSSID(slot + 1);

  File file = SPIFFS.open(TMP_PATH, "w");
  if (!file) return false;
  for (int i = 0; i < ssidsCount; i++) {
    if (strlen(ssids[i].ssid) > 0) {
      file.printf("%s\t%s\n", ssids[i].ssid, ssids[i].password);
    }
  }
  file.close();
  
  if (SPIFFS.exists(TMP_PATH)) {
    SPIFFS.remove(SSIDS_PATH);
    return SPIFFS.rename(TMP_PATH, SSIDS_PATH);
  }
  return false;
}

bool Config::importWifi() {
  if (!SPIFFS.exists(TMP_PATH)) return false;
  SPIFFS.remove(SSIDS_PATH);
  SPIFFS.rename(TMP_PATH, SSIDS_PATH);
  ESP.restart();
  return true;
}

bool Config::initNetwork() {
  File file = SPIFFS.open(SSIDS_PATH, "r");
  if (!file || file.isDirectory()) {
    return false;
  }
  ssidsCount = 0;
  char ssidval[sizeof(ssids[0].ssid)], passval[sizeof(ssids[0].password)];
  while (file.available() && ssidsCount < 5) {
    if (parseSsid(file.readStringUntil('\n').c_str(), ssidval, passval)) {
      strlcpy(ssids[ssidsCount].ssid, ssidval, sizeof(ssids[0].ssid));
      strlcpy(ssids[ssidsCount].password, passval, sizeof(ssids[0].password));
      ssidsCount++;
    }
  }
  file.close();
  return true;
}

void Config::setBrightness(bool dosave) {
  #if BRIGHTNESS_PIN!=255
    if (!store.dspon && dosave) {
      display.wakeup();
    }
    analogWrite(BRIGHTNESS_PIN, map(store.brightness, 0, 100, 0, 255));
    if (!store.dspon) store.dspon = true;
    if (dosave) {
      saveValue(&store.brightness, store.brightness, false, true);
      saveValue(&store.dspon, store.dspon, true, true);
    }
  #endif
  #ifdef USE_NEXTION
    nextion.wake();
    char cmd[15];
    snprintf(cmd, 15, "dims=%d", store.brightness);
    nextion.putcmd(cmd);
    if (!store.dspon) store.dspon = true;
    if (dosave) {
      saveValue(&store.brightness, store.brightness, false, true);
      saveValue(&store.dspon, store.dspon, true, true);
    }
  #endif
}

void Config::setDspOn(bool dspon, bool saveval) {
  if (saveval) {
    store.dspon = dspon;
    saveValue(&store.dspon, store.dspon, true, true);
  }
  #ifdef USE_NEXTION
    if (!dspon) nextion.sleep();
    else nextion.wake();
  #endif
  if (!dspon) {
    #if BRIGHTNESS_PIN!=255
      analogWrite(BRIGHTNESS_PIN, 0);
    #endif
    display.deepsleep();
  } else {
    display.wakeup();
    #if BRIGHTNESS_PIN!=255
      analogWrite(BRIGHTNESS_PIN, map(store.brightness, 0, 100, 0, 255));
    #endif
  }
}

void Config::doSleep() {
  if (BRIGHTNESS_PIN!=255) analogWrite(BRIGHTNESS_PIN, 0);
  display.deepsleep();
  #ifdef USE_NEXTION
    nextion.sleep();
  #endif
  #ifndef ARDUINO_ESP32C3_DEV
    if (WAKE_PIN!=255) esp_sleep_enable_ext0_wakeup((gpio_num_t)WAKE_PIN, LOW);
    esp_sleep_enable_timer_wakeup(config.sleepfor * 60 * 1000000ULL);
    esp_deep_sleep_start();
  #endif
}

void Config::doSleepW() {
  if (BRIGHTNESS_PIN!=255) analogWrite(BRIGHTNESS_PIN, 0);
  display.deepsleep();
  #ifdef USE_NEXTION
    nextion.sleep();
  #endif
  #ifndef ARDUINO_ESP32C3_DEV
    if (WAKE_PIN!=255) esp_sleep_enable_ext0_wakeup((gpio_num_t)WAKE_PIN, LOW);
    esp_deep_sleep_start();
  #endif
}

void Config::sleepForAfter(uint16_t sf, uint16_t sa) {
  sleepfor = sf;
  if (sa > 0) _sleepTimer.attach(sa * 60, doSleep);
  else doSleep();
}

void Config::purgeUnwantedFiles() {
  BOOTLOG("Scanning SPIFFS for unwanted files...");
  File root = SPIFFS.open("/");
  if (!root || !root.isDirectory()) return;

  File file = root.openNextFile();
  while (file) {
    if (file.isDirectory()) {
      file = root.openNextFile();
      continue;
    }
    String path = file.path();
    bool keep = false;
    if (path.startsWith("/www/")) {
      String name = path.substring(5);
      for (size_t i = 0; i < wwwFilesCount; i++) {
        if (name == String(wwwFiles[i]) || name == String(wwwFiles[i]) + ".gz") {
          keep = true;
          break;
        }
      }
    } else if (path.startsWith("/data/")) {
      String name = path.substring(6);
      for (size_t i = 0; i < dataFilesCount; i++) {
        if (name == String(dataFiles[i])) {
          keep = true;
          break;
        }
      }
    }
    if (!keep) {
      SPIFFS.remove(path);
      BOOTLOG("Removed: %s", path.c_str());
    }
    file = root.openNextFile();
  }
  BOOTLOG("Purge complete.");
}

void Config::deleteMainwwwFile() {
  if (wwwFilesCount > 0) {
    const char* lastFile = wwwFiles[wwwFilesCount - 1];
    char mainfile[64];
    snprintf(mainfile, sizeof(mainfile), "/www/%s", lastFile);
    if (SPIFFS.exists(mainfile)) {
      SPIFFS.remove(mainfile);
      Serial.printf("[Config] Deleted main www file: %s\n", mainfile);
    }
    snprintf(mainfile, sizeof(mainfile), "/www/%s.gz", lastFile);
    if (SPIFFS.exists(mainfile)) {
      SPIFFS.remove(mainfile);
      Serial.printf("[Config] Deleted main www file: %s\n", mainfile);
    }
  }
}

void cleanStaleSearchResults() {
  const char* metaPath = "/www/searchresults.json.meta";
  if (SPIFFS.exists(metaPath)) {
    File metaFile = SPIFFS.open(metaPath, "r");
    metaFile.readStringUntil('\n'); // 1st line query
    String timeStr = metaFile.readStringUntil('\n'); //2nd line is time
    metaFile.close();
    if (timeStr.length() > 0) {
      time_t fileTime = atol(timeStr.c_str());
      time_t now = time(nullptr);
      if (now < 100000000 || (now - fileTime) > 86400) {
        Serial.print("Cleaning stale search results.\n");
        SPIFFS.remove(metaPath);
        SPIFFS.remove("/www/searchresults.json");
        SPIFFS.remove("/www/search.txt");
      }
    }
  }
}

void fixPlaylistFileEnding() {
  const char* playlistPath = PLAYLIST_PATH;
  if (!SPIFFS.exists(playlistPath)) return;
  File playlistfile = SPIFFS.open(playlistPath, "r+");
  if (!playlistfile) return;
  size_t sz = playlistfile.size();
  if (sz < 2) { playlistfile.close(); return; }
  playlistfile.seek(sz - 2, SeekSet);
  char last2[3] = {0};
  playlistfile.read((uint8_t*)last2, 2);
  if (!(last2[0] == '\r' && last2[1] == '\n')) {
    playlistfile.seek(sz, SeekSet);
    playlistfile.write((const uint8_t*)"\r\n", 2);
  }
  playlistfile.close();
}

void getRequiredFiles(void* param) {
  #ifdef UPDATEURL
    player.sendCommand({PR_STOP, 0});
    char localFileGz[64];
    char localFile[64];
    char tryFile[64];
    char tryUrl[128];
    for (size_t i = 0; i < wwwFilesCount; i++) {
      display.putRequest(NEWMODE, UPDATING);
      const char* fname = wwwFiles[i];
      snprintf(localFileGz, sizeof(localFileGz), "/www/%s.gz", fname);
      snprintf(localFile, sizeof(localFile), "/www/%s", fname);
      if (SPIFFS.exists(localFileGz)) SPIFFS.remove(localFileGz);
      if (SPIFFS.exists(localFile)) SPIFFS.remove(localFile);
      for (size_t j = 0; j < 2; j++) {
        if (j == 0) { // Try compressed first
          snprintf(tryFile, sizeof(tryFile), "%s", localFileGz);
          snprintf(tryUrl, sizeof(tryUrl), "%s%s.gz", FILESURL, fname);
        } else { // Fallback to uncompressed
          snprintf(tryFile, sizeof(tryFile), "%s", localFile);
          snprintf(tryUrl, sizeof(tryUrl), "%s%s", FILESURL, fname);
        }
        Serial.printf("[ESPFileUpdater: %s] Updating required file.\n", tryFile);
        ESPFileUpdater* getfile = (ESPFileUpdater*)param;
        ESPFileUpdater::UpdateStatus result = getfile->checkAndUpdate(
            tryFile,
            tryUrl,
            "",
            ESPFILEUPDATER_VERBOSE
       );
        if (result == ESPFileUpdater::UPDATED) {
          Serial.printf("[ESPFileUpdater: %s] Download completed.\n", tryFile);
          break; // Exit inner loop on success
        } else {
          if (j == 0) Serial.printf("[ESPFileUpdater: %s] Download failed. Will retry for uncompressed file.\n", tryFile);
          if (j == 1) Serial.printf("[ESPFileUpdater: %s] Download failed. No online file available. Are you running a custom version?\n", tryFile);
        }
      }
    }
    // Delete any files in /www that are not in the wwwFiles list
    File root = SPIFFS.open("/www");
    if (root && root.isDirectory()) {
      File file = root.openNextFile();
      while (file) {
        const char* path = file.name();
        // Extract filename from full path
        const char* name = path;
        const char* slash = strrchr(path, '/');
        if (slash) name = slash + 1;
        bool found = false;
        for (size_t j = 0; j < wwwFilesCount; j++) {
          // Check against both compressed and uncompressed names
          char requiredNameGz[64];
          snprintf(requiredNameGz, sizeof(requiredNameGz), "%s.gz", wwwFiles[j]);
          if (strcmp(name, wwwFiles[j]) == 0 || strcmp(name, requiredNameGz) == 0) {
            found = true;
            break;
          }
        }
        if (!found) {
          Serial.printf("[File: /www/%s] Deleting - not in required file list.\n", path);
          SPIFFS.remove(path);
        }
        file = root.openNextFile();
      }
    }
    delay(200);
    ESP.restart();
    vTaskDelete(NULL);
  #endif //#ifdef UPDATEURL
}

void checkNewVersionFile() {
  #ifdef UPDATEURL
    const char* newVersionPath = "/data/new_ver.txt";
    netserver.newVersion = String(RADIOVERSION);
    if (SPIFFS.exists(newVersionPath)) {
      File newVerFile = SPIFFS.open(newVersionPath, "r");
      if (newVerFile) {
        String line = newVerFile.readStringUntil('\n');
        line.trim();
        if (line.indexOf(VERSIONSTRING) >= 0) {
          int firstQuote = line.indexOf('"');
          int lastQuote = line.lastIndexOf('"');
          if (firstQuote >= 0 && lastQuote > firstQuote) {
            String extractedVersion = line.substring(firstQuote + 1, lastQuote);
            if (extractedVersion.length() > 0) {
              netserver.newVersion = extractedVersion;
            }
          }
        }
        newVerFile.close();
      }
    }
    if (netserver.newVersion != String(RADIOVERSION)) {
      netserver.newVersionAvailable = true;
    } else {
      netserver.newVersionAvailable =  false;
    }
  #endif //#ifdef UPDATEURL
}

void Config::updateFile(void* param, const char* localFile, const char* onlineFile, const char* updatePeriod, const char* simpleName) {
  Serial.printf("[ESPFileUpdater: %s] Started update.\n", simpleName);
  ESPFileUpdater* updatefile = (ESPFileUpdater*)param;
  ESPFileUpdater::UpdateStatus result = updatefile->checkAndUpdate(
      localFile,
      onlineFile,
      updatePeriod,
      ESPFILEUPDATER_VERBOSE
 );
  if (result == ESPFileUpdater::UPDATED) {
    Serial.printf("[ESPFileUpdater: %s] Update completed.\n", simpleName);
  } else if (result == ESPFileUpdater::NOT_MODIFIED||result == ESPFileUpdater::MAX_AGE_NOT_REACHED) {
    Serial.printf("[ESPFileUpdater: %s] No update needed.\n", simpleName);
  } else {
    Serial.printf("[ESPFileUpdater: %s] Update failed.\n", simpleName);
  }
}

void startAsyncServices(void* param) {
  #ifdef PLAYLIST_DEFAULT_URL
    if (!SPIFFS.exists("/data/playlist.csv")) config.updateFile(param, "/data/playlist.csv", PLAYLIST_DEFAULT_URL, "", "Default playlist");
  #endif
  fixPlaylistFileEnding(); // playlist.csv MUST have a line-feed at end (can happen easily by uploading a file)
  #ifdef UPDATEURL
    config.updateFile(param, "/data/new_ver.txt", CHECKUPDATEURL, CHECKUPDATEURL_TIME, "New version number");
    checkNewVersionFile();
  #endif
  config.updateFile(param, "/www/timezones.json.gz", TIMEZONES_JSON_URL, TIMEZONES_JSON_CHECKTIME, "Timezones database file");
  config.updateFile(param, "/www/rb_srvrs.json", RADIO_BROWSER_SERVERS_URL, RB_SERVERS_CHECKTIME, "Radio Browser servers list");
  cleanStaleSearchResults();
  vTaskDelete(NULL);
}

void Config::startAsyncServicesButWait() {
  if (WiFi.status() != WL_CONNECTED) return;
  ESPFileUpdater* updater = nullptr;
  updater = new ESPFileUpdater(SPIFFS);
  updater->setMaxSize(1024);
  updater->setUserAgent(ESPFILEUPDATER_USERAGENT);
  if (!wwwFilesExist) {
    #ifdef UPDATEURL
      xTaskCreate(getRequiredFiles, "getRequiredFiles", 8192, updater, 2, NULL);
    #endif
  } else {
    xTaskCreate(startAsyncServices, "startAsyncServices", 8192, updater, 2, NULL);
  }
}

void Config::bootInfo() {
  BOOTLOG("************************************************");
  BOOTLOG("*               ehRadio %s             *", RADIOVERSION);
  BOOTLOG("************************************************");
  BOOTLOG("------------------------------------------------");
  BOOTLOG("arduino:\t%d", ARDUINO);
  BOOTLOG("compiler:\t%s", __VERSION__);
  BOOTLOG("esp32core:\t%d.%d.%d", ESP_ARDUINO_VERSION_MAJOR, ESP_ARDUINO_VERSION_MINOR, ESP_ARDUINO_VERSION_PATCH);
  uint32_t chipId = 0;
  for(int i=0; i<17; i=i+8) {
    chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
  }
  BOOTLOG("chip:\t\tmodel: %s | rev: %d | id: %d | cores: %d | psram: %d", ESP.getChipModel(), ESP.getChipRevision(), chipId, ESP.getChipCores(), ESP.getPsramSize());
  BOOTLOG("display:\t%d", DSP_MODEL);
  if (VS1053_CS==255) {
    BOOTLOG("audio:\t\t%s (%d, %d, %d)", "I2S", I2S_DOUT, I2S_BCLK, I2S_LRC);
  } else {
    BOOTLOG("audio:\t\t%s (%d, %d, %d, %d, %s)", "VS1053", VS1053_CS, VS1053_DCS, VS1053_DREQ, VS1053_RST, VS_HSPI?"true":"false");
  }
  BOOTLOG("audioinfo:\t%s", store.audioinfo?"true":"false");
  BOOTLOG("smartstart:\t%s", store.smartstart ? "true" : "false");
  BOOTLOG("vumeter:\t%s", store.vumeter?"true":"false");
  BOOTLOG("softapdelay:\t%d", store.softapdelay);
  BOOTLOG("flipscreen:\t%s", store.flipscreen?"true":"false");
  BOOTLOG("volumepage:\t%s", store.volumepage?"true":"false");
  BOOTLOG("clock12:\t%s", store.clock12?"true":"false");
  BOOTLOG("invertdisplay:\t%s", store.invertdisplay?"true":"false");
  BOOTLOG("showweather:\t%s", store.showweather?"true":"false");
  BOOTLOG("wifiscanbest:\t%s", store.wifiscanbest?"true":"false");
  BOOTLOG("mqttenable:\t%s", store.mqttenable?"true":"false");
  BOOTLOG("buttons:\tleft=%d, center=%d, right=%d, up=%d, down=%d, mode=%d, pullup=%s", 
          BTN_LEFT, BTN_CENTER, BTN_RIGHT, BTN_UP, BTN_DOWN, BTN_MODE, BTN_INTERNALPULLUP?"true":"false");
  BOOTLOG("encoders:\tl1=%d, b1=%d, r1=%d, pullup=%s, l2=%d, b2=%d, r2=%d, pullup=%s", 
          ENC_BTNL, ENC_BTNB, ENC_BTNR, ENC_INTERNALPULLUP?"true":"false", ENC2_BTNL, ENC2_BTNB, ENC2_BTNR, ENC2_INTERNALPULLUP?"true":"false");
  BOOTLOG("ir:\t\t%d", IR_PIN);
  if (SDC_CS!=255) BOOTLOG("SD:\t%d", SDC_CS);
  #ifdef FIRMWARE
    BOOTLOG("firmware:\t%s", FIRMWARE);
  #endif
  #ifdef UPDATEURL
    BOOTLOG("updateurl:\t%s", UPDATEURL);
  #endif
  BOOTLOG("------------------------------------------------");
}

// Preferences Look-up Table (store_variable, "key_max_15_char")
// Macro expands to 3 fields (offset_of_config_t_store_variable, "key_max_15_char", size_of_store_variable)
const configKeyMap Config::keyMap[] = {
  CONFIG_KEY_ENTRY(config_set, "cfgset"),
  CONFIG_KEY_ENTRY(lastStation, "laststa"),
  CONFIG_KEY_ENTRY(countStation, "countsta"),
  CONFIG_KEY_ENTRY(lastSSID, "lastssid"),
  CONFIG_KEY_ENTRY(lastSdStation, "lastsdsta"),
  CONFIG_KEY_ENTRY(play_mode, "playmode"),
  CONFIG_KEY_ENTRY(volume, "vol"),
  CONFIG_KEY_ENTRY(balance, "bal"),
  CONFIG_KEY_ENTRY(treble, "treb"),
  CONFIG_KEY_ENTRY(middle, "mid"),
  CONFIG_KEY_ENTRY(bass, "bass"),
  CONFIG_KEY_ENTRY(sdshuffle, "sdshuffle"),
  CONFIG_KEY_ENTRY(smartstart, "smartstartx"),
  CONFIG_KEY_ENTRY(audioinfo, "audioinfo"),
  CONFIG_KEY_ENTRY(vumeter, "vumeter"),
  CONFIG_KEY_ENTRY(wifiscanbest, "wifiscan"),
  CONFIG_KEY_ENTRY(softapdelay, "softapdelay"),
  CONFIG_KEY_ENTRY(mdnsname, "mdnsname"),
  CONFIG_KEY_ENTRY(flipscreen, "flipscr"),
  CONFIG_KEY_ENTRY(invertdisplay, "invdisp"),
  CONFIG_KEY_ENTRY(dspon, "dspon"),
  CONFIG_KEY_ENTRY(numplaylist, "numplaylist"),
  CONFIG_KEY_ENTRY(clock12, "clock12"),
  CONFIG_KEY_ENTRY(volumepage, "volpage"),
  CONFIG_KEY_ENTRY(brightness, "bright"),
  CONFIG_KEY_ENTRY(contrast, "contrast"),
  CONFIG_KEY_ENTRY(screensaverEnabled, "scrnsvren"),
  CONFIG_KEY_ENTRY(screensaverTimeout, "scrnsvrto"),
  CONFIG_KEY_ENTRY(screensaverBlank, "scrnsvrbl"),
  CONFIG_KEY_ENTRY(screensaverPlayingEnabled, "scrnsvrplen"),
  CONFIG_KEY_ENTRY(screensaverPlayingTimeout, "scrnsvrplto"),
  CONFIG_KEY_ENTRY(screensaverPlayingBlank, "scrnsvrplbl"),
  CONFIG_KEY_ENTRY(volsteps, "vsteps"),
  CONFIG_KEY_ENTRY(fliptouch, "fliptouch"),
  CONFIG_KEY_ENTRY(dbgtouch, "dbgtouch"),
  CONFIG_KEY_ENTRY(encacc, "encacc"),
  CONFIG_KEY_ENTRY(skipPlaylistUpDown, "skipplupdn"),
  CONFIG_KEY_ENTRY(irtlp, "irtlp"),
  CONFIG_KEY_ENTRY(tz_name, "tzname"),
  CONFIG_KEY_ENTRY(tzposix, "tzposix"),
  CONFIG_KEY_ENTRY(sntp1, "sntp1"),
  CONFIG_KEY_ENTRY(sntp2, "sntp2"),
  CONFIG_KEY_ENTRY(showweather, "showwthr"),
  CONFIG_KEY_ENTRY(weatherlat, "weatherlat"),
  CONFIG_KEY_ENTRY(weatherlon, "weatherlon"),
  CONFIG_KEY_ENTRY(weatherkey, "weatherkey"),
  CONFIG_KEY_ENTRY(mqttenable, "mqttenable"),
  CONFIG_KEY_ENTRY(mqtthost, "mqtthost"),
  CONFIG_KEY_ENTRY(mqttport, "mqttport"),
  CONFIG_KEY_ENTRY(mqttuser, "mqttuser"),
  CONFIG_KEY_ENTRY(mqttpass, "mqttpass"),
  CONFIG_KEY_ENTRY(mqtttopic, "mqtttopic"),
  {0, nullptr, 0} // Yup, 3 fields - don't delete the last line!
};

void Config::deleteOldKeys() {
  // List any old/legacy keys to remove here (they will be deleted from prefs if found)
  prefs.remove("smartstart"); // previous smartstart was numeric 0, 1, 2
  // prefs.remove("removedkey"); // note
}
