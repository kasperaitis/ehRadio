#ifndef myoptions_h
#define myoptions_h

/* - - - = = = - - - Choose the Radio (defined by platformio.ini env) - - - = = = - - - */
/* automatic builds define the board - - - be sure to comment all lines after debugging */

//#define DEBUG_MYOPTIONS                              // uncomment to debug myoptions.h -- and uncomment one option below!
//#define ESP32_S3_KASPERAITIS_ES3C28P                 // ESP32-S3 ES3C28P Dev Board (attached 240x320 screen and ES8311 + FM8002E Decoder)

/* --- FIRMWARE FILENAME & BOARD --- */

#if defined(BOARD_ESP32) & not defined(DEBUG_MYOPTIONS)
  #undef FIRMWARE
  #define FIRMWARE "board_esp32.bin"
  //#undef UPDATEURL /* if an ESP does not have the memory to do online updates from https sources (this will disable it) */
#elif defined(BOARD_ESP32_S3_N16R8)
  #undef FIRMWARE
  #define FIRMWARE "board_esp32_s3_n16r8.bin"
  #define ARDUINO_ESP32S3_DEV
#elif defined(ESP32_S3_KASPERAITIS_ES3C28P)
  #undef FIRMWARE
  #define FIRMWARE "esp32_s3_kasperaitis_esc3c28p.bin"
  #define ARDUINO_ESP32S3_DEV
#endif


/* --- LED --- */

#if defined(BOARD_ESP32) & not defined(DEBUG_MYOPTIONS)
  #define USE_BUILTIN_LED     true
#else
  #define USE_BUILTIN_LED     false    /* usually...! Unless you actually want to use the builtin as defined by the board's .h file */
#endif

#if defined(ESP32_S3_KASPERAITIS_ES3C28P)
  #define USE_RGB_LED     true         /* Enable single-pin RGB LED (WS2812 style) on ES3C28P boards */
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

/* Display config for I2C displays */



/* Display config for SPI displays */
/* When using SPI Displays, trying to use same SPI MOSI, SCK, MISO as VS1053 doesn't work */
#if defined(ESP32_S3_KASPERAITIS_ES3C28P)
  #define DSP_MODEL       DSP_ILI9341
  #define PRINT_FIX
  #define SCREEN_INVERT true
  #define TFT_CS          10
  #define TFT_DC          46
  #define TFT_RST         -1
  #define TFT_BL          45
  //#define GFX_BL          45
  /* SPI pins for the TFT module (ES3C28P) */
  #define TFT_MOSI        11
  #define TFT_SCLK        12
  #define TFT_MISO        13
  #define BRIGHTNESS_PIN  TFT_BL
#endif


/* --- AUDIO DECODER --- */

#if defined(ESP32_S3_KASPERAITIS_ES3C28P)
  #define USE_ES8311                  /* a special define for a special decoder */
  /* ES3C28P I2S pins (from LCDWiki / user) */
  #define I2S_MCLK        4
  #define I2S_BCLK        5
  #define I2S_DIN         6       /* mic in */
  #define I2S_LRC         7
  #define I2S_DOUT        8       /* speaker out */
  #define PA_ENABLE       1       /* enable on-board power amp */
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
  #define VS1053_CS       255     /* set to 255 to disable VS1053 */
#endif


/* --- TOUCH --- */

#if defined(ESP32_S3_KASPERAITIS_ES3C28P)
  // For some ES3C28P boards the touch controller may be D-FT6336G family — set to TS_MODEL_FT6336 if required
  #define TS_MODEL            TS_MODEL_FT6336
  #define TS_SDA              16
  #define TS_SCL              15
  #define TS_INT              17
  #define TS_RST              18
#endif


/* --- BUTTONS --- */

#if defined(ESP32_S3_KASPERAITIS_ES3C28P)
  #define ONE_CLICK_SWITCH true
  #define BTN_DOWN        0       /* BOOT button - Next, Move Down */
#endif

/* Extras: unused in all */
//#define BTN_INTERNALPULLUP          false   /* Enable the weak pull up resistors */
//#define BTN_LONGPRESS_LOOP_DELAY    200     /* Delay between calling DuringLongPress event */
//#define BTN_CLICK_TICKS             300     /* Event Timing https://github.com/mathertel/OneButton#event-timing */
//#define BTN_PRESS_TICKS             500     /* Event Timing https://github.com/mathertel/OneButton#event-timing */


/* --- ROTARY ENCODER(S) --- */

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

#if defined(ESP32_S3_KASPERAITIS_ES3C28P)
  #define SD_SPIPINS      38, 39, 40     /* SCK, MISO, MOSI */
  #define SDC_CS          47
  #define SDSPISPEED      40000000       /* Default speed 20000000 */
