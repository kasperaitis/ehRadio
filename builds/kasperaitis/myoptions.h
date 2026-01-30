#ifndef myoptions_h
#define myoptions_h

/* - - - = = = - - - Choose the Radio (defined by platformio.ini env) - - - = = = - - - */
/* automatic builds define the board - - - be sure to comment all lines after debugging */

//#define DEBUG_MYOPTIONS                              // uncomment to debug myoptions.h -- and uncomment one option below!
//#define ESP32_S3_TRIP5_SH1106_PCM_REMOTE             // Self-contained OLED with PCM, Remote
//#define ESP32_S3_TRIP5_SH1106_PCM_1BUTTON            // Mini OLED with PCM, 1 Button, Speakers built-in
//#define ESP32_S3_TRIP5_SSD1306X32_PCM_1BUTTON        // Mini Tiny OLED with PCM, 1 Button, Speakers built-in
//#define ESP32_S3_TRIP5_SH1106_VS1053_3BUTTONS        // Ali Speaker with OLED, VS1053, 3 Buttons
//#define ESP32_S3_TRIP5_ST7735_PCM_1BUTTON            // Color TFT (red board) with PCM I2S, 1 Button
//#define ESP32_S3_TRIP5_ILI9488_PCM_1BUTTON           // Big Screen with PCM, 1 button

/* --- FIRMWARE FILENAME & BOARD --- */

#if defined(BOARD_ESP32) & not defined(DEBUG_MYOPTIONS)
#undef FIRMWARE
#define FIRMWARE "board_esp32.bin"
//#undef UPDATEURL // if an ESP does not have the memory to do online updates from https sources (this will disable it)
#elif defined(BOARD_ESP32_S3_N16R8)
#undef FIRMWARE
#define FIRMWARE "board_esp32_s3_n16r8.bin"
#define ARDUINO_ESP32S3_DEV
#elif defined(ESP32_S3_ES3C28P)
#undef FIRMWARE
#define FIRMWARE "esp32_s3_esc3c28p.bin"
#define ARDUINO_ESP32S3_DEV
#elif defined(ESP32_S3_TRIP5_SH1106_PCM_REMOTE)
#undef FIRMWARE
#define FIRMWARE "esp32_s3_trip5_sh1106_pcm_remote.bin"
#define ARDUINO_ESP32S3_DEV
#elif defined(ESP32_S3_TRIP5_SH1106_PCM_1BUTTON)
#undef FIRMWARE
#define FIRMWARE "esp32_s3_trip5_sh1106_pcm_1button.bin"
#define ARDUINO_ESP32S3_DEV
#elif defined(ESP32_S3_TRIP5_SSD1306X32_PCM_1BUTTON)
#undef FIRMWARE
#define FIRMWARE "esp32_s3_trip5_ssd1306x32_pcm_1button.bin"
#define ARDUINO_ESP32S3_DEV
#elif defined(ESP32_S3_TRIP5_SH1106_VS1053_3BUTTONS)
#undef FIRMWARE
#define FIRMWARE "esp32_s3_trip5_sh1106_vs1053_3buttons.bin"
#define ARDUINO_ESP32S3_DEV
#elif defined(ESP32_S3_TRIP5_ST7735_PCM_1BUTTON)
#undef FIRMWARE
#define FIRMWARE "esp32_s3_trip5_st7735_pcm_1button.bin"
#define ARDUINO_ESP32S3_DEV
#elif defined(ESP32_S3_TRIP5_ILI9488_PCM_1BUTTON)
#undef FIRMWARE
#define FIRMWARE "esp32_s3_trip5_ili9488_pcm_1button.bin"
#define ARDUINO_ESP32S3_DEV
#endif


/* --- LED --- */

#if defined(BOARD_ESP32)
#define USE_BUILTIN_LED     true
#else
#define USE_BUILTIN_LED     false   /* usually...! Unless you actually want to use the builtin as defined by the board's .h file */
#endif

#if defined(ESP32_S3_TRIP5_SH1106_PCM_REMOTE)
#define LED_BUILTIN_S3      8
#define LED_INVERT          true
#elif defined(ESP32_S3_ES3C28P)
/* Enable single-pin RGB LED (WS2812 style) on ES3C28P boards */
#define USE_RGB_LED     true
#ifndef RGB_LED_PIN
  #define RGB_LED_PIN   42
#endif
#ifndef RGB_LED_ORDER
  #define RGB_LED_ORDER GRB
#endif
#elif defined(BOARD_ESP32_S3_N16R8)
//#define LED_BUILTIN         48          /* S3 RGB LED probably default in board def 48 */
#else
/* LED config for all others - keep it off */
#define LED_BUILTIN_S3      255
#endif


/* --- DISPLAY --- */

