#ifndef dsp_full_loc
#define dsp_full_loc
#include <pgmspace.h>
/*************************************************************************************
    HOWTO:
    Copy this file to locale/displayL10n_custom.h
    and modify it
*************************************************************************************/
// Language: Hungarian
// IETF BCP 47: "hu-HU"
const char mon[] PROGMEM = "hé";
const char tue[] PROGMEM = "ke";
const char wed[] PROGMEM = "sz";
const char thu[] PROGMEM = "cs";
const char fri[] PROGMEM = "pe";
const char sat[] PROGMEM = "so";
const char sun[] PROGMEM = "va";

const char monf[] PROGMEM = "Hétfő";
const char tuef[] PROGMEM = "Kedd";
const char wedf[] PROGMEM = "Szerda";
const char thuf[] PROGMEM = "Csütörtök";
const char frif[] PROGMEM = "Péntek";
const char satf[] PROGMEM = "Szombat";
const char sunf[] PROGMEM = "Vasárnap";

const char jan[] PROGMEM = "Január";
const char feb[] PROGMEM = "Február";
const char mar[] PROGMEM = "Március";
const char apr[] PROGMEM = "Április";
const char may[] PROGMEM = "Május";
const char jun[] PROGMEM = "Június";
const char jul[] PROGMEM = "Július";
const char aug[] PROGMEM = "Augusztus";
const char sep[] PROGMEM = "Szeptember";
const char octt[] PROGMEM = "Október";
const char nov[] PROGMEM = "November";
const char decc[] PROGMEM = "December";

const char wn_N[]      PROGMEM = "ÉSZAK";
const char wn_NNE[]    PROGMEM = "NNE";
const char wn_NE[]     PROGMEM = "NE";
const char wn_ENE[]    PROGMEM = "ENE";
const char wn_E[]      PROGMEM = "KELET";
const char wn_ESE[]    PROGMEM = "ESE";
const char wn_SE[]     PROGMEM = "SE";
const char wn_SSE[]    PROGMEM = "SSE";
const char wn_S[]      PROGMEM = "DÉL";
const char wn_SSW[]    PROGMEM = "SSW";
const char wn_SW[]     PROGMEM = "SW";
const char wn_WSW[]    PROGMEM = "WSW";
const char wn_W[]      PROGMEM = "NYUGAT";
const char wn_WNW[]    PROGMEM = "WNW";
const char wn_NW[]     PROGMEM = "NW";
const char wn_NNW[]    PROGMEM = "NNW";

const char* const dow[]     PROGMEM = { sun, mon, tue, wed, thu, fri, sat };
const char* const dowf[]    PROGMEM = { sunf, monf, tuef, wedf, thuf, frif, satf };
const char* const mnths[]   PROGMEM = { jan, feb, mar, apr, may, jun, jul, aug, sep, octt, nov, decc };
const char* const wind[]    PROGMEM = { wn_N, wn_NNE, wn_NE, wn_ENE, wn_E, wn_ESE, wn_SE, wn_SSE, wn_S, wn_SSW, wn_SW, wn_WSW, wn_W, wn_WNW, wn_NW, wn_NNW, wn_N };

const char    const_PlReady[]    PROGMEM = "[kész]";
const char  const_PlStopped[]    PROGMEM = "[leállítva]";
const char  const_PlConnect[]    PROGMEM = "[csatlakozás]";
const char  const_DlgVolume[]    PROGMEM = "HANGERŐ";
const char    const_DlgLost[]    PROGMEM = "* KAPCSOLAT MEGSZAKADT *";
const char  const_DlgUpdate[]    PROGMEM = "* FRISSÍTÉS *";
const char const_DlgNextion[]    PROGMEM = "NEXTION";
const char const_getWeather[]    PROGMEM = "";
const char  const_waitForSD[]    PROGMEM = "INDEX SD";

const char        apNameTxt[]    PROGMEM = "AP NÉV";
#ifdef AP_PASSWORD
  const char        apPassTxt[]    PROGMEM = "JELSZÓ";
#else
  const char        apPassTxt[]    PROGMEM = "NINCS JELSZÓ";
#endif

const char       bootstrFmt[]    PROGMEM = "Wi-fi: %s";
const char        apSettFmt[]    PROGMEM = "CSATLAKOZZ ÉS NYISD MEG HTTP://%s/";

#ifdef UPDATEURL
  const char      updFirmware[]    PROGMEM = "Firmware frissítése";
  const char         updFiles[]    PROGMEM = "Fájlok frissítése";
  const char        updFailed[]    PROGMEM = "Frissítés sikertelen";
#endif

#if EXT_WEATHER
const char       weatherFmt[]    PROGMEM = "%s, %.1f\011C \007 érzet: %.1f\011C \007 nyomás: %d hPa \007 páratartalom: %s%% \007 szél: %.1f m/s [%s]";
#else
const char       weatherFmt[]    PROGMEM = "%s, %.1f\011C \007 nyomás: %d hPa \007 páratartalom: %s%%";
#endif
const char     weatherUnits[]    PROGMEM = "metric";   /* standard, metric, imperial */
const char      weatherLang[]    PROGMEM = "hu";       /* https://openweathermap.org/current#multi */

#endif

