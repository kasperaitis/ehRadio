#ifndef network_h
#define network_h
#include <Ticker.h>
#include <WiFi.h>
#include <DNSServer.h>
#include <ImprovWiFiLibrary.h>

//#define TSYNC_DELAY 10800000    // 1000*60*60*3 = 3 hours
#define TSYNC_DELAY       3600000     // 1000*60*60   = 1 hour
#define WEATHER_STRING_L  254

enum n_Status_e { CONNECTED, SOFT_AP, FAILED, SDREADY };

class MyNetwork {
  public:
    n_Status_e status = FAILED;
// Ensure DNSServer full definition is available
    struct tm timeinfo = {0};
    bool firstRun = true, forceTimeSync = true, forceWeather = true;
    bool lostPlaying = false, beginReconnect = false;
    //uint8_t tsFailCnt, wsFailCnt;
    Ticker ctimer;
    char *weatherBuf = nullptr;
    bool trueWeather = false;
    DNSServer* dnsServer = nullptr;
    ImprovWiFi *improv = nullptr;
  public:
    MyNetwork() : improv(nullptr) {};
    bool wifiBegin(bool silent=false);
    void begin();
    void loopImprov();
    void setWifiParams();
    void requestTimeSync(bool withTelnetOutput=false, uint8_t clientId=0);
    void raiseSoftAP();
    void requestWeatherSync();
  private:
    Ticker rtimer;
    unsigned long lastImprovBroadcast = 0;
    static void WiFiReconnected(WiFiEvent_t event, WiFiEventInfo_t info);
    static void WiFiLostConnection(WiFiEvent_t event, WiFiEventInfo_t info);
};

extern MyNetwork network;

extern __attribute__((weak)) void network_on_connect();

#endif
