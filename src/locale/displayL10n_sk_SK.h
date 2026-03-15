#ifndef dsp_full_loc
#define dsp_full_loc
#include <pgmspace.h>
/*************************************************************************************
    HOWTO:
    Copy this file to locale/displayL10n_custom.h
    and modify it
*************************************************************************************/
// Language: Slovak
// IETF BCP 47: "sk-SK"
const char mon[] PROGMEM = "po";
const char tue[] PROGMEM = "ut";
const char wed[] PROGMEM = "st";
const char thu[] PROGMEM = "št";
const char fri[] PROGMEM = "pi";
const char sat[] PROGMEM = "so";
const char sun[] PROGMEM = "ne";

const char monf[] PROGMEM = "Pondelok";
const char tuef[] PROGMEM = "Utorok";
const char wedf[] PROGMEM = "Streda";
const char thuf[] PROGMEM = "Štvrtok";
const char frif[] PROGMEM = "Piatok";
const char satf[] PROGMEM = "Sobota";
const char sunf[] PROGMEM = "Nedeľa";

const char jan[] PROGMEM = "Január";
const char feb[] PROGMEM = "Február";
const char mar[] PROGMEM = "Marec";
const char apr[] PROGMEM = "Apríl";
const char may[] PROGMEM = "Máj";
const char jun[] PROGMEM = "Jún";
const char jul[] PROGMEM = "Júl";
const char aug[] PROGMEM = "August";
const char sep[] PROGMEM = "September";
const char oct[] PROGMEM = "Október";
const char nov[] PROGMEM = "November";
const char dec[] PROGMEM = "December";

const char wn_N[]      PROGMEM = "SEVER";
const char wn_NNE[]    PROGMEM = "NNE";
const char wn_NE[]     PROGMEM = "NE";
const char wn_ENE[]    PROGMEM = "ENE";
const char wn_E[]      PROGMEM = "VÝCHOD";
const char wn_ESE[]    PROGMEM = "ESE";
const char wn_SE[]     PROGMEM = "SE";
const char wn_SSE[]    PROGMEM = "SSE";
const char wn_S[]      PROGMEM = "JUH";
const char wn_SSW[]    PROGMEM = "SSW";
const char wn_SW[]     PROGMEM = "SW";
const char wn_WSW[]    PROGMEM = "WSW";
const char wn_W[]      PROGMEM = "ZÁPAD";
const char wn_WNW[]    PROGMEM = "WNW";
const char wn_NW[]     PROGMEM = "NW";
const char wn_NNW[]    PROGMEM = "NNW";

const char* const dow[]     PROGMEM = { sun, mon, tue, wed, thu, fri, sat };
const char* const dowf[]    PROGMEM = { sunf, monf, tuef, wedf, thuf, frif, satf };
const char* const mnths[]   PROGMEM = { jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };
const char* const wind[]    PROGMEM = { wn_N, wn_NNE, wn_NE, wn_ENE, wn_E, wn_ESE, wn_SE, wn_SSE, wn_S, wn_SSW, wn_SW, wn_WSW, wn_W, wn_WNW, wn_NW, wn_NNW, wn_N };

const char    const_PlReady[]    PROGMEM = "[pripravený]";
const char  const_PlStopped[]    PROGMEM = "[zastavené]";
const char  const_PlConnect[]    PROGMEM = "[pripájanie]";
const char  const_DlgVolume[]    PROGMEM = "HLASITOSŤ";
const char    const_DlgLost[]    PROGMEM = "* STRATENÉ PRIPOJENIE *";
const char  const_DlgUpdate[]    PROGMEM = "* AKTUALIZÁCIA *";
const char const_DlgNextion[]    PROGMEM = "NEXTION";
const char  const_waitForSD[]    PROGMEM = "INDEX SD";

const char        apNameTxt[]    PROGMEM = "NÁZOV AP";
#ifdef AP_PASSWORD
  const char        apPassTxt[]    PROGMEM = "HESLO";
#else
  const char        apPassTxt[]    PROGMEM = "BEZ HESLA";
#endif

const char       bootstrFmt[]    PROGMEM = "Wi-fi: %s";
const char        apSettFmt[]    PROGMEM = "PRIPOJTE SA A OTVORTE HTTP://%s/";

#ifdef UPDATEURL
  const char      updFirmware[]    PROGMEM = "Aktualizuje sa firmware";
  const char         updFiles[]    PROGMEM =  "Aktualizujú sa súbory";
  const char        updFailed[]    PROGMEM = "Aktualizácia zlyhala";
#endif

const char weather_feelslike[]  PROGMEM = "pocit:";
const char weather_pressure[]   PROGMEM = "tlak:";
const char weather_humidity[]   PROGMEM = "vlhkosť:";
const char weather_wind[]       PROGMEM = "vietor:";

#endif

