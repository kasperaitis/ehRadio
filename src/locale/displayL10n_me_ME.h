#ifndef dsp_full_loc
#define dsp_full_loc
#include <pgmspace.h>
/*************************************************************************************
    HOWTO:
    Copy this file to locale/displayL10n_custom.h
    and modify it
*************************************************************************************/
// Language: Montenegrin
// IETF BCP 47: "me-ME"
const char mon[] PROGMEM = "po";
const char tue[] PROGMEM = "ut";
const char wed[] PROGMEM = "sr";
const char thu[] PROGMEM = "če";
const char fri[] PROGMEM = "pe";
const char sat[] PROGMEM = "su";
const char sun[] PROGMEM = "ne";

const char monf[] PROGMEM = "ponedjeljak";
const char tuef[] PROGMEM = "utorak";
const char wedf[] PROGMEM = "srijeda";
const char thuf[] PROGMEM = "četvrtak";
const char frif[] PROGMEM = "petak";
const char satf[] PROGMEM = "subota";
const char sunf[] PROGMEM = "nedjelja";

const char jan[] PROGMEM = "januar";
const char feb[] PROGMEM = "februar";
const char mar[] PROGMEM = "mart";
const char apr[] PROGMEM = "april";
const char may[] PROGMEM = "maj";
const char jun[] PROGMEM = "jun";
const char jul[] PROGMEM = "jul";
const char aug[] PROGMEM = "avgust";
const char sep[] PROGMEM = "septembar";
const char oct[] PROGMEM = "oktobar";
const char nov[] PROGMEM = "novembar";
const char dec[] PROGMEM = "decembar";

const char wn_N[]      PROGMEM = "SJEVER";
const char wn_NNE[]    PROGMEM = "SSV";
const char wn_NE[]     PROGMEM = "SV";
const char wn_ENE[]    PROGMEM = "VSV";
const char wn_E[]      PROGMEM = "ISTOK";
const char wn_ESE[]    PROGMEM = "VJV";
const char wn_SE[]     PROGMEM = "JV";
const char wn_SSE[]    PROGMEM = "JJV";
const char wn_S[]      PROGMEM = "JUG";
const char wn_SSW[]    PROGMEM = "JJZ";
const char wn_SW[]     PROGMEM = "JZ";
const char wn_WSW[]    PROGMEM = "ZZJ";
const char wn_W[]      PROGMEM = "ZAPAD";
const char wn_WNW[]    PROGMEM = "ZZS";
const char wn_NW[]     PROGMEM = "ZS";
const char wn_NNW[]    PROGMEM = "SNS";

const char* const dow[]     PROGMEM = { sun, mon, tue, wed, thu, fri, sat };
const char* const dowf[]    PROGMEM = { sunf, monf, tuef, wedf, thuf, frif, satf };
const char* const mnths[]   PROGMEM = { jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };
const char* const wind[]    PROGMEM = { wn_N, wn_NNE, wn_NE, wn_ENE, wn_E, wn_ESE, wn_SE, wn_SSE, wn_S, wn_SSW, wn_SW, wn_WSW, wn_W, wn_WNW, wn_NW, wn_NNW, wn_N };

const char    const_PlReady[]    PROGMEM = "[spremno]";
const char  const_PlStopped[]    PROGMEM = "[zaustavljeno]";
const char  const_PlConnect[]    PROGMEM = "[povezivanje]";
const char  const_DlgVolume[]    PROGMEM = "JAČINA";
const char    const_DlgLost[]    PROGMEM = "* PREKINUTO *";
const char  const_DlgUpdate[]    PROGMEM = "* AŽURIRANJE *";
const char const_DlgNextion[]    PROGMEM = "NEXTION";
const char  const_waitForSD[]    PROGMEM = "INDEKS SD";

const char        apNameTxt[]    PROGMEM = "IME AP";
#ifdef AP_PASSWORD
  const char        apPassTxt[]    PROGMEM = "LOZINKA";
#else
  const char        apPassTxt[]    PROGMEM = "BEZ LOZINKE";
#endif

const char       bootstrFmt[]    PROGMEM = "Wi-fi: %s";
const char        apSettFmt[]    PROGMEM = "POVEŽITE SE I OTVORITE HTTP://%s/";

#ifdef UPDATEURL
  const char      updFirmware[]    PROGMEM = "Ažuriranje firmvera";
  const char         updFiles[]    PROGMEM = "Ažuriranje datoteka";
  const char        updFailed[]    PROGMEM = "Ažuriranje nije uspjelo";
#endif

const char weather_feelslike[]  PROGMEM = "осећај:";
const char weather_pressure[]   PROGMEM = "притисак:";
const char weather_humidity[]   PROGMEM = "влажност:";
const char weather_wind[]       PROGMEM = "ветар:";

#endif

