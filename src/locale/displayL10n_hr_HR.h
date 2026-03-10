#ifndef dsp_full_loc
#define dsp_full_loc
#include <pgmspace.h>
/*************************************************************************************
    HOWTO:
    Copy this file to locale/displayL10n_custom.h
    and modify it
*************************************************************************************/
// Language: Croatian
// IETF BCP 47: "hr-HR"
const char mon[] PROGMEM = "po";
const char tue[] PROGMEM = "ut";
const char wed[] PROGMEM = "sr";
const char thu[] PROGMEM = "če";
const char fri[] PROGMEM = "pe";
const char sat[] PROGMEM = "su";
const char sun[] PROGMEM = "ne";

const char monf[] PROGMEM = "Ponedjeljak";
const char tuef[] PROGMEM = "Utorak";
const char wedf[] PROGMEM = "Srijeda";
const char thuf[] PROGMEM = "Četvrtak";
const char frif[] PROGMEM = "Petak";
const char satf[] PROGMEM = "Subota";
const char sunf[] PROGMEM = "Nedjelja";

const char jan[] PROGMEM = "Siječanj";
const char feb[] PROGMEM = "Veljača";
const char mar[] PROGMEM = "Ožujak";
const char apr[] PROGMEM = "Travanj";
const char may[] PROGMEM = "Svibanj";
const char jun[] PROGMEM = "Lipanj";
const char jul[] PROGMEM = "Srpanj";
const char aug[] PROGMEM = "Kolovoz";
const char sep[] PROGMEM = "Rujan";
const char octt[] PROGMEM = "Listopad";
const char nov[] PROGMEM = "Studeni";
const char decc[] PROGMEM = "Prosinac";

const char wn_N[]      PROGMEM = "SJEVER";
const char wn_NNE[]    PROGMEM = "NNE";
const char wn_NE[]     PROGMEM = "NE";
const char wn_ENE[]    PROGMEM = "ENE";
const char wn_E[]      PROGMEM = "ISTOK";
const char wn_ESE[]    PROGMEM = "ESE";
const char wn_SE[]     PROGMEM = "SE";
const char wn_SSE[]    PROGMEM = "SSE";
const char wn_S[]      PROGMEM = "JUG";
const char wn_SSW[]    PROGMEM = "SSW";
const char wn_SW[]     PROGMEM = "SW";
const char wn_WSW[]    PROGMEM = "WSW";
const char wn_W[]      PROGMEM = "ZAPAD";
const char wn_WNW[]    PROGMEM = "WNW";
const char wn_NW[]     PROGMEM = "NW";
const char wn_NNW[]    PROGMEM = "NNW";

const char* const dow[]     PROGMEM = { sun, mon, tue, wed, thu, fri, sat };
const char* const dowf[]    PROGMEM = { sunf, monf, tuef, wedf, thuf, frif, satf };
const char* const mnths[]   PROGMEM = { jan, feb, mar, apr, may, jun, jul, aug, sep, octt, nov, decc };
const char* const wind[]    PROGMEM = { wn_N, wn_NNE, wn_NE, wn_ENE, wn_E, wn_ESE, wn_SE, wn_SSE, wn_S, wn_SSW, wn_SW, wn_WSW, wn_W, wn_WNW, wn_NW, wn_NNW, wn_N };

const char    const_PlReady[]    PROGMEM = "[spreman]";
const char  const_PlStopped[]    PROGMEM = "[zaustavljeno]";
const char  const_PlConnect[]    PROGMEM = "[povezivanje]";
const char  const_DlgVolume[]    PROGMEM = "GLASNOĆA";
const char    const_DlgLost[]    PROGMEM = "* NEMA VEZE *";
const char  const_DlgUpdate[]    PROGMEM = "* AŽURIRANJE *";
const char const_DlgNextion[]    PROGMEM = "NEXTION";
const char const_getWeather[]    PROGMEM = "";
const char  const_waitForSD[]    PROGMEM = "INDEKS SD";

const char        apNameTxt[]    PROGMEM = "IME AP";
#ifdef AP_PASSWORD
  const char        apPassTxt[]    PROGMEM = "LOZINKA";
#else
  const char        apPassTxt[]    PROGMEM = "BEZ LOZINKE";
#endif

const char       bootstrFmt[]    PROGMEM = "Wi-fi: %s";
const char        apSettFmt[]    PROGMEM = "POVEŽI SE I OTVORI HTTP://%s/";

#ifdef UPDATEURL
  const char      updFirmware[]    PROGMEM = "Ažuriranje firmvera";
  const char         updFiles[]    PROGMEM = "Ažuriranje datoteka";
  const char        updFailed[]    PROGMEM = "Neuspjelo ažuriranje";
#endif

#if EXT_WEATHER
const char       weatherFmt[]    PROGMEM = "%s, %.1f\011C \007 osjeća se kao: %.1f\011C \007 tlak: %d hPa \007 vlaga: %s%% \007 vjetar: %.1f m/s [%s]";
#else
const char       weatherFmt[]    PROGMEM = "%s, %.1f\011C \007 tlak: %d hPa \007 vlaga: %s%%";
#endif
const char     weatherUnits[]    PROGMEM = "metric";   /* standard, metric, imperial */
const char      weatherLang[]    PROGMEM = "hr";       /* https://openweathermap.org/current#multi */

#endif

