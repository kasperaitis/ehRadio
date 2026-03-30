#ifndef optionschecker_h
#define optionschecker_h

#if REAL_LEDBUILTIN==TFT_RST
#  error LED_BUILTIN IS THE SAME AS TFT_RST. Check it in myoptions.h
#endif

#if REAL_LEDBUILTIN==VS1053_RST
#  error LED_BUILTIN IS THE SAME AS VS1053_RST. Check it in myoptions.h
#endif

#if (I2S_DOUT!=255) && (VS1053_CS!=255)
#  error YOU MUST CHOOSE BETWEEN I2S DAC AND VS1053 BY DISABLING THE SECOND MODULE IN THE myoptions.h
#endif

#if !(defined(ARDUINO_ESP32_DEV) || defined(ARDUINO_ESP32S3_DEV) || defined(ARDUINO_ESP32C3_DEV))
#  error ONLY MODULES "ESP32 Dev Module", "ESP32 Wrover Module" AND "ESP32 S3 Dev Module" ARE SUPPORTED. PLEASE SELECT ONE OF THEM
#endif

#if (defined(L10N_CP_CYRILLIC) && defined(L10N_CP_LATIN))
#  error Why are L10N_CP_CYRILLIC and L10N_CP_LATIN both defined? Do not define 2 codepages!
#endif

#if defined(TIME_SYNC_INTERVAL) && (TIME_SYNC_INTERVAL < 1 || TIME_SYNC_INTERVAL > 24)
#  error TIME_SYNC_INTERVAL must be a number from 1 to 24
#endif

#if defined(WEATHER_SYNC_INTERVAL) && (WEATHER_SYNC_INTERVAL < 10 || WEATHER_SYNC_INTERVAL > 60)
#  error WEATHER_SYNC_INTERVAL must be a number from 10 to 60
#endif

#ifdef WEATHER_WIND_SPEED_UNITS
static_assert(
  __builtin_strcmp(WEATHER_WIND_SPEED_UNITS, "kmh") == 0 ||
  __builtin_strcmp(WEATHER_WIND_SPEED_UNITS, "mph") == 0 ||
  __builtin_strcmp(WEATHER_WIND_SPEED_UNITS, "kn")  == 0 ||
  __builtin_strcmp(WEATHER_WIND_SPEED_UNITS, "m/s") == 0,
  "WEATHER_WIND_SPEED_UNITS must be \"kmh\", \"mph\", \"kn\", or \"m/s\""
);
#endif

#endif // #ifndef optionschecker_h
