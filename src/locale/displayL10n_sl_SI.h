#ifndef dsp_full_loc
#define dsp_full_loc
#include <pgmspace.h>
/*************************************************************************************
    HOWTO:
    Copy this file to locale/displayL10n_custom.h
    and modify it
*************************************************************************************/
// Language: Slovenian
// IETF BCP 47: "sl-SI"
const char mon[] PROGMEM = "po";
const char tue[] PROGMEM = "to";
const char wed[] PROGMEM = "sr";
const char thu[] PROGMEM = "če";
const char fri[] PROGMEM = "pe";
const char sat[] PROGMEM = "so";
const char sun[] PROGMEM = "ne";

const char monf[] PROGMEM = "ponedeljek";
const char tuef[] PROGMEM = "torek";
const char wedf[] PROGMEM = "sreda";
const char thuf[] PROGMEM = "četrtek";
const char frif[] PROGMEM = "petek";
const char satf[] PROGMEM = "sobota";
const char sunf[] PROGMEM = "nedelja";

const char jan[] PROGMEM = "januar";
const char feb[] PROGMEM = "februar";
const char mar[] PROGMEM = "marec";
const char apr[] PROGMEM = "april";
const char may[] PROGMEM = "maj";
const char jun[] PROGMEM = "junij";
const char jul[] PROGMEM = "julij";
const char aug[] PROGMEM = "avgust";
const char sep[] PROGMEM = "september";
const char octt[] PROGMEM = "oktober";
const char nov[] PROGMEM = "november";
const char decc[] PROGMEM = "december";

const char wn_N[]      PROGMEM = "S";
const char wn_NNE[]    PROGMEM = "SSV";
const char wn_NE[]     PROGMEM = "SV";
const char wn_ENE[]    PROGMEM = "VSV";
const char wn_E[]      PROGMEM = "V";
const char wn_ESE[]    PROGMEM = "VJV";
const char wn_SE[]     PROGMEM = "JV";
const char wn_SSE[]    PROGMEM = "JJV";
const char wn_S[]      PROGMEM = "J";
const char wn_SSW[]    PROGMEM = "JJZ";
const char wn_SW[]     PROGMEM = "JZ";
const char wn_WSW[]    PROGMEM = "ZZJ";
const char wn_W[]      PROGMEM = "Z";
const char wn_WNW[]    PROGMEM = "ZZS";
const char wn_NW[]     PROGMEM = "ZS";
const char wn_NNW[]    PROGMEM = "SNS";

const char* const dow[]     PROGMEM = { sun, mon, tue, wed, thu, fri, sat };
const char* const dowf[]    PROGMEM = { sunf, monf, tuef, wedf, thuf, frif, satf };
const char* const mnths[]   PROGMEM = { jan, feb, mar, apr, may, jun, jul, aug, sep, octt, nov, decc };
const char* const wind[]    PROGMEM = { wn_N, wn_NNE, wn_NE, wn_ENE, wn_E, wn_ESE, wn_SE, wn_SSE, wn_S, wn_SSW, wn_SW, wn_WSW, wn_W, wn_WNW, wn_NW, wn_NNW, wn_N };

const char    const_PlReady[]    PROGMEM = "[pripravljen]";
const char  const_PlStopped[]    PROGMEM = "[ustavljen]";
const char  const_PlConnect[]    PROGMEM = "[povezovanje]";
const char  const_DlgVolume[]    PROGMEM = "GLASNOST";
const char    const_DlgLost[]    PROGMEM = "* PREKINJENO *";
const char  const_DlgUpdate[]    PROGMEM = "* POSODOBITEV *";
const char const_DlgNextion[]    PROGMEM = "NEXTION";
const char const_getWeather[]    PROGMEM = "";
const char  const_waitForSD[]    PROGMEM = "INDEKS SD";

const char        apNameTxt[]    PROGMEM = "IME AP";
#ifdef AP_PASSWORD
  const char        apPassTxt[]    PROGMEM = "GESLO";
#else
  const char        apPassTxt[]    PROGMEM = "BREZ GESLA";
#endif

const char       bootstrFmt[]    PROGMEM = "Wi-fi: %s";
const char        apSettFmt[]    PROGMEM = "POVEŽITE SE IN ODPRITE HTTP://%s/";

#ifdef UPDATEURL
  const char      updFirmware[]    PROGMEM = "Posodablja se firmware";
  const char         updFiles[]    PROGMEM =  "Posodabljajo se datoteke";
  const char        updFailed[]    PROGMEM = "Posodobitev ni uspela";
#endif

#if EXT_WEATHER
const char       weatherFmt[]    PROGMEM = "%s, %.1f\011C \007 občutek: %.1f\011C \007 tlak: %d hPa \007 vlažnost: %s%% \007 veter: %.1f m/s [%s]";
#else
const char       weatherFmt[]    PROGMEM = "%s, %.1f\011C \007 tlak: %d hPa \007 vlažnost: %s%%";
#endif
const char     weatherUnits[]    PROGMEM = "metric";   /* standard, metric, imperial */
const char      weatherLang[]    PROGMEM = "sl";       /* https://openweathermap.org/current#multi */

#endif

