#include "Arduino.h"
#include "esp_system.h"

#include "core/options.h"

SET_LOOP_TASK_STACK_SIZE(LOOP_TASK_STACK_SIZE * 1024);

#include "core/config.h"
#include "pluginsManager/pluginsManager.h"
#include "core/telnet.h"
#include "core/player.h"
#include "core/display.h"
#include "core/network.h"
#include <DNSServer.h>
#include "core/netserver.h"
#include "core/controls.h"
#include "core/mqtt.h"
#include "core/optionschecker.h"
#include "core/rgbled.h"
#ifdef USE_NEXTION
#include "displays/nextion.h"
#endif

#if DSP_HSPI || TS_HSPI || VS_HSPI
SPIClass SPI2(HSPI);
#endif

extern __attribute__((weak)) void ehradio_on_setup();

void setup() {
  Serial.begin(115200);
  #if CORE_DEBUG_LEVEL > 0
    if (esp_reset_reason() == ESP_RST_POWERON || esp_reset_reason() == ESP_RST_EXT) { // checking if this is a poweron boot
      delay(1000);
      Serial.println("##[BOOT]#       Delay 1 second after cold boot to ensure serial logs are completely available. Only when CORE_DEBUG_LEVEL > 0.");
    }
  #endif
  if(REAL_LEDBUILTIN!=255) pinMode(REAL_LEDBUILTIN, OUTPUT);
  rgbled_init();
  if (ehradio_on_setup) ehradio_on_setup();
  pm.on_setup();
  config.init();
  display.init();
  player.init();
  if (rgbled_is_initialized()) {
    if (player.isRunning()) rgbled_playing(); else rgbled_stopped();
  }
  network.begin();
  if (network.status != CONNECTED && network.status!=SDREADY) {
    netserver.begin();
    initControls();
    display.putRequest(DSP_START);
    while(!display.ready()) delay(10);
    return;
  }
  if(SDC_CS!=255) {
    display.putRequest(WAITFORSD, 0);
    Serial.print("##[BOOT]#\tSD search\t");
  }
  config.initPlaylistMode();
  netserver.begin();
  telnet.begin();
  initControls();
  display.putRequest(DSP_START);
  while(!display.ready()) delay(10);
  #ifdef MQTT_ENABLE
    if (config.store.mqttenable) mqttInit();
  #endif
  #if LED_INVERT
    if(REAL_LEDBUILTIN!=255) digitalWrite(REAL_LEDBUILTIN, true);
  #endif
  if (config.getMode()==PM_SDCARD) player.initHeaders(config.station.url);
  player.lockOutput=false;
  if (config.store.smartstart) {  // If smart start is enabled
    //delay(99);
    uint16_t stn = config.lastStation();
    if (stn > 0) {  // Only play if there's a valid station
      player.sendCommand({PR_PLAY, stn});
    }
  }
  config.startAsyncServicesButWait();
  pm.on_end_setup();
}

void loop() {
  if (network.status == SOFT_AP) {
    network.loopImprov();
    if (network.dnsServer) network.dnsServer->processNextRequest();
  } else {
    telnet.loop();
  }
  
  rgbled_loop();
  if (network.status == CONNECTED || network.status==SDREADY) {
    player.loop();
  }
  loopControls();
  netserver.loop();
}

#include "core/audiohandlers.h"

/**************************************************************************
*   Plugin BacklightDown.
*   Ver.1.0 (Maleksm) for ёРадио 20.12.2024
*   Ver.1.1 (Trip5) 2025.07.19
*   Ver.1.2 (Kasperaitis/Trip5) 2026.02.01
***************************************************************************/
#if (BRIGHTNESS_PIN!=255) && (defined(DOWN_LEVEL) || defined(DOWN_INTERVAL))
#include <Ticker.h>

/* Основные константы настроек */
#ifdef DOWN_LEVEL
  const uint8_t brightness_down_level = DOWN_LEVEL;
#else
  const uint8_t brightness_down_level = 2;   /* lowest level brightness (from 0 to 255) */
#endif
#ifdef DOWN_INTERVAL
  const uint16_t Out_Interval = DOWN_INTERVAL;
#else
  const uint16_t Out_Interval = 60;         /* interval for BacklightDown in sec (60 sec = 1 min) */
#endif

  Ticker backlightTicker;
  Ticker rampTicker;
  uint8_t current_brightness;

  void stepBacklight() {
    if (current_brightness > brightness_down_level) {
      current_brightness -= 2;
      if (current_brightness < brightness_down_level) current_brightness = brightness_down_level;
      analogWrite(BRIGHTNESS_PIN, current_brightness);
    } else {
      rampTicker.detach();
    }
  }

  void backlightDown() {
    if (network.status != SOFT_AP) {
      backlightTicker.detach();
      current_brightness = map(config.store.brightness, 0, 100, 0, 255);
      rampTicker.attach_ms(30, stepBacklight);
    }
  }

  void brightnessOn() {
    backlightTicker.detach();
    rampTicker.detach();
    analogWrite(BRIGHTNESS_PIN, map(config.store.brightness, 0, 100, 0, 255));
    backlightTicker.attach(Out_Interval, backlightDown);
  }

  /* Backlight callback functions were here; moved below to ensure RGB callbacks are available even when backlight plugin isn't enabled */
  void ctrls_on_loop() {                            /* Backlight ON for reg. operations */
    if (!config.isScreensaver) {
      static uint32_t prevBlPinMillis;
      if ((display.mode() != PLAYER) && (millis() - prevBlPinMillis > 1000)) {
        prevBlPinMillis = millis();
        brightnessOn();
      }
    }
  }
#else  /*  #if BRIGHTNESS_PIN!=255 */
  void brightnessOn() { } /* No-op stub */
#endif

// Call rgbled loop from main loop too (no-op if not enabled)
void rgbled_loop_caller() {
  rgbled_loop();
}

void ehradio_on_setup() {
  rgbled_init();
  brightnessOn();
}

void player_on_track_change() {
  rgbled_trackchange();
  brightnessOn();
}

void player_on_start_play() {
  rgbled_playing();
  brightnessOn();
}

void player_on_stop_play() {
  rgbled_stopped();
  brightnessOn();
}