#endif

/* Extras: unused in all */
//#define SD_HSPI     /* false (not needed when using custom pins) */


/* --- Battery --- */

#if defined(ESP32_S3_KASPERAITIS_ES3C28P)
  /* Battery monitoring on ES3C28P board */
  #define BATTERY_PIN     9       /* GPIO9: ADC pin for battery voltage */
  //#define BATTERY_CHARGE_PIN 255  /* No charging status GPIO exposed (TP4054 CHRG pin not connected on ES3C28P) */

  #define BATTERY_DIVIDER_RATIO 2.0   /* 100k + 100k voltage divider = 1:2 ratio */
  #define BATTERY_ADC_REF_MV 3438     /* ESP32-S3 ADC reference voltage (calibrated EL103565 3000mAh 11.1Wh) */
  #define BATTERY_UPDATE_INTERVAL 60000 /* Update every 60 seconds */
  //#define BATTERY_DEBUG               /* Uncomment to enable debug output */

  #define BATTERY_CHARGE_INFER_HOLD_SAMPLES 3 /* number of measurements (samples) to hold (e.g., 3 readings at BATTERY_UPDATE_INTERVAL) */
  #define BATTERY_IMMEDIATE_PERCENT_THRESHOLD 20 /* percent */
  #define BATTERY_CANDIDATE_PERCENT_DELTA 1 /* percent */
  #define BATTERY_SUSTAINED_PERCENT_WINDOW_THRESHOLD 0 /* percent over hold window */

  /* --- Plugin BacklightDown --- */

  //#define DOWN_INTERVAL 60   // seconds before auto-dim
  //#define DOWN_LEVEL    50   // optional: target PWM level (0..255). 64 ≈ 25% brightness
#endif


/* --- USER DEFAULTS --- */

#if defined (BOARD_ESP32_S3_N16R8) || defined (BOARD_ESP32) & not defined(DEBUG_MYOPTIONS)
  #define TIMEZONE_NAME   "Europe/Moscow"
  #define TIMEZONE_POSIX  "MSK-3"
  #define SNTP_1          "pool.ntp.org"
  #define SNTP_2          "0.ru.pool.ntp.org"
  #define WEATHER_LAT     "55.7512"       /* latitude */
  #define WEATHER_LON     "37.6184"       /* longitude */
#elif defined(ESP32_S3_KASPERAITIS_ES3C28P)
  #define SMART_START true
  #define SHOW_AUDIO_INFO true
  #define SS_PLAYING true
  #define WIFI_SCAN_BEST_RSSI true
  #define TIMEZONE_NAME   "Europe/Vilnius"
  #define TIMEZONE_POSIX  "EET-2EEST,M3.5.0/3,M10.5.0/42"
  #define SNTP_1          "lt.pool.ntp.org"
  #define SNTP_2          "pool.ntp.org"
  #define WEATHER_LAT     "55.721924"       /* latitude */
  #define WEATHER_LON     "21.117868"      /* longitude */
  #define SCREEN_FLIP     true
  #define SHOW_VU_METER   true
  #define VOLUME_STEPS    5
#endif


/* --- SYSTEM OVERRIDES --- */

#if defined (BOARD_ESP32) & not defined(DEBUG_MYOPTIONS)
  #define LOOP_TASK_STACK_SIZE 8  /* Compiler default is 8KB but seems safe on ESP32-S3 to increase to 16KB for audio decoding + concurrent tasks */
  #define CONFIG_ASYNC_TCP_QUEUE_SIZE 32
#elif defined (BOARD_ESP32_S3_N16R8) ||\
      defined(ESP32_S3_KASPERAITIS_ES3C28P)
  #define LOOP_TASK_STACK_SIZE 16  /* Compiler default is 8KB but seems safe on ESP32-S3 to increase to 16KB for audio decoding + concurrent tasks / 8KB is safe when using a VS1053 decoder */
  #define CONFIG_ASYNC_TCP_QUEUE_SIZE 64
  #define SEARCHRESULTS_BUFFER 1024*32 // 32KB matches chunk sizes from radio-browser.info but likely only good for ESP32-S3
  #define SEARCHRESULTS_YIELDINTERVAL 0 // With a large buffer, skipping is almost eliminated with 0
#endif


/* --- URL SOURCE OVERRIDE --- */
/* Only use this if you've decided to use your own Github as the source of files */
/* ...or your firmware is not available from Trip5's Github... sorry! */
/* Read the notes in the ./builds folder for more detailed information */

//#define GITHUBURL "https://github.com/kasperaitis/ehradio" // used by the radio to update firmware and files...

#endif // myoptions_h