#if defined(ESP32_S3_ES3C28P)
#define DSP_MODEL       DSP_ILI9341
#define PRINT_FIX
#define SCREEN_INVERT true
#define TFT_CS          10
#define TFT_DC          46
#define TFT_RST         -1
#define TFT_BL          45
//#define GFX_BL          45
// SPI pins for the TFT module (ES3C28P)
#define TFT_MOSI        11
#define TFT_SCLK        12
#define TFT_MISO        13
#define BRIGHTNESS_PIN  TFT_BL
#endif

#if defined(ESP32_S3_TRIP5_SH1106_PCM_REMOTE) || defined(ESP32_S3_TRIP5_SH1106_PCM_1BUTTON) ||\
    defined(ESP32_S3_TRIP5_SH1106_VS1053_3BUTTONS)
#define DSP_MODEL       DSP_SH1106      /* Regular OLED - platformio.ini */
#define PRINT_FIX
#define I2C_SDA         42
#define I2C_SCL         41
#endif

#if defined(ESP32_S3_TRIP5_SSD1306X32_PCM_1BUTTON)
#define DSP_MODEL       DSP_SSD1306x32  /* Tiny OLED */
#define PRINT_FIX
#define I2C_SDA         42
#define I2C_SCL         41
#endif

/* Display config for SPI displays (pick one) */
/* When using SPI Displays, trying to use same SPI MOSI, SCK, MISO as VS1053 doesn't work */
#if defined(ESP32_S3_TRIP5_ILI9488_PCM_1BUTTON)
#define DSP_MODEL       DSP_ILI9488     /* Big Display */
#define PRINT_FIX
#define BIG_BOOT_LOGO
#define SCREEN_INVERT true
#define TFT_DC          10
#define TFT_CS          9
#define BRIGHTNESS_PIN  4
#define TFT_RST         -1      /* set to -1 if connected to ESP EN pin */
#define DOWN_LEVEL      63      /* Maleksm's mod: brightness level 0 to 255, default 2 */
#define DOWN_INTERVAL   120     /* Maleksm's mod: seconds to dim, default 60 = 60 seconds */
/* modify src\displays\displayILI9488.cpp -- in section DspCore::initDisplay and add setRotation(3); to do 180 degree rotation */
#endif

#if defined(ESP32_S3_TRIP5_ST7735_PCM_1BUTTON)
#define DSP_MODEL       DSP_ST7735          /* Red board / 1.8" Black Tab, if problems try one of DTYPE */
/* DSP_ST7735 DTYPES BELOW (add if needed but so far, not needed)*/
//#define DTYPE           INITR_GREENTAB      /* add for Green Tab */
//#define DTYPE           INITR_REDTAB        /* add for Red Tab */
//#define DTYPE           INITR_144GREENTAB   /* add for 1.44" Green Tab */
//#define DTYPE           INITR_MINI160x80    /* add for 0.96" Mini 160x80 */
#define PRINT_FIX
#define TFT_DC          10
#define TFT_CS          9
#define BRIGHTNESS_PIN  4       /* Red Smaller TFT doesn't have brightness control so leave commented? use unused pin? or 255? */
#define TFT_RST         -1      /* set to -1 if connected to ESP EN pin */
#endif

/* --- TOUCH --- */

#if defined(ESP32_S3_ES3C28P)
// For some ES3C28P boards the touch controller may be D-FT6336G family — set to TS_MODEL_FT6336 if required
#define TS_MODEL            TS_MODEL_FT6336
#define TS_SDA                16
#define TS_SCL                15
#define TS_INT                17
#define TS_RST                18
#endif

/* --- AUDIO DECODER --- */

#if defined(ESP32_S3_ES3C28P)
// ES3C28P I2S pins (from LCDWiki / user)
#define I2S_MCLK        4
#define I2S_BCLK        5
#define I2S_DIN         6   /* mic in */
#define I2S_LRC         7
#define I2S_DOUT        8   /* speaker out */

#define PA_ENABLE       1   /* enable on-board power amp */
#define I2C_SCL         15
#define I2C_SDA         16

/* Audio amplifier control (IO1 low -> enable).
   Default: write MUTE_VAL (HIGH) while stopped, write !MUTE_VAL while playing.
   Set MUTE_PIN to enable control (for FM8002/ES8311, etc). */
#define MUTE_PIN        1
#define MUTE_VAL        HIGH

/* Maximum I2S value to allow when mapping to ES8311 codec (0..254). */
#ifndef ES8311_MAX_I2S
#define ES8311_MAX_I2S 180
#endif

