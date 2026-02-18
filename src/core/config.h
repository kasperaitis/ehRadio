#ifndef config_h
#define config_h
#pragma once
#include <Arduino.h>
#include <Ticker.h>
#include <SPI.h>
#include <SPIFFS.h>
#include <Preferences.h>
#include "../displays/widgets/widgetsconfig.h"

#define ESPFILEUPDATER_USERAGENT "ehradio/" RADIOVERSION "(" GITHUBURL ")"  // used as a user-agent string for downloading with ESPFileUpdater
#ifdef ESPFILEUPDATER_DEBUG
  #define ESPFILEUPDATER_VERBOSE true
#else
  #define ESPFILEUPDATER_VERBOSE false
#endif

#define PLAYLIST_PATH     "/data/playlist.csv"
#define SSIDS_PATH        "/data/wifi.csv"
#define TMP_PATH          "/data/tmpfile.txt"
#define TMP2_PATH         "/data/tmpfile2.txt"
#define INDEX_PATH        "/data/index.dat"
#define PLAYLIST_SD_PATH  "/data/playlistsd.csv"
#define INDEX_SD_PATH     "/data/indexsd.dat"
#define REAL_PLAYL   config.getMode()==PM_WEB?PLAYLIST_PATH:PLAYLIST_SD_PATH
#define REAL_INDEX   config.getMode()==PM_WEB?INDEX_PATH:INDEX_SD_PATH

#define MAX_PLAY_MODE   1
#define WEATHERKEY_LENGTH 58
#define MDNS_LENGTH 24

#if ESP_ARDUINO_VERSION >= ESP_ARDUINO_VERSION_VAL(3, 0, 0)
  #define ESP_ARDUINO_3 1
#endif

enum playMode_e      : uint8_t  { PM_WEB=0, PM_SDCARD=1 };

void u8fix(char *src);
void cleanStaleSearchResults();
void fixPlaylistFileEnding();
void getRequiredFiles(void* param);
void checkNewVersionFile();
void startAsyncServices(void* param);

struct theme_t {
  uint16_t background;
  uint16_t meta;
  uint16_t metabg;
  uint16_t metafill;
  uint16_t title1;
  uint16_t title2;
  uint16_t digit;
  uint16_t div;
  uint16_t weather;
  uint16_t vumax;
  uint16_t vumin;
  uint16_t clock;
  uint16_t clockbg;
  uint16_t seconds;
  uint16_t dow;
  uint16_t date;
  uint16_t heap;
  uint16_t buffer;
  uint16_t ip;
  uint16_t vol;
  uint16_t rssi;
  uint16_t bitrate;
  uint16_t volbarout;
  uint16_t volbarin;
  uint16_t plcurrent;
  uint16_t plcurrentbg;
  uint16_t plcurrentfill;
  uint16_t playlist[5];
};
struct config_t // specify defaults here (and macros in options.h) (defaults are NOT saved to Prefs)
{
  uint16_t  config_set = 4262;
  uint16_t  lastStation = 0;
  uint16_t  countStation = 0;
  uint8_t   lastSSID = 0;
  uint16_t  lastSdStation = 0;
  uint8_t   play_mode = 0;
  uint8_t   volume = SOUND_VOLUME;
  int8_t    balance = SOUND_BALANCE;
  int8_t    treble = EQ_TREBLE;
  int8_t    middle = EQ_MIDDLE;
  int8_t    bass = EQ_BASS;
  bool      sdshuffle = SD_SHUFFLE;
  bool      smartstart = SMART_START;
  bool      autoupdate = false;
  bool      audioinfo = SHOW_AUDIO_INFO;
  bool      vumeter = SHOW_VU_METER;
  bool      wifiscanbest = WIFI_SCAN_BEST_RSSI;
  uint8_t   softapdelay = SOFTAP_REBOOT_DELAY;
  char      mdnsname[24] = "";
  bool      flipscreen = SCREEN_FLIP;
  bool      invertdisplay = SCREEN_INVERT;
  bool      dspon = true;
  bool      numplaylist = NUMBERED_PLAYLIST;
  bool      clock12 = CLOCK_TWELVE;
  bool      volumepage = VOLUME_PAGE;
  uint8_t   brightness = SCREEN_BRIGHTNESS;
  uint8_t   contrast = SCREEN_CONTRAST;
  bool      screensaverEnabled = SS_NOTPLAYING;
  bool      screensaverBlank = SS_NOTPLAYING_BLANK;
  uint16_t  screensaverTimeout = SS_NOTPLAYING_TIME;
  bool      screensaverPlayingEnabled = SS_PLAYING;
  bool      screensaverPlayingBlank = SS_PLAYING_BLANK;
  uint16_t  screensaverPlayingTimeout = SS_PLAYING_TIME;
  uint8_t   volsteps = VOLUME_STEPS;
  bool      fliptouch = TOUCH_FLIP;
  bool      dbgtouch = TOUCH_DEBUG;
  uint16_t  encacc = ROTARY_ACCEL;
  // Battery ADC calibration reference (in mV). Set via 'calbatt <mV>' (saves immediately) or override in myoptions.h
  uint16_t  battery_adc_ref_mv = BATTERY_ADC_REF_MV;
  bool      skipPlaylistUpDown = ONE_CLICK_SWITCH;
  uint8_t   irtlp = IR_TOLERANCE;
  char      tz_name[70] = TIMEZONE_NAME;
  char      tzposix[70] = TIMEZONE_POSIX;
  char      sntp1[35] = SNTP_1;
  char      sntp2[35] = SNTP_2;
  bool      showweather = false;
  char      weatherlat[10] = WEATHER_LAT;
  char      weatherlon[10] = WEATHER_LON;
  char      weatherkey[WEATHERKEY_LENGTH] = "";
  bool      mqttenable = false;
  char      mqtthost[60] = MQTT_HOST;
  uint16_t  mqttport = MQTT_PORT;
  char      mqttuser[30] = MQTT_USER;
  char      mqttpass[40] = MQTT_PASS;
  char      mqtttopic[60] = MQTT_TOPIC;

