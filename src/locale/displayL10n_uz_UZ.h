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
const char octt[] PROGMEM = "oktyabr";
const char nov[] PROGMEM = "noyabr";
const char decc[] PROGMEM = "dekabr";

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
const char* const mnths[]   PROGMEM = { jan, feb, mar, apr, may, jun, jul, aug, sep, octt, nov, decc };
const char* const wind[]    PROGMEM = { wn_N, wn_NNE, wn_NE, wn_ENE, wn_E, wn_ESE, wn_SE, wn_SSE, wn_S, wn_SSW, wn_SW, wn_WSW, wn_W, wn_WNW, wn_NW, wn_NNW, wn_N };

const char    const_PlReady[]    PROGMEM = "[tayyor]";
const char  const_PlStopped[]    PROGMEM = "[to'xtatilgan]";
const char  const_PlConnect[]    PROGMEM = "[ulanish]";
const char  const_DlgVolume[]    PROGMEM = "HAJMI";
const char    const_DlgLost[]    PROGMEM = "* ULANISH YO'Q *";
const char  const_DlgUpdate[]    PROGMEM = "* YANGILANMOQDA *";
const char const_DlgNextion[]    PROGMEM = "NEXTION";
const char const_getWeather[]    PROGMEM = "";
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

#if EXT_WEATHER
const char       weatherFmt[]    PROGMEM = "%s, %.1f\011C \007 haqiqiy his: %.1f\011C \007 bosim: %d hPa \007 namlik: %s%% \007 shamol: %.1f m/s [%s]";
#else
const char       weatherFmt[]    PROGMEM = "%s, %.1f\011C \007 bosim: %d hPa \007 namlik: %s%%";
#endif
const char     weatherUnits[]    PROGMEM = "metric";   /* standard, metric, imperial */
const char      weatherLang[]    PROGMEM = "en";       /* https://openweathermap.org/current#multi */

#endif