#define VS1053_CS       255  /* set to 255 to disable VS1053 */
#endif
#if defined(ESP32_S3_TRIP5_SH1106_VS1053_3BUTTONS)
#define VS_HSPI         false
#define VS1053_CS       9
#define VS1053_DCS      14
#define VS1053_DREQ     10
#define VS1053_RST      -1      /* set to -1 if connected to ESP EN pin */
#define I2S_DOUT        255     /* set to 255 to disable PCM */
#define VS_PATCH_ENABLE false   /* For the 2.5V boards with wrong voltage regulator.  See here: https://github.com/e2002/yoradio/issues/108 */
                                /* Probably works on all */
#endif
#if defined(ESP32_S3_TRIP5_ST7735_PCM_1BUTTON) || defined(ESP32_S3_TRIP5_ILI9488_PCM_1BUTTON)
#define I2S_DOUT        15
#define I2S_BCLK        7
#define I2S_LRC         6
#define VS1053_CS       255     /* set to 255 to disable VS1053 */
#endif
#if defined(ESP32_S3_TRIP5_SH1106_PCM_REMOTE) || defined(ESP32_S3_TRIP5_SH1106_PCM_1BUTTON) ||\
    defined(ESP32_S3_TRIP5_SSD1306X32_PCM_1BUTTON)
#define I2S_DOUT        12
#define I2S_BCLK        11
#define I2S_LRC         10
#define VS1053_CS       255     /* set to 255 to disable VS1053 */
#endif


/* --- BUTTONS --- */

#if defined(ESP32_S3_TRIP5_SH1106_VS1053_3BUTTONS)
#define ONE_CLICK_SWITCH true
#define BTN_UP          17      /* Prev, Move Up */
#define BTN_DOWN        18      /* Next, Move Down */
#define BTN_MODE        16      /* MODE switcher  */
#define WAKE_PIN        16      /* Wake from Deepsleep (actually using existing pins kind of disables sleep) */
#endif
#if defined(ESP32_S3_TRIP5_SH1106_PCM_1BUTTON) || defined(ESP32_S3_TRIP5_SSD1306X32_PCM_1BUTTON)
#define ONE_CLICK_SWITCH true
#define BTN_DOWN        17      /* Next, Move Down */
#endif
#if defined(ESP32_S3_TRIP5_SH1106_PCM_REMOTE)
#define ONE_CLICK_SWITCH true
#define VOLUME_STEPS 2
#define BTN_UP          17      /* Prev, Move Up */
#define BTN_DOWN        16      /* Next, Move Down */
#define BTN_CENTER      18      /* ENTER, Play/pause  */
#define BTN_LEFT        7       /* VolDown, Prev */
#define BTN_RIGHT       15      /* VolUp, Next */
#define WAKE_PIN        18      /* Wake from Deepsleep (actually using existing pins kind of disables sleep) */
#endif
#if defined(ESP32_S3_TRIP5_ST7735_PCM_1BUTTON) || defined(ESP32_S3_TRIP5_ILI9488_PCM_1BUTTON)
#define ONE_CLICK_SWITCH true
#define BTN_DOWN		42		/* Next, Move Down */
#endif
#if defined(ESP32_S3_ES3C28P)
#define ONE_CLICK_SWITCH true
#define BTN_DOWN        0       /* BOOT button - Next, Move Down */
#endif

/* Extras: unused in all */
//#define BTN_INTERNALPULLUP          false   /* Enable the weak pull up resistors */
//#define BTN_LONGPRESS_LOOP_DELAY    200     /* Delay between calling DuringLongPress event */
//#define BTN_CLICK_TICKS             300     /* Event Timing https://github.com/mathertel/OneButton#event-timing */
//#define BTN_PRESS_TICKS             500     /* Event Timing https://github.com/mathertel/OneButton#event-timing */


/* --- ROTARY ENCODER(S) --- */

#if defined(ESP32_S3_TRIP5_SH1106_VS1053_3BUTTONS) || defined(ESP32_S3_TRIP5_ST7735_PCM_1BUTTON) ||\
    defined(ESP32_S3_TRIP5_ILI9488_PCM_1BUTTON) || defined(ESP32_S3_TRIP5_SH1106_PCM_REMOTE)
#define ENC_BTNR        40
#define ENC_BTNL        39
#define ENC_BTNB        38
#elif defined(ESP32_S3_TRIP5_SH1106_PCM_1BUTTON) || defined(ESP32_S3_TRIP5_SSD1306X32_PCM_1BUTTON)
#define ENC_BTNR        7
#define ENC_BTNL        15
#define ENC_BTNB        16
#endif

/* Extras: unused in all */
//#define ENC_INTERNALPULLUP  true
//#define ENC_HALFQUARD       false

/* 2nd Rotary Encoder: ?? None yet */
//#define ENC2_BTNR       40
//#define ENC2_BTNL       39
//#define ENC2_BTNB       38
/* Extras: unused */
//#define ENC2_INTERNALPULLUP     true
//#define ENC2_HALFQUARD          false


/* --- SD CARD --- */

