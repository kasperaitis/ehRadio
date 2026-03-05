#ifndef dsp_full_loc
#define dsp_full_loc
#include <pgmspace.h>
/*************************************************************************************
    HOWTO:
    Copy this file to locale/displayL10n_custom.h
    and modify it
*************************************************************************************/
// Language: Norwegian
// IETF BCP 47: "no-NO"
const char mon[] PROGMEM = "ma";
const char tue[] PROGMEM = "ti";
const char wed[] PROGMEM = "on";
const char thu[] PROGMEM = "to";
const char fri[] PROGMEM = "fr";
const char sat[] PROGMEM = "lø";
const char sun[] PROGMEM = "sø";

const char monf[] PROGMEM = "Mandag";
const char tuef[] PROGMEM = "Tirsdag";
const char wedf[] PROGMEM = "Onsdag";
const char thuf[] PROGMEM = "Torsdag";
const char frif[] PROGMEM = "Fredag";
const char satf[] PROGMEM = "Lørdag";
const char sunf[] PROGMEM = "Søndag";

const char jan[] PROGMEM = "Januar";
const char feb[] PROGMEM = "Februar";
const char mar[] PROGMEM = "Mars";
const char apr[] PROGMEM = "April";
const char may[] PROGMEM = "Mai";
const char jun[] PROGMEM = "Juni";
const char jul[] PROGMEM = "Juli";
const char aug[] PROGMEM = "August";
const char sep[] PROGMEM = "September";
const char octt[] PROGMEM = "Oktober";
const char nov[] PROGMEM = "November";
const char decc[] PROGMEM = "Desember";

const char wn_N[]      PROGMEM = "NORD";
const char wn_NNE[]    PROGMEM = "NNE";
const char wn_NE[]     PROGMEM = "NE";
const char wn_ENE[]    PROGMEM = "ENE";
const char wn_E[]      PROGMEM = "ØST";
const char wn_ESE[]    PROGMEM = "ESE";
const char wn_SE[]     PROGMEM = "SØ";
const char wn_SSE[]    PROGMEM = "SSE";
const char wn_S[]      PROGMEM = "SØR";
const char wn_SSW[]    PROGMEM = "SSW";
const char wn_SW[]     PROGMEM = "SV";
const char wn_WSW[]    PROGMEM = "WSW";
const char wn_W[]      PROGMEM = "VEST";
const char wn_WNW[]    PROGMEM = "WNW";
const char wn_NW[]     PROGMEM = "NV";
const char wn_NNW[]    PROGMEM = "NNW";

const char* const dow[]     PROGMEM = { sun, mon, tue, wed, thu, fri, sat };
const char* const dowf[]    PROGMEM = { sunf, monf, tuef, wedf, thuf, frif, satf };
const char* const mnths[]   PROGMEM = { jan, feb, mar, apr, may, jun, jul, aug, sep, octt, nov, decc };
const char* const wind[]    PROGMEM = { wn_N, wn_NNE, wn_NE, wn_ENE, wn_E, wn_ESE, wn_SE, wn_SSE, wn_S, wn_SSW, wn_SW, wn_WSW, wn_W, wn_WNW, wn_NW, wn_NNW, wn_N };

const char    const_PlReady[]    PROGMEM = "[klar]";
const char  const_PlStopped[]    PROGMEM = "[stoppet]";
const char  const_PlConnect[]    PROGMEM = "[kobler]";
const char  const_DlgVolume[]    PROGMEM = "VOLUM";
const char    const_DlgLost[]    PROGMEM = "* TAPT FORBINDELSE *";
const char  const_DlgUpdate[]    PROGMEM = "* OPPDATERER *";
const char const_DlgNextion[]    PROGMEM = "NEXTION";
const char const_getWeather[]    PROGMEM = "";
const char  const_waitForSD[]    PROGMEM = "INDEKS SD";

const char        apNameTxt[]    PROGMEM = "AP NAVN";
#ifdef AP_PASSWORD
  const char        apPassTxt[]    PROGMEM = "PASSORD";
#else
  const char        apPassTxt[]    PROGMEM = "INGEN PASSORD";
#endif

const char       bootstrFmt[]    PROGMEM = "Wi-fi: %s";
const char        apSettFmt[]    PROGMEM = "KOBLE TIL & ÅPNE HTTP://%s/";

#ifdef UPDATEURL
  const char      updFirmware[]    PROGMEM = "Oppdaterer fastvare";
  const char         updFiles[]    PROGMEM = "Oppdaterer filer";
  const char        updFailed[]    PROGMEM = "Oppdatering mislyktes";
#endif

#if EXT_WEATHER
const char       weatherFmt[]    PROGMEM = "%s, %.1f\011C \007 føles som: %.1f\011C \007 trykk: %d hPa \007 fuktighet: %s%% \007 vind: %.1f m/s [%s]";
#else
const char       weatherFmt[]    PROGMEM = "%s, %.1f\011C \007 trykk: %d hPa \007 fuktighet: %s%%";
#endif
const char     weatherUnits[]    PROGMEM = "metric";   /* standard, metric, imperial */
const char      weatherLang[]    PROGMEM = "no";       /* https://openweathermap.org/current#multi */

#endif

