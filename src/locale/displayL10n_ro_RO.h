#ifndef dsp_full_loc
#define dsp_full_loc
#include <pgmspace.h>
/*************************************************************************************
    HOWTO:
    Copy this file to locale/displayL10n_custom.h
    and modify it
*************************************************************************************/
// Language: Romanian
// IETF BCP 47: "ro-RO"
const char mon[] PROGMEM = "lu";
const char tue[] PROGMEM = "ma";
const char wed[] PROGMEM = "mi";
const char thu[] PROGMEM = "jo";
const char fri[] PROGMEM = "vi";
const char sat[] PROGMEM = "sâ";
const char sun[] PROGMEM = "du";

const char monf[] PROGMEM = "Luni";
const char tuef[] PROGMEM = "Marți";
const char wedf[] PROGMEM = "Miercuri";
const char thuf[] PROGMEM = "Joi";
const char frif[] PROGMEM = "Vineri";
const char satf[] PROGMEM = "Sâmbătă";
const char sunf[] PROGMEM = "Duminică";

const char jan[] PROGMEM = "Ianuarie";
const char feb[] PROGMEM = "Februarie";
const char mar[] PROGMEM = "Martie";
const char apr[] PROGMEM = "Aprilie";
const char may[] PROGMEM = "Mai";
const char jun[] PROGMEM = "Iunie";
const char jul[] PROGMEM = "Iulie";
const char aug[] PROGMEM = "August";
const char sep[] PROGMEM = "Septembrie";
const char octt[] PROGMEM = "Octombrie";
const char nov[] PROGMEM = "Noiembrie";
const char decc[] PROGMEM = "Decembrie";

const char wn_N[]      PROGMEM = "NORD";
const char wn_NNE[]    PROGMEM = "NNE";
const char wn_NE[]     PROGMEM = "NE";
const char wn_ENE[]    PROGMEM = "ENE";
const char wn_E[]      PROGMEM = "EST";
const char wn_ESE[]    PROGMEM = "ESE";
const char wn_SE[]     PROGMEM = "SE";
const char wn_SSE[]    PROGMEM = "SSE";
const char wn_S[]      PROGMEM = "SUD";
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

const char    const_PlReady[]    PROGMEM = "[gata]";
const char  const_PlStopped[]    PROGMEM = "[oprit]";
const char  const_PlConnect[]    PROGMEM = "[conectare]";
const char  const_DlgVolume[]    PROGMEM = "VOLUM";
const char    const_DlgLost[]    PROGMEM = "* FĂRĂ CONEXIUNE *";
const char  const_DlgUpdate[]    PROGMEM = "* ACTUALIZARE *";
const char const_DlgNextion[]    PROGMEM = "NEXTION";
const char const_getWeather[]    PROGMEM = "";
const char  const_waitForSD[]    PROGMEM = "INDEX SD";

const char        apNameTxt[]    PROGMEM = "NUME AP";
#ifdef AP_PASSWORD
  const char        apPassTxt[]    PROGMEM = "PAROLĂ";
#else
  const char        apPassTxt[]    PROGMEM = "FĂRĂ PAROLĂ";
#endif

const char       bootstrFmt[]    PROGMEM = "Wi-fi: %s";
const char        apSettFmt[]    PROGMEM = "CONECTAȚI-VĂ ȘI DESCHIDEȚI HTTP://%s/";

#ifdef UPDATEURL
  const char      updFirmware[]    PROGMEM = "Actualizare firmware";
  const char         updFiles[]    PROGMEM = "Actualizare fișiere";
  const char        updFailed[]    PROGMEM = "Actualizare eșuată";
#endif

#if EXT_WEATHER
const char       weatherFmt[]    PROGMEM = "%s, %.1f\011C \007 senzație: %.1f\011C \007 presiune: %d hPa \007 umiditate: %s%% \007 vânt: %.1f m/s [%s]";
#else
const char       weatherFmt[]    PROGMEM = "%s, %.1f\011C \007 presiune: %d hPa \007 umiditate: %s%%";
#endif
const char     weatherUnits[]    PROGMEM = "metric";   /* standard, metric, imperial */
const char      weatherLang[]    PROGMEM = "ro";       /* https://openweathermap.org/current#multi */

#endif

