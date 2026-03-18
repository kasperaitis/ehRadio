#ifndef dsp_full_loc
#define dsp_full_loc
#include <pgmspace.h>
/*************************************************************************************
    HOWTO:
    Copy this file to locale/displayL10n_custom.h
    and modify it
*************************************************************************************/
// Language: Icelandic
// IETF BCP 47: "is-IS"
const char mon[] PROGMEM = "ma";
const char tue[] PROGMEM = "ti";
const char wed[] PROGMEM = "mi";
const char thu[] PROGMEM = "fi";
const char fri[] PROGMEM = "fö";
const char sat[] PROGMEM = "la";
const char sun[] PROGMEM = "su";

const char monf[] PROGMEM = "Mánudagur";
const char tuef[] PROGMEM = "Þriðjudagur";
const char wedf[] PROGMEM = "Miðvikudagur";
const char thuf[] PROGMEM = "Fimmtudagur";
const char frif[] PROGMEM = "Föstudagur";
const char satf[] PROGMEM = "Laugardagur";
const char sunf[] PROGMEM = "Sunnudagur";

const char jan[] PROGMEM = "Janúar";
const char feb[] PROGMEM = "Febrúar";
const char mar[] PROGMEM = "Mars";
const char apr[] PROGMEM = "Apríl";
const char may[] PROGMEM = "Maí";
const char jun[] PROGMEM = "Júní";
const char jul[] PROGMEM = "Júlí";
const char aug[] PROGMEM = "Ágúst";
const char sep[] PROGMEM = "September";
const char oct[] PROGMEM = "Október";
const char nov[] PROGMEM = "Nóvember";
const char dec[] PROGMEM = "Desember";

const char wn_N[]      PROGMEM = "NORÐUR";
const char wn_NNE[]    PROGMEM = "NNE";
const char wn_NE[]     PROGMEM = "NE";
const char wn_ENE[]    PROGMEM = "ENE";
const char wn_E[]      PROGMEM = "AUSTUR";
const char wn_ESE[]    PROGMEM = "ESE";
const char wn_SE[]     PROGMEM = "SE";
const char wn_SSE[]    PROGMEM = "SSE";
const char wn_S[]      PROGMEM = "SUÐUR";
const char wn_SSW[]    PROGMEM = "SSW";
const char wn_SW[]     PROGMEM = "SW";
const char wn_WSW[]    PROGMEM = "WSW";
const char wn_W[]      PROGMEM = "VESTUR";
const char wn_WNW[]    PROGMEM = "WNW";
const char wn_NW[]     PROGMEM = "NW";
const char wn_NNW[]    PROGMEM = "NNW";

const char* const dow[]     PROGMEM = { sun, mon, tue, wed, thu, fri, sat };
const char* const dowf[]    PROGMEM = { sunf, monf, tuef, wedf, thuf, frif, satf };
const char* const mnths[]   PROGMEM = { jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };
const char* const wind[]    PROGMEM = { wn_N, wn_NNE, wn_NE, wn_ENE, wn_E, wn_ESE, wn_SE, wn_SSE, wn_S, wn_SSW, wn_SW, wn_WSW, wn_W, wn_WNW, wn_NW, wn_NNW, wn_N };

const char    const_PlReady[]    PROGMEM = "[tilbúinn]";
const char  const_PlStopped[]    PROGMEM = "[stöðvaður]";
const char  const_PlConnect[]    PROGMEM = "[tengist]";
const char  const_DlgVolume[]    PROGMEM = "HLJÓÐSTYRKUR";
const char    const_DlgLost[]    PROGMEM = "* TENGING BROTIN *";
const char  const_DlgUpdate[]    PROGMEM = "* UPPFYLLING *";
const char const_DlgNextion[]    PROGMEM = "NEXTION";
const char  const_waitForSD[]    PROGMEM = "INDEKS SD";

const char        apNameTxt[]    PROGMEM = "AP NAFN";
#ifdef AP_PASSWORD
  const char        apPassTxt[]    PROGMEM = "LYKILORÐ";
#else
  const char        apPassTxt[]    PROGMEM = "ENGIN LYKILORÐ";
#endif

const char       bootstrFmt[]    PROGMEM = "Wi-fi: %s";
const char        apSettFmt[]    PROGMEM = "TENGIÐ & OPIÐ HTTP://%s/";

#ifdef UPDATEURL
  const char      updFirmware[]    PROGMEM = "Uppfæri firmware";
  const char         updFiles[]    PROGMEM = "Uppfæri skrár";
  const char        updFailed[]    PROGMEM = "Uppfærsla mistókst";
#endif

const char weather_feelslike[]  PROGMEM = "finnst:";
const char weather_pressure[]   PROGMEM = "þrýstingur:";
const char weather_humidity[]   PROGMEM = "raki:";
const char weather_wind[]       PROGMEM = "vindur:";
const char weather_loading[]    PROGMEM = "Sæki veðurgögn...";

// WMO Weather Code Translations (for Open-Meteo)
const char w_clear_sky[]         PROGMEM = "H eimskt himinn";
const char w_overcast[]          PROGMEM = "Skyggt";
const char w_foggy[]             PROGMEM = "Þ oka";
const char w_drizzle[]           PROGMEM = "Strokregn";
const char w_freezing_drizzle[]  PROGMEM = "Froststrokregn";
const char w_rain[]              PROGMEM = "Regn";
const char w_freezing_rain[]     PROGMEM = "Frostregn";
const char w_snow[]              PROGMEM = "Snær";
const char w_snow_grains[]       PROGMEM = "Snjókorn";
const char w_rain_showers[]      PROGMEM = "Skafregn";
const char w_snow_showers[]      PROGMEM = "Snjókafol";
const char w_thunderstorm[]      PROGMEM = "Él veður";
const char w_thunderstorm_hail[] PROGMEM = "Élveður með hagli";

#endif