  // if adding a variable, you can do it anywhere, just be sure to add it to configKeyMap() in config.cpp
  // if removing a variable and key, add to deleteOldKeys()
  // note that defaults are mostly built from macros, except a few which are disabled by default
};

#define CONFIG_KEY_ENTRY(field, keyname) { offsetof(config_t, field), keyname, sizeof(((config_t*)0)->field) }

struct configKeyMap {
    size_t fieldOffset;
    const char* key;
    size_t size;
};

#if IR_PIN!=255
  struct ircodes_t
  {
    unsigned int ir_set = 0; // will be 4224 if written/restored correctly
    uint64_t irVals[20][3];
  };
#endif

struct station_t
{
  char name[BUFLEN];
  char url[BUFLEN];
  char title[BUFLEN];
  uint16_t bitrate;
  int  ovol;
};

struct neworkItem
{
  char ssid[30];
  char password[40];
};

class Config {
  public:
    config_t store;
    station_t station;
    theme_t   theme;

    #if IR_PIN!=255
      int irindex = -1;
      uint8_t irchck = 0;
      ircodes_t ircodes;
    #endif

    BitrateFormat configFmt = BF_UNKNOWN;
    neworkItem ssids[5];
    uint8_t ssidsCount = 0;
    uint16_t sleepfor = 0;
    uint32_t sdResumePos = 0;
    bool     wwwFilesExist = false;
    uint16_t vuThreshold = 0;
    uint16_t screensaverTicks = 0;
    uint16_t screensaverPlayingTicks = 0;
    bool     isScreensaver = false;
    int      newConfigMode = 0;
    char       ipBuf[16] = {0};

