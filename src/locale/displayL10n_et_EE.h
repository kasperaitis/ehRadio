#ifndef dsp_full_loc
#define dsp_full_loc
#include <pgmspace.h>
/*************************************************************************************
    HOWTO:
    Copy this file to locale/displayL10n_custom.h
    and modify it
*************************************************************************************/
// Language: Estonian
// IETF BCP 47: "et-EE"
const char mon[] PROGMEM = "es";
const char tue[] PROGMEM = "te";
const char wed[] PROGMEM = "ko";
const char thu[] PROGMEM = "ne";
const char fri[] PROGMEM = "re";
const char sat[] PROGMEM = "la";
const char sun[] PROGMEM = "pä";

const char monf[] PROGMEM = "Esmaspäev";
const char tuef[] PROGMEM = "Teisipäev";
const char wedf[] PROGMEM = "Kolmapäev";
const char thuf[] PROGMEM = "Neljapäev";
const char frif[] PROGMEM = "Reede";
const char satf[] PROGMEM = "Laupäev";
const char sunf[] PROGMEM = "Pühapäev";

const char jan[] PROGMEM = "Jaanuar";
const char feb[] PROGMEM = "Veebruar";
const char mar[] PROGMEM = "Märts";
const char apr[] PROGMEM = "Aprill";
const char may[] PROGMEM = "Mai";
const char jun[] PROGMEM = "Juuni";
const char jul[] PROGMEM = "Juuli";
const char aug[] PROGMEM = "August";
const char sep[] PROGMEM = "September";
const char oct[] PROGMEM = "Oktoober";
const char nov[] PROGMEM = "November";
const char dec[] PROGMEM = "Detsember";

const char wn_N[]      PROGMEM = "PÕHJA";
const char wn_NNE[]    PROGMEM = "NNE";
const char wn_NE[]     PROGMEM = "NE";
const char wn_ENE[]    PROGMEM = "ENE";
const char wn_E[]      PROGMEM = "IDA";
const char wn_ESE[]    PROGMEM = "ESE";
const char wn_SE[]     PROGMEM = "SE";
const char wn_SSE[]    PROGMEM = "SSE";
const char wn_S[]      PROGMEM = "LÕUNA";
const char wn_SSW[]    PROGMEM = "SSW";
const char wn_SW[]     PROGMEM = "SW";
const char wn_WSW[]    PROGMEM = "WSW";
const char wn_W[]      PROGMEM = "LÄÄN";
const char wn_WNW[]    PROGMEM = "WNW";
const char wn_NW[]     PROGMEM = "NW";
const char wn_NNW[]    PROGMEM = "NNW";

const char* const dow[]     PROGMEM = { sun, mon, tue, wed, thu, fri, sat };
const char* const dowf[]    PROGMEM = { sunf, monf, tuef, wedf, thuf, frif, satf };
const char* const mnths[]   PROGMEM = { jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };
const char* const wind[]    PROGMEM = { wn_N, wn_NNE, wn_NE, wn_ENE, wn_E, wn_ESE, wn_SE, wn_SSE, wn_S, wn_SSW, wn_SW, wn_WSW, wn_W, wn_WNW, wn_NW, wn_NNW, wn_N };

const char    const_PlReady[]    PROGMEM = "[valmis]";
const char  const_PlStopped[]    PROGMEM = "[peatatud]";
const char  const_PlConnect[]    PROGMEM = "[ühendamine]";
const char  const_DlgVolume[]    PROGMEM = "HELITUVEGUS";
const char    const_DlgLost[]    PROGMEM = "* ÜHENDUS KATKENUD *";
const char  const_DlgUpdate[]    PROGMEM = "* UUENDAMINE *";
const char const_DlgNextion[]    PROGMEM = "NEXTION";
const char  const_waitForSD[]    PROGMEM = "INDEKSEERIMINE SD";

const char        apNameTxt[]    PROGMEM = "AP NIMI";
#ifdef AP_PASSWORD
  const char        apPassTxt[]    PROGMEM = "PAROOL";
#else
  const char        apPassTxt[]    PROGMEM = "ILMA PAROOLITA";
#endif

const char       bootstrFmt[]    PROGMEM = "Wi-fi: %s";
const char        apSettFmt[]    PROGMEM = "ÜHENDAGE JA AVAGE HTTP://%s/";

#ifdef UPDATEURL
  const char      updFirmware[]    PROGMEM = "Püsivara värskendamine";
  const char         updFiles[]    PROGMEM = "Failide värskendamine";
  const char        updFailed[]    PROGMEM = "Värskendamine ebaõnnestus";
#endif

const char weather_feelslike[]  PROGMEM = "tundub:";
const char weather_pressure[]   PROGMEM = "rõhk:";
const char weather_humidity[]   PROGMEM = "niiskus:";
const char weather_wind[]       PROGMEM = "tuul:";
const char weather_loading[]    PROGMEM = "Ilmaandmete laadimine...";

// WMO Weather Code Translations (for Open-Meteo)
const char w_clear_sky[]         PROGMEM = "Selge taevas";
const char w_overcast[]          PROGMEM = "Pilves";
const char w_foggy[]             PROGMEM = "Udu";
const char w_drizzle[]           PROGMEM = "Uduvihm";
const char w_freezing_drizzle[]  PROGMEM = "Külmuv uduvihm";
const char w_rain[]              PROGMEM = "Vihm";
const char w_freezing_rain[]     PROGMEM = "Külmuv vihm";
const char w_snow[]              PROGMEM = "Lumi";
const char w_snow_grains[]       PROGMEM = "Lumeterakesed";
const char w_rain_showers[]      PROGMEM = "Vihmahood";
const char w_snow_showers[]      PROGMEM = "Lumehood";
const char w_thunderstorm[]      PROGMEM = "Äikest orm";
const char w_thunderstorm_hail[] PROGMEM = "Äikestorm rahehooga";

#endif

