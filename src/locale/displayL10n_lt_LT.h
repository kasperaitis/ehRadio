#ifndef dsp_full_loc
#define dsp_full_loc
#include <pgmspace.h>
/*************************************************************************************
    HOWTO:
    Copy this file to locale/displayL10n_custom.h
    and modify it
*************************************************************************************/
// Language: Lithuanian
// IETF BCP 47: "lt-LT"
const char mon[] PROGMEM = "pr";
const char tue[] PROGMEM = "an";
const char wed[] PROGMEM = "tr";
const char thu[] PROGMEM = "kt";
const char fri[] PROGMEM = "pn";
const char sat[] PROGMEM = "št";
const char sun[] PROGMEM = "sk";

const char monf[] PROGMEM = "pirmadienis";
const char tuef[] PROGMEM = "antradienis";
const char wedf[] PROGMEM = "trečiadienis";
const char thuf[] PROGMEM = "ketvirtadienis";
const char frif[] PROGMEM = "penktadienis";
const char satf[] PROGMEM = "šeštadienis";
const char sunf[] PROGMEM = "sekmadienis";

const char jan[] PROGMEM = "sausio";
const char feb[] PROGMEM = "vasario";
const char mar[] PROGMEM = "kovo";
const char apr[] PROGMEM = "balandžio";
const char may[] PROGMEM = "gegužės";
const char jun[] PROGMEM = "birželio";
const char jul[] PROGMEM = "liepos";
const char aug[] PROGMEM = "rugpjūčio";
const char sep[] PROGMEM = "rugsėjo";
const char octt[] PROGMEM = "spalio";
const char nov[] PROGMEM = "lapkričio";
const char decc[] PROGMEM = "gruodžio";

const char wn_N[]      PROGMEM = "ŠIAURĖS";
const char wn_NNE[]    PROGMEM = "ŠŠR";
const char wn_NE[]     PROGMEM = "ŠR";
const char wn_ENE[]    PROGMEM = "RSR";
const char wn_E[]      PROGMEM = "RYTŲ";
const char wn_ESE[]    PROGMEM = "RPR";
const char wn_SE[]     PROGMEM = "PR";
const char wn_SSE[]    PROGMEM = "PPR";
const char wn_S[]      PROGMEM = "PIETŲ";
const char wn_SSW[]    PROGMEM = "PPV";
const char wn_SW[]     PROGMEM = "PV";
const char wn_WSW[]    PROGMEM = "VPV";
const char wn_W[]      PROGMEM = "VAKARŲ";
const char wn_WNW[]    PROGMEM = "VŠV";
const char wn_NW[]     PROGMEM = "ŠV";
const char wn_NNW[]    PROGMEM = "ŠŠV";

const char* const dow[]     PROGMEM = { sun, mon, tue, wed, thu, fri, sat };
const char* const dowf[]    PROGMEM = { sunf, monf, tuef, wedf, thuf, frif, satf };
const char* const mnths[]   PROGMEM = { jan, feb, mar, apr, may, jun, jul, aug, sep, octt, nov, decc };
const char* const wind[]    PROGMEM = { wn_N, wn_NNE, wn_NE, wn_ENE, wn_E, wn_ESE, wn_SE, wn_SSE, wn_S, wn_SSW, wn_SW, wn_WSW, wn_W, wn_WNW, wn_NW, wn_NNW, wn_N };

const char    const_PlReady[]    PROGMEM = "[paruošta]";
const char  const_PlStopped[]    PROGMEM = "[sustabdyta]";
const char  const_PlConnect[]    PROGMEM = "[jungiamasi]";
const char  const_DlgVolume[]    PROGMEM = "GARSAS";
const char    const_DlgLost[]    PROGMEM = "* ATSIJUNGĘS *";
const char  const_DlgUpdate[]    PROGMEM = "* Atnaujinama *";
const char const_DlgNextion[]    PROGMEM = "NEXTION";
const char const_getWeather[]    PROGMEM = "";
const char  const_waitForSD[]    PROGMEM = "INDEKSUOJAMA SD";

const char        apNameTxt[]    PROGMEM = "TAŠKO VARDAS";
#ifdef AP_PASSWORD
  const char        apPassTxt[]    PROGMEM = "SLAPTAŽODIS";
#else
  const char        apPassTxt[]    PROGMEM = "BE SLAPTAŽODŽIO";
#endif

const char       bootstrFmt[]    PROGMEM = "Wi-fi: %s";
const char        apSettFmt[]    PROGMEM = "PRISIJUNKITE IR ATIDARYKITE HTTP://%s/";

#ifdef UPDATEURL
  const char      updFirmware[]    PROGMEM = "Atnaujinama programinė įranga";
  const char         updFiles[]    PROGMEM = "Atnaujinami failai";
  const char        updFailed[]    PROGMEM = "Atnaujinimas nepavyko";
#endif

#if EXT_WEATHER
const char       weatherFmt[]    PROGMEM = "%s, %.1f\011C \007 jaučiasi: %.1f\011C \007 slėgis: %d hPa \007 drėgmė: %s%% \007 vėjas: %.1f m/s [%s]";
#else
const char       weatherFmt[]    PROGMEM = "%s, %.1f\011C \007 slėgis: %d hPa \007 drėgmė: %s%%";
#endif
const char     weatherUnits[]    PROGMEM = "metric";   /* standard, metric, imperial */
const char      weatherLang[]    PROGMEM = "lt";       /* https://openweathermap.org/current#multi */

#endif

