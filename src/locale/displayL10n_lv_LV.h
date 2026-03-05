#ifndef dsp_full_loc
#define dsp_full_loc
#include <pgmspace.h>
/*************************************************************************************
    HOWTO:
    Copy this file to locale/displayL10n_custom.h
    and modify it
*************************************************************************************/
// Language: Latvian
// IETF BCP 47: "lv-LV"
const char mon[] PROGMEM = "pr";
const char tue[] PROGMEM = "ot";
const char wed[] PROGMEM = "tr";
const char thu[] PROGMEM = "ce";
const char fri[] PROGMEM = "pk";
const char sat[] PROGMEM = "se";
const char sun[] PROGMEM = "sv";

const char monf[] PROGMEM = "Pirmdiena";
const char tuef[] PROGMEM = "Otrdiena";
const char wedf[] PROGMEM = "Trešdiena";
const char thuf[] PROGMEM = "Ceturtdiena";
const char frif[] PROGMEM = "Piektdiena";
const char satf[] PROGMEM = "Sestdiena";
const char sunf[] PROGMEM = "Svētdiena";

const char jan[] PROGMEM = "Janvāris";
const char feb[] PROGMEM = "Februāris";
const char mar[] PROGMEM = "Marts";
const char apr[] PROGMEM = "Aprīlis";
const char may[] PROGMEM = "Maijs";
const char jun[] PROGMEM = "Jūnijs";
const char jul[] PROGMEM = "Jūlijs";
const char aug[] PROGMEM = "Augusts";
const char sep[] PROGMEM = "Septembris";
const char octt[] PROGMEM = "Oktobris";
const char nov[] PROGMEM = "Novembris";
const char decc[] PROGMEM = "Decembris";

const char wn_N[]      PROGMEM = "ZIEMEĻI";
const char wn_NNE[]    PROGMEM = "NNE";
const char wn_NE[]     PROGMEM = "NE";
const char wn_ENE[]    PROGMEM = "ENE";
const char wn_E[]      PROGMEM = "AUSTRUMI";
const char wn_ESE[]    PROGMEM = "ESE";
const char wn_SE[]     PROGMEM = "SE";
const char wn_SSE[]    PROGMEM = "SSE";
const char wn_S[]      PROGMEM = "DIENVIDI";
const char wn_SSW[]    PROGMEM = "SSW";
const char wn_SW[]     PROGMEM = "SW";
const char wn_WSW[]    PROGMEM = "WSW";
const char wn_W[]      PROGMEM = "RIETUMI";
const char wn_WNW[]    PROGMEM = "WNW";
const char wn_NW[]     PROGMEM = "NW";
const char wn_NNW[]    PROGMEM = "NNW";

const char* const dow[]     PROGMEM = { sun, mon, tue, wed, thu, fri, sat };
const char* const dowf[]    PROGMEM = { sunf, monf, tuef, wedf, thuf, frif, satf };
const char* const mnths[]   PROGMEM = { jan, feb, mar, apr, may, jun, jul, aug, sep, octt, nov, decc };
const char* const wind[]    PROGMEM = { wn_N, wn_NNE, wn_NE, wn_ENE, wn_E, wn_ESE, wn_SE, wn_SSE, wn_S, wn_SSW, wn_SW, wn_WSW, wn_W, wn_WNW, wn_NW, wn_NNW, wn_N };

const char    const_PlReady[]    PROGMEM = "[gatavs]";
const char  const_PlStopped[]    PROGMEM = "[apturēts]";
const char  const_PlConnect[]    PROGMEM = "[savienojas]";
const char  const_DlgVolume[]    PROGMEM = "SKAĻUMS";
const char    const_DlgLost[]    PROGMEM = "* PAZAUDĒTS *";
const char  const_DlgUpdate[]    PROGMEM = "* ATJAUNOT *";
const char const_DlgNextion[]    PROGMEM = "NEXTION";
const char const_getWeather[]    PROGMEM = "";
const char  const_waitForSD[]    PROGMEM = "INDEKSS SD";

const char        apNameTxt[]    PROGMEM = "AP VĀRDS";
#ifdef AP_PASSWORD
  const char        apPassTxt[]    PROGMEM = "PAROLE";
#else
  const char        apPassTxt[]    PROGMEM = "BEZ PAROLES";
#endif

const char       bootstrFmt[]    PROGMEM = "Wi-fi: %s";
const char        apSettFmt[]    PROGMEM = "PIESLĒDZIES UN ATVERI HTTP://%s/";

#ifdef UPDATEURL
  const char      updFirmware[]    PROGMEM = "Atjaunina programmaparatūru";
  const char         updFiles[]    PROGMEM = "Atjaunina failus";
  const char        updFailed[]    PROGMEM = "Atjaunināšana neizdevās";
#endif

#if EXT_WEATHER
const char       weatherFmt[]    PROGMEM = "%s, %.1f\011C \007 jūtas kā: %.1f\011C \007 spiediens: %d hPa \007 mitrums: %s%% \007 vējš: %.1f m/s [%s]";
#else
const char       weatherFmt[]    PROGMEM = "%s, %.1f\011C \007 spiediens: %d hPa \007 mitrums: %s%%";
#endif
const char     weatherUnits[]    PROGMEM = "metric";   /* standard, metric, imperial */
const char      weatherLang[]    PROGMEM = "la";       /* https://openweathermap.org/current#multi */

#endif