#if defined(ESP32_S3_ES3C28P)
  // SD card in SPI mode using HSPI bus (separate from display FSPI)
  #define BUILD_SDSPI 1
  #define SD_ID HSPI
  #define SD_HSPI true
  #define SD_SPIPINS      38, 39, 40     /* SCK, MISO, MOSI */
  #define SDC_CS          47
  // Increase SD SPI clock to 40 MHz to reduce read latency and avoid audio clipping.
  #define SDSPISPEED      40000000
#elif defined(ESP32_S3_TRIP5_ST7735_PCM_1BUTTON) || defined(ESP32_S3_TRIP5_SH1106_PCM_REMOTE) || defined(ESP32_S3_TRIP5_SH1106_PCM_1BUTTON) || defined(ESP32_S3_TRIP5_SSD1306X32_PCM_1BUTTON)
#define SD_SPIPINS      21, 13, 14      /* SCK, MISO, MOSI */
#define SDC_CS          47
#elif defined(ESP32_S3_TRIP5_SH1106_VS1053_3BUTTONS ) || defined(ESP32_S3_TRIP5_ILI9488_PCM_1BUTTON)
#define SD_SPIPINS      21, 2, 1        /* SCK, MISO, MOSI */
#define SDC_CS          47
#endif

/* Extras: unused in all */
//#define SD_HSPI     /* false (not needed when using custom pins) */
//#define SDSPISPEED      8000000     /* Default speed 20000000 */

/* --- WIFI --- */

#if defined(ESP32_S3_ES3C28P)
/* WiFi Scanning - enable for multiple APs (slower startup) */
#define WIFI_SCAN_BEST_RSSI true     /* Scan and connect to strongest RSSI (slower startup, useful with multiple APs) */
#endif

/* --- USER DEFAULTS --- */

#if defined (BOARD_ESP32_S3_N16R8) || defined (BOARD_ESP32)
#define TIMEZONE_NAME   "Europe/Moscow"
#define TIMEZONE_POSIX  "MSK-3"
#define SNTP_1          "pool.ntp.org"
#define SNTP_2          "lt.pool.ntp.org"
#define WEATHER_LAT     "55.7512"       /* latitude */
#define WEATHER_LON     "37.6184"       /* longitude */
#elif defined(ESP32_S3_ES3C28P)
#define SMART_START true
#define SHOW_AUDIO_INFO true
#define SS_PLAYING true
#define TIMEZONE_NAME   "Europe/Vilnius"
#define TIMEZONE_POSIX  "EET-2EEST,M3.5.0/3,M10.5.0/42"
#define SNTP_1          "pool.ntp.org"
#define SNTP_2          "lt.pool.ntp.org"
#define WEATHER_LAT     "55.721924"       /* latitude */
#define WEATHER_LON     "21.117868"      /* longitude */
#define VOLUME_STEPS    5

#elif defined(ESP32_S3_TRIP5_ST7735_PCM_1BUTTON) || defined(ESP32_S3_TRIP5_SH1106_PCM_REMOTE) ||\
      defined(ESP32_S3_TRIP5_SH1106_PCM_1BUTTON) || defined(ESP32_S3_TRIP5_SSD1306X32_PCM_1BUTTON) ||\
      defined(ESP32_S3_TRIP5_SH1106_VS1053_3BUTTONS ) || defined(ESP32_S3_TRIP5_ILI9488_PCM_1BUTTON)
#define SMART_START true
#define SD_SHUFFLE true
#define SHOW_AUDIO_INFO true
#define SHOW_VU_METER true
#define SS_PLAYING true
#define TIMEZONE_NAME   "Asia/Seoul"
#define TIMEZONE_POSIX  "KST-9"
#define SNTP_1          "kr.pool.ntp.org"
#define SNTP_2          "pool.ntp.org"
#define WEATHER_LAT     "37.5503"       /* latitude */
#define WEATHER_LON     "126.9971"      /* longitude */
#define HIDE_WEATHER
#define MQTT_ENABLE
#endif

/* --- MORE, UNUSED, UNKNOWN, NOTES --- */

//#define IR_PIN                1
//#define IR_TIMEOUT            80              /*  see kTimeout description in IRremoteESP8266 example https://github.com/crankyoldgit/IRremoteESP8266/blob/master/examples/IRrecvDumpV2/IRrecvDumpV2.ino */

//#define ROTATE_90 /* rotates 90 degrees? */

//#define ESPFILEUPDATER_DEBUG

/* Extras: unused in all */
//#define L10N_LANGUAGE EN
//#define IR_PIN 4

/* Memory? */
//#define XTASK_MEM_SIZE 4096 /* default 4096*/

/* Does this get carried to SD Lib and allow Exfat? */
//#define FF_FS_EXFAT 1

#endif // myoptions_h
