#ifndef dsp_full_loc
#define dsp_full_loc
#include <pgmspace.h>
/*************************************************************************************
    HOWTO:
    Copy this file to locale/displayL10n_custom.h
    and modify it
*************************************************************************************/
// Language: Uzbek
// IETF BCP 47: "uz-UZ"
const char mon[] PROGMEM = "du";
const char tue[] PROGMEM = "se";
const char wed[] PROGMEM = "ch";
const char thu[] PROGMEM = "pa";
const char fri[] PROGMEM = "ju";
const char sat[] PROGMEM = "sh";
const char sun[] PROGMEM = "ya";

const char monf[] PROGMEM = "dushanba";
const char tuef[] PROGMEM = "seshanba";
const char wedf[] PROGMEM = "chorshanba";
const char thuf[] PROGMEM = "payshanba";
const char frif[] PROGMEM = "juma";
const char satf[] PROGMEM = "shanba";
const char sunf[] PROGMEM = "yakshanba";

const char jan[] PROGMEM = "yanvar";
const char feb[] PROGMEM = "fevral";
const char mar[] PROGMEM = "mart";
const char apr[] PROGMEM = "aprel";
const char may[] PROGMEM = "may";
const char jun[] PROGMEM = "iyun";
const char jul[] PROGMEM = "iyul";
const char aug[] PROGMEM = "avgust";
const char sep[] PROGMEM = "sentyabr";
const char oct[] PROGMEM = "oktyabr";
const char nov[] PROGMEM = "noyabr";
const char dec[] PROGMEM = "dekabr";

const char wn_N[]      PROGMEM = "Shimol";
const char wn_NNE[]    PROGMEM = "SSS";
const char wn_NE[]     PROGMEM = "SS";
const char wn_ENE[]    PROGMEM = "VS";
const char wn_E[]      PROGMEM = "Sharq";
const char wn_ESE[]    PROGMEM = "VVJ";
const char wn_SE[]     PROGMEM = "VJ";
const char wn_SSE[]    PROGMEM = "JJV";
const char wn_S[]      PROGMEM = "Janub";
const char wn_SSW[]    PROGMEM = "JJK";
const char wn_SW[]     PROGMEM = "J";
const char wn_WSW[]    PROGMEM = "ZJZ";
const char wn_W[]      PROGMEM = "G'arb";
const char wn_WNW[]    PROGMEM = "ZZS";
const char wn_NW[]     PROGMEM = "ZS";
const char wn_NNW[]    PROGMEM = "SNS";

const char* const dow[]     PROGMEM = { sun, mon, tue, wed, thu, fri, sat };
const char* const dowf[]    PROGMEM = { sunf, monf, tuef, wedf, thuf, frif, satf };
const char* const mnths[]   PROGMEM = { jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };
const char* const wind[]    PROGMEM = { wn_N, wn_NNE, wn_NE, wn_ENE, wn_E, wn_ESE, wn_SE, wn_SSE, wn_S, wn_SSW, wn_SW, wn_WSW, wn_W, wn_WNW, wn_NW, wn_NNW, wn_N };

const char    const_PlReady[]    PROGMEM = "[tayyor]";
const char  const_PlStopped[]    PROGMEM = "[to'xtatilgan]";
const char  const_PlConnect[]    PROGMEM = "[ulanish]";
const char  const_DlgVolume[]    PROGMEM = "HAJMI";
const char    const_DlgLost[]    PROGMEM = "* ULANISH YO'Q *";
const char  const_DlgUpdate[]    PROGMEM = "* YANGILANMOQDA *";
const char const_DlgNextion[]    PROGMEM = "NEXTION";
const char  const_waitForSD[]    PROGMEM = "SD INDEKSI";

const char        apNameTxt[]    PROGMEM = "AP NOMI";
#ifdef AP_PASSWORD
  const char        apPassTxt[]    PROGMEM = "PAROL";
#else
  const char        apPassTxt[]    PROGMEM = "PAROLSIZ";
#endif

const char       bootstrFmt[]    PROGMEM = "Wi-fi: %s";
const char        apSettFmt[]    PROGMEM = "ULANING & OCHING HTTP://%s/";

#ifdef UPDATEURL
  const char      updFirmware[]    PROGMEM = "Firmware yangilanmoqda";
  const char         updFiles[]    PROGMEM = "Fayllar yangilanmoqda";
  const char        updFailed[]    PROGMEM = "Yangilanish muvaffaqiyatsiz tugadi";
#endif

const char weather_feelslike[]  PROGMEM = "his qilish:";
const char weather_pressure[]   PROGMEM = "bosim:";
const char weather_humidity[]   PROGMEM = "namlik:";
const char weather_wind[]       PROGMEM = "shamol:";
const char weather_loading[]    PROGMEM = "Ob-havo ma'lumotlari yuklanmoqda...";

// WMO Weather Code Translations (for Open-Meteo)
const char w_clear_sky[]         PROGMEM = "Ochiq osmon";
const char w_overcast[]          PROGMEM = "Bulutli";
const char w_foggy[]             PROGMEM = "Tumanli";
const char w_drizzle[]           PROGMEM = "Mayda yomg'ir";
const char w_freezing_drizzle[]  PROGMEM = "Muzlaydigan mayda yomg'ir";
const char w_rain[]              PROGMEM = "Yomg'ir";
const char w_freezing_rain[]     PROGMEM = "Muzlaydigan yomg'ir";
const char w_snow[]              PROGMEM = "Qor";
const char w_snow_grains[]       PROGMEM = "Qor donalari";
const char w_rain_showers[]      PROGMEM = "Jala yomg'ir";
const char w_snow_showers[]      PROGMEM = "Qor yog'ishi";
const char w_thunderstorm[]      PROGMEM = "Momaqaldiroq";
const char w_thunderstorm_hail[] PROGMEM = "Do'l bilan momaqaldiroq";

#endif

