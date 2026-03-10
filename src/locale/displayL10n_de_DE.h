#ifndef dsp_full_loc
#define dsp_full_loc
#include <pgmspace.h>
/*************************************************************************************
    HOWTO:
    Copy this file to locale/displayL10n_custom.h
    and modify it
*************************************************************************************/
// Language: German
// IETF BCP 47: "de-DE"
const char mon[] PROGMEM = "mo";
const char tue[] PROGMEM = "di";
const char wed[] PROGMEM = "mi";
const char thu[] PROGMEM = "do";
const char fri[] PROGMEM = "fr";
const char sat[] PROGMEM = "sa";
const char sun[] PROGMEM = "so";

const char monf[] PROGMEM = "Montag";
const char tuef[] PROGMEM = "Dienstag";
const char wedf[] PROGMEM = "Mittwoch";
const char thuf[] PROGMEM = "Donnerstag";
const char frif[] PROGMEM = "Freitag";
const char satf[] PROGMEM = "Samstag";
const char sunf[] PROGMEM = "Sonntag";

const char jan[] PROGMEM = "Januar";
const char feb[] PROGMEM = "Februar";
const char mar[] PROGMEM = "Maerz";
const char apr[] PROGMEM = "April";
const char may[] PROGMEM = "Mai";
const char jun[] PROGMEM = "Juni";
const char jul[] PROGMEM = "Juli";
const char aug[] PROGMEM = "August";
const char sep[] PROGMEM = "September";
const char octt[] PROGMEM = "Oktober";
const char nov[] PROGMEM = "November";
const char decc[] PROGMEM = "Dezember";

const char wn_N[]      PROGMEM = "NORD";
const char wn_NNE[]    PROGMEM = "NNE";
const char wn_NE[]     PROGMEM = "NE";
const char wn_ENE[]    PROGMEM = "ENE";
const char wn_E[]      PROGMEM = "OST";
const char wn_ESE[]    PROGMEM = "ESE";
const char wn_SE[]     PROGMEM = "SE";
const char wn_SSE[]    PROGMEM = "SSE";
const char wn_S[]      PROGMEM = "SÜD";
const char wn_SSW[]    PROGMEM = "SSW";
const char wn_SW[]     PROGMEM = "SW";
const char wn_WSW[]    PROGMEM = "WSW";
const char wn_W[]      PROGMEM = "WEST";
const char wn_WNW[]    PROGMEM = "WNW";
const char wn_NW[]     PROGMEM = "NW";
const char wn_NNW[]    PROGMEM = "NNW";

const char* const dow[]     PROGMEM = { sun, mon, tue, wed, thu, fri, sat };
const char* const dowf[]    PROGMEM = { sunf, monf, tuef, wedf, thuf, frif, satf };
const char* const mnths[]   PROGMEM = { jan, feb, mar, apr, may, jun, jul, aug, sep, octt, nov, decc };
const char* const wind[]    PROGMEM = { wn_N, wn_NNE, wn_NE, wn_ENE, wn_E, wn_ESE, wn_SE, wn_SSE, wn_S, wn_SSW, wn_SW, wn_WSW, wn_W, wn_WNW, wn_NW, wn_NNW, wn_N };

const char    const_PlReady[]    PROGMEM = "[bereit]";
const char  const_PlStopped[]    PROGMEM = "[gestoppt]";
const char  const_PlConnect[]    PROGMEM = "[verbinde]";
const char  const_DlgVolume[]    PROGMEM = "LAUTST";
const char    const_DlgLost[]    PROGMEM = "* VERBINDUNG VERLOREN *";
const char  const_DlgUpdate[]    PROGMEM = "* AKTUALISIERE *";
const char const_DlgNextion[]    PROGMEM = "NEXTION";
const char const_getWeather[]    PROGMEM = "";
const char  const_waitForSD[]    PROGMEM = "INDEX SD";

const char        apNameTxt[]    PROGMEM = "AP NAME";
#ifdef AP_PASSWORD
  const char        apPassTxt[]    PROGMEM = "PASSWORT";
#else
  const char        apPassTxt[]    PROGMEM = "KEIN PASSWORT";
#endif

const char       bootstrFmt[]    PROGMEM = "Wi-fi: %s";
const char        apSettFmt[]    PROGMEM = "CONNECT & OPEN HTTP://%s/";

#ifdef UPDATEURL
  const char      updFirmware[]    PROGMEM = "Firmware wird aktualisiert";
  const char         updFiles[]    PROGMEM = "Dateien werden aktualisiert";
  const char        updFailed[]    PROGMEM = "Aktualisierung fehlgeschlagen";
#endif

#if EXT_WEATHER
const char       weatherFmt[]    PROGMEM = "%s, %.1f\011C \007 gefühlt: %.1f\011C \007 Druck: %d hPa \007 Luftfeuchte: %s%% \007 Wind: %.1f m/s [%s]";
#else
const char       weatherFmt[]    PROGMEM = "%s, %.1f\011C \007 Druck: %d hPa \007 Luftfeuchte: %s%%";
#endif
const char     weatherUnits[]    PROGMEM = "metric";   /* standard, metric, imperial */
const char      weatherLang[]    PROGMEM = "de";       /* https://openweathermap.org/current#multi */

#endif
