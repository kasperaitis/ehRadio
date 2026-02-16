#ifndef netserver_h
#define netserver_h

#include <ESPAsyncWebServer.h>
#include "../displays/widgets/widgetsconfig.h"

enum requestType_e : uint8_t  { PLAYLIST=1, STATION=2, STATIONNAME=3, ITEM=4, TITLE=5, VOLUME=6, NRSSI=7, BITRATE=8, MODE=9, EQUALIZER=10, BALANCE=11, PLAYLISTSAVED=12, STARTUP=13, GETINDEX=14, GETACTIVE=15, GETSYSTEM=16, GETSCREEN=17, GETTIMEZONE=18, GETWEATHER=19, GETCONTROLS=20, DSPON=21, SDPOS=22, SDLEN=23, SDSHUFFLE=24, SDINIT=25, GETPLAYERMODE=26, CHANGEMODE=27, SEARCH_DONE=28, SEARCH_FAILED=29, GETMQTT=30, GETBATTERY=31 }; 
enum import_e      : uint8_t  { IMDONE=0, IMPL=1, IMWIFI=2 };
const char emptyfs_html[] PROGMEM = R"(
<!DOCTYPE html><html><head><meta name="viewport" content="width=device-width, initial-scale=1, minimum-scale=0.25"><meta charset="UTF-8">
<link rel="icon" type="image/png" href="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAABABAMAAABYR2ztAAAAAXNSR0IB2cksfwAAAAlwSFlzAAAOxAAADsQBlSsOGwAAAB5QTFRFyAwCAAAAyAwCyAwCyAwCyAwCyAwCyAwCyAwCyAwCS0TDwgAAAAp0Uk5T/wAM4Cq8mkZ/ZYZ9vz0AAAIWSURBVHichZXBb9MwFMY/YZLC0W5puluddWp2i9YWbbdFSidxC9uoOLYDUe22DoTgloGQdmTAhf8W20ldk9nOu9S1f+p73/eeXdBGJI3vaALfMz/A0js/EOHIDwzQ8QMvEPqBUxDuBZbAxgf0UmDlA/oAzn3AjQA6PqAUQOgC9kT5hQACseY2oH/JGWRwGk1twIC8HVXA6PeVDYgAooD7wvDCAHrYRWYDWGEF+u/1+kafPzdk9sj1VtNSAzuvYojtk/pLqQHtVTSDaDDqLKcaeFpXdZaGECMCslZZ9jXwugLOUkwhhkyEmtShBlRD2WexeqiBDvtjAk8kMJd94VAjAHIoWtQ1U8QsVXprABe4lNXUsaGHs4NKL+hevUk2GiBcuFpUckATLX6ugfijdgyGwalevdkZAkO9JaSKgQ9ABjkn7ghFCpZ6gE4bcCSBwgOs5Mj9bAOG7nPxFMAcxUfxjBq9sEUgf8Hrw7QlhZJJI7cRQaZu1oETOK+unrOKY14BTi+/bS9vcmGvgOvb3bPVObsyrr8tyS3fAqP8i+W8fpLB8q+OGl9+WEgVS4eCqozrWyS+gRIzB/rKN1HBL1lk4jqeLKpesNJ+TuLaarpPJhNLKVNt1PhTnsupIJNFefxDoeG7WboyH1JWBn/Xecy7d9K3RTpl2ZibAI0r47oP6mO81g8p/T+Gm8bGo7/FViBrAea8sfEPiURzVU+EBKkAAAAASUVORK5CYII=">
<title>ehRadio - WEB Board Uploader</title><style>html, body{margin: 0; padding: 0; height: 100%; background-color:#000;color:#eecccc;font-size:20px;display:flex;flex-direction:column;}
hr{margin:20px 0;border:0; border-top:#555 1px solid;} p{text-align:center;margin-bottom:10px;} section{max-width:500px; text-align:center;margin:0 auto 30px auto;padding:20px;flex:1;}
.hidden{display:none;} a{color: #ccccee; font-size:14px; text-decoration: none; font-weight: bold;} a:hover{text-decoration: underline}
#copy{text-align: center; padding: 14px; font-size: 14px;}
input[type=file]{color:#ccc;} input[type=file]::file-selector-button, input[type=submit]{border:2px solid #eecccc;color:#000;padding:6px 16px;border-radius:25px;background-color:#eecccc;margin:0 6px;cursor:pointer;}
input[type=submit]{font-size:18px;text-transform:uppercase;padding:8px 26px;margin-top:10px;font-family:Times;} span{color:#ccc} .flex{display:flex;justify-content: space-around;margin-top:10px;}
input[type=text],input[type=password]{width:170px;background:#272727;color:#eecccc;padding:6px 12px;font-size:20px;border:#2d2d2d 1px solid;margin:4px 0 0 4px;border-radius:4px;outline:none;}
@media screen and (max-width:480px) {section{zoom:0.7;-moz-transform:scale(0.7);}}
</style>
<script type="text/javascript" src="/variables.js"></script>
</head><body>
<section>
<div id="uploader">
<h2>ehRadio - WEB Board Uploader</h2>
<hr />
<span>Select <u>ALL</u> files from <i>data/www/</i><br />and upload them using the form below</span>
<hr />
<form action="/webboard" method="post" enctype="multipart/form-data">
<p><label for="www">www:</label> <input type="file" name="www" id="www" multiple></p>
<hr />
<span>= OPTIONAL =<br />You can also upload <i>playlist.csv</i><br />and <i>wifi.csv files</i> from your backup</span>
<p><label for="data">wifi:</label><input type="file" name="data" id="data" multiple></p>
<hr />
<p><input type="submit" name="submit" value="Upload Files"></p>
</form>
</div>
<div style="padding:10px 0 0;" id="wupload">
<div id="credtitle-x">
<hr />
<span>= OPTIONAL =<br />If you can't connect from PC to 192.168.4.1 address<br />setup WiFi connection first!</span>
</div>
<div id="credtitle" class="hidden">
<h2>ehRadio - Credentials</h2>
<hr />
</div>
<form name="wifiform" method="post" enctype="multipart/form-data">
<div class="flex"><div><label for="ssid">ssid:</label><input type="text" id="ssid" name="ssid" value="" maxlength="30" autocomplete="off"></div>
<div><label for="pass">pass:</label><input type="password" id="pass" name="pass" value="" maxlength="40" autocomplete="off"></div>
</div>
<p><input type="submit" name="submit" value="Save Credentials"></p>
</form>
</div>
<div id="downloader" class="hidden">
<h2>ehRadio - WEB Board Downloader</h2>
<hr />
<span>The WebUI files are currently downloading. Please wait a few moments. The device will restart and this page will reload when everything is ready.</span>
<hr />
</div>
</section>
<p><a href="/emergency">emergency firmware uploader</a></p>
<div id="copy">powered by <a target="_blank" href="https://github.com/trip5/ehRadio/">ehRadio</a> | <span id="version"></span></div>
</body>
<script>
document.wifiform.action = `/${formAction}`;
if (playMode === 'player') {
document.getElementById("wupload").classList.add("hidden");
if (onlineupdatecapable) {
document.getElementById('downloader').classList.remove("hidden");
document.getElementById('uploader').classList.add("hidden");
setTimeout(() => { window.location.reload(true); }, 10000);
}
} else if (onlineupdatecapable) {
document.getElementById('credtitle').classList.remove("hidden");
document.getElementById('credtitle-x').classList.add("hidden");
document.getElementById('uploader').classList.add("hidden");
}
document.getElementById("version").innerHTML=`${radioVersion}`;
</script>
</html>
)";
const char index_html[] PROGMEM = R"(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no">
  <meta name="theme-color" content="#eecccc">
  <meta name="apple-mobile-web-app-capable" content="yes">
  <meta name="apple-mobile-web-app-status-bar-style" content="default">
  <link rel="icon" type="image/png" href="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAABABAMAAABYR2ztAAAAAXNSR0IB2cksfwAAAAlwSFlzAAAOxAAADsQBlSsOGwAAAB5QTFRFyAwCAAAAyAwCyAwCyAwCyAwCyAwCyAwCyAwCyAwCS0TDwgAAAAp0Uk5T/wAM4Cq8mkZ/ZYZ9vz0AAAIWSURBVHichZXBb9MwFMY/YZLC0W5puluddWp2i9YWbbdFSidxC9uoOLYDUe22DoTgloGQdmTAhf8W20ldk9nOu9S1f+p73/eeXdBGJI3vaALfMz/A0js/EOHIDwzQ8QMvEPqBUxDuBZbAxgf0UmDlA/oAzn3AjQA6PqAUQOgC9kT5hQACseY2oH/JGWRwGk1twIC8HVXA6PeVDYgAooD7wvDCAHrYRWYDWGEF+u/1+kafPzdk9sj1VtNSAzuvYojtk/pLqQHtVTSDaDDqLKcaeFpXdZaGECMCslZZ9jXwugLOUkwhhkyEmtShBlRD2WexeqiBDvtjAk8kMJd94VAjAHIoWtQ1U8QsVXprABe4lNXUsaGHs4NKL+hevUk2GiBcuFpUckATLX6ugfijdgyGwalevdkZAkO9JaSKgQ9ABjkn7ghFCpZ6gE4bcCSBwgOs5Mj9bAOG7nPxFMAcxUfxjBq9sEUgf8Hrw7QlhZJJI7cRQaZu1oETOK+unrOKY14BTi+/bS9vcmGvgOvb3bPVObsyrr8tyS3fAqP8i+W8fpLB8q+OGl9+WEgVS4eCqozrWyS+gRIzB/rKN1HBL1lk4jqeLKpesNJ+TuLaarpPJhNLKVNt1PhTnsupIJNFefxDoeG7WboyH1JWBn/Xecy7d9K3RTpl2ZibAI0r47oP6mO81g8p/T+Gm8bGo7/FViBrAea8sfEPiURzVU+EBKkAAAAASUVORK5CYII=">
  <link rel="stylesheet" href="theme.css" type="text/css" />
  <link rel="stylesheet" href="style.css" type="text/css" />
  <script type="text/javascript" src="variables.js"></script>
  <script type="text/javascript" src="script.js"></script>
  <script type="text/javascript" src="dragpl.js"></script>
  </head>
<body>
<div id="content" class="hidden progmem"></div><!--content--><div id="progress"><span id="loader"></span></div>
</body>
</html>
)";
const char emergency_form[] PROGMEM = R"(
<form method="POST" action="/update" enctype="multipart/form-data">
  <input type="hidden" name="updatetarget" value="fw" />
  <label for="uploadfile">upload firmware</label>
  <input type="file" id="uploadfile" accept=".bin,.hex" name="update" />
  <input type="submit" value="Update" />
</form>
)";
struct nsRequestParams_t
{
  requestType_e type;
  uint8_t clientId;
};

void mqttplaylistSend();
char* updateError();
void handleSearch(AsyncWebServerRequest *request);
void handleSearchPost(AsyncWebServerRequest *request);
const char *getFormat(BitrateFormat _format);
void handleUpload(AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final);
void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);
void selectRadioBrowserServer();
void vTaskSearchRadioBrowser(void *pvParameters);
void launchPlaybackTask(const String& url, const String& name);
void radioBrowserSendClick(const char* stationUrl);
void processRadioBrowserClick();
void checkForOnlineUpdate();
void startOnlineUpdate();
void handleNotFound(AsyncWebServerRequest * request);
void handleIndex(AsyncWebServerRequest * request);

class NetServer {
  public:
    import_e importRequest = IMDONE;
    bool resumePlay = false;
    char chunkedPathBuffer[40] = {0};
    bool irRecordEnable = false;
    String newVersion = String(RADIOVERSION);
    bool newVersionAvailable = false;
  public:
    NetServer() {};
    bool begin(bool quiet=false);
    void chunkedHtmlPage(const String& contentType, AsyncWebServerRequest *request, const char * path);
    void loop();
    void irToWs(const char* protocol, uint64_t irvalue);
    void irValsToWs();
    void onWsMessage(void *arg, uint8_t *data, size_t len, uint8_t clientId);
    void requestOnChange(requestType_e request, uint8_t clientId);
    void resetQueue();

    void setRSSI(int val) { rssi = val; };
    int  getRSSI()        { return rssi; };
  private:
    requestType_e request = PLAYLIST;
    QueueHandle_t nsQueue;
    int rssi = 0;

    static size_t chunkedHtmlPageCallback(uint8_t* buffer, size_t maxLen, size_t index);
    void processQueue();
    void getPlaylist(uint8_t clientId);
    int _readPlaylistLine(File &file, char * line, size_t size);
    bool importPlaylist();
};

extern NetServer netserver;
extern AsyncWebSocket websocket;

#endif
