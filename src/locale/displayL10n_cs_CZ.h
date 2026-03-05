#ifndef dsp_full_loc
#define dsp_full_loc
#include <pgmspace.h>
/*************************************************************************************
    HOWTO:
    Copy this file to locale/displayL10n_custom.h
    and modify it
*************************************************************************************/
// Language: Czech
// IETF BCP 47: "cs-CZ"
const char mon[] PROGMEM = "po";
const char tue[] PROGMEM = "út";
const char wed[] PROGMEM = "st";
const char thu[] PROGMEM = "čt";
const char fri[] PROGMEM = "pá";
const char sat[] PROGMEM = "so";
const char sun[] PROGMEM = "ne";

const char monf[] PROGMEM = "pondělí";
const char tuef[] PROGMEM = "úterý";
const char wedf[] PROGMEM = "středa";
const char thuf[] PROGMEM = "čtvrtek";
const char frif[] PROGMEM = "pátek";
const char satf[] PROGMEM = "sobota";
const char sunf[] PROGMEM = "neděle";

const char jan[] PROGMEM = "leden";
const char feb[] PROGMEM = "únor";
const char mar[] PROGMEM = "březen";
const char apr[] PROGMEM = "duben";
const char may[] PROGMEM = "květen";
const char jun[] PROGMEM = "červen";
const char jul[] PROGMEM = "červenec";
const char aug[] PROGMEM = "srpen";
const char sep[] PROGMEM = "září";
const char octt[] PROGMEM = "říjen";
const char nov[] PROGMEM = "listopad";
const char decc[] PROGMEM = "prosinec";

const char wn_N[]      PROGMEM = "SEVER";
const char wn_NNE[]    PROGMEM = "SSE";
const char wn_NE[]     PROGMEM = "SV";
const char wn_ENE[]    PROGMEM = "VSV";
const char wn_E[]      PROGMEM = "VÝCHOD";
const char wn_ESE[]    PROGMEM = "JJV";
const char wn_SE[]     PROGMEM = "JV";
const char wn_SSE[]    PROGMEM = "JJS";
const char wn_S[]      PROGMEM = "JIH";
const char wn_SSW[]    PROGMEM = "JZS";
const char wn_SW[]     PROGMEM = "JZ";
const char wn_WSW[]    PROGMEM = "ZZJ";
const char wn_W[]      PROGMEM = "ZÁPAD";
const char wn_WNW[]    PROGMEM = "ZSS";
const char wn_NW[]     PROGMEM = "ZS";
const char wn_NNW[]    PROGMEM = "SSZ";

const char* const dow[]     PROGMEM = { sun, mon, tue, wed, thu, fri, sat };
const char* const dowf[]    PROGMEM = { sunf, monf, tuef, wedf, thuf, frif, satf };
const char* const mnths[]   PROGMEM = { jan, feb, mar, apr, may, jun, jul, aug, sep, octt, nov, decc };
const char* const wind[]    PROGMEM = { wn_N, wn_NNE, wn_NE, wn_ENE, wn_E, wn_ESE, wn_SE, wn_SSE, wn_S, wn_SSW, wn_SW, wn_WSW, wn_W, wn_WNW, wn_NW, wn_NNW, wn_N };

const char    const_PlReady[]    PROGMEM = "[připraveno]";
const char  const_PlStopped[]    PROGMEM = "[zastaveno]";
const char  const_PlConnect[]    PROGMEM = "[připojuji]";
const char  const_DlgVolume[]    PROGMEM = "HLASITOST";
const char    const_DlgLost[]    PROGMEM = "* ZTRACENO *";
const char  const_DlgUpdate[]    PROGMEM = "* AKTUALIZACE *";
const char const_DlgNextion[]    PROGMEM = "NEXTION";
const char const_getWeather[]    PROGMEM = "";
const char  const_waitForSD[]    PROGMEM = "INDEX SD";

const char        apNameTxt[]    PROGMEM = "JMÉNO AP";
#ifdef AP_PASSWORD
  const char        apPassTxt[]    PROGMEM = "HESLO";
#else
  const char        apPassTxt[]    PROGMEM = "ŽÁDNÉ HESLO";
#endif

const char       bootstrFmt[]    PROGMEM = "Wi-fi: %s";
const char        apSettFmt[]    PROGMEM = "PŘIPOJTE SE A OTEVŘETE HTTP://%s/";

#ifdef UPDATEURL
  const char      updFirmware[]    PROGMEM = "Aktualizace firmwaru";
  const char         updFiles[]    PROGMEM = "Aktualizace souborů";
  const char        updFailed[]    PROGMEM = "Aktualizace neúspěšná";
#endif

#if EXT_WEATHER
const char       weatherFmt[]    PROGMEM = "%s, %.1f\011C \007 pocitově: %.1f\011C \007 tlak: %d hPa \007 vlhkost: %s%% \007 vítr: %.1f m/s [%s]";
#else
const char       weatherFmt[]    PROGMEM = "%s, %.1f\011C \007 tlak: %d hPa \007 vlhkost: %s%%";
#endif
const char     weatherUnits[]    PROGMEM = "metric";   /* standard, metric, imperial */
const char      weatherLang[]    PROGMEM = "cz";       /* https://openweathermap.org/current#multi */

#endif