    void init();
    void loadPreferences();
    void changeMode(int newmode=-1);
    void initSDPlaylist();
    bool spiffsCleanup();
    char * ipToStr(IPAddress ip);
    void initPlaylistMode();
    void loadTheme();
    void reset();
    void enableScreensaver(bool val);
    void setScreensaverTimeout(uint16_t val);
    void setScreensaverBlank(bool val);
    void setScreensaverPlayingEnabled(bool val);
    void setScreensaverPlayingTimeout(uint16_t val);
    void setScreensaverPlayingBlank(bool val);
    void setShowweather(bool val);
    void setWeatherKey(const char *val);
    void setSDpos(uint32_t val);
    void setIrBtn(int val);
    void saveIR();
    void resetSystem(const char *val, uint8_t clientId);
    void setShuffle(bool sn);
    void saveVolume();
    uint8_t setVolume(uint8_t val);
    void setTone(int8_t bass, int8_t middle, int8_t treble);
    void setSmartStart(bool ss);
    void setBalance(int8_t balance);
    uint8_t setLastStation(uint16_t val);
    uint8_t setCountStation(uint16_t val);
    uint8_t setLastSSID(uint8_t val);
    void setTitle(const char* title);
    void setStation(const char* station);
    void indexPlaylist();
    void initPlaylist();
    uint16_t playlistLength();
    bool loadStation(uint16_t station);
    char * stationByNum(uint16_t num);
    void escapeQuotes(const char* input, char* output, size_t maxLen);
    bool parseCSV(const char* line, char* name, char* url, int &ovol);
    bool parseWsCommand(const char* line, char* cmd, char* val, uint8_t cSize);
    bool parseSsid(const char* line, char* ssid, char* pass);
    bool saveWifi(const char* post);
    bool addSsid(const char* ssid, const char* password);
    bool importWifi();
    bool initNetwork();
    void setBrightness(bool dosave=false);
    void setDspOn(bool dspon, bool saveval = true);
    void doSleepW();
    void sleepForAfter(uint16_t sleepfor, uint16_t sa=0);
    void purgeUnwantedFiles();
    void deleteMainwwwFile();
    void updateFile(void* param, const char* localFile, const char* onlineFile, const char* updatePeriod, const char* simpleName);
    void startAsyncServicesButWait();
    void bootInfo();
    void deleteOldKeys();
    void setBitrateFormat(BitrateFormat fmt) { configFmt = fmt; }
    uint16_t lastStation() {
      return getMode()==PM_WEB?store.lastStation:store.lastSdStation;
    }
    void lastStation(uint16_t newstation) {
      if (getMode()==PM_WEB) saveValue(&store.lastStation, newstation);
      else saveValue(&store.lastSdStation, newstation);
    }
    uint8_t getMode() { return store.play_mode; }
    FS* SDPLFS() { return _SDplaylistFS; }
    bool isRTCFound() { return _rtcFound; };
    Preferences prefs; // For Preferences, we use a look-up table to maintain compatibility...
    static const configKeyMap keyMap[];

    // Helper to get key map entry for a field pointer
    const configKeyMap* getKeyMapEntryForField(const void* field) const {
        size_t offset = (const uint8_t*)field - (const uint8_t*)&store;
        for (size_t i = 0; keyMap[i].key != nullptr; ++i) {
            if (keyMap[i].fieldOffset == offset) return &keyMap[i];
        }
        return nullptr;
    }
    template <typename T>
    void loadValue(T *field) {
      const configKeyMap* entry = getKeyMapEntryForField(field);
      if (entry) prefs.getBytes(entry->key, field, entry->size);
    }
    template <typename T>
    void saveValue(T *field, const T &value, bool commit=true, bool force=false) {
      // commit ignored (kept for compatibility)
      const configKeyMap* entry = getKeyMapEntryForField(field);
      if (entry) {
        prefs.begin("ehradio", false);
        T oldValue;
        size_t existingLen = prefs.getBytesLength(entry->key);
        size_t bytesRead = prefs.getBytes(entry->key, &oldValue, entry->size);
        bool exists = bytesRead == entry->size;
        bool needSave = (existingLen != entry->size) || !exists || memcmp(&oldValue, &value, entry->size) != 0;
        if (needSave) {
          prefs.putBytes(entry->key, &value, entry->size);
          *field = value;
        }
        prefs.end();
      }
    }
    void saveValue(char *field, const char *value, size_t N = 0, bool commit=true, bool force=false) {
      // commit ignored (kept for compatibility)
      const configKeyMap* entry = getKeyMapEntryForField(field);
      if (entry) {
        size_t sz = entry->size;
        prefs.begin("ehradio", false);
        char oldValue[sz];
        memset(oldValue, 0, sz);
        size_t existingLen = prefs.getBytesLength(entry->key);
        bool exists = prefs.getBytes(entry->key, oldValue, sz) == sz;
        bool needSave = (existingLen != sz) || !exists || strncmp(oldValue, value, sz) != 0 || force;
        if (needSave) {
          prefs.putBytes(entry->key, value, sz);
          strlcpy(field, value, sz);
        }
        prefs.end();
      }
    }
    uint32_t getChipId() {
      uint32_t chipId = 0;
      for(int i=0; i<17; i=i+8) {
        chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
      }
      return chipId;
    }

  private:
    bool _bootDone = false;
    bool _rtcFound = false;
    FS* _SDplaylistFS = nullptr;
    Ticker   _sleepTimer;

    bool _wwwFilesExist();
    void _initHW();
    uint16_t color565(uint8_t r, uint8_t g, uint8_t b);
    void setDefaults();
    static void doSleep();

    uint16_t _randomStation() {
      randomSeed(esp_random() ^ millis());
      uint16_t station = random(1, store.countStation);
      return station;
    }
    char _stationBuf[BUFLEN/2];
};

extern Config config;

#if DSP_HSPI || TS_HSPI || VS_HSPI
  extern SPIClass  SPI2;
#endif

#endif
