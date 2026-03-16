#ifndef dsp_full_loc
#define dsp_full_loc
#include <pgmspace.h>
/*************************************************************************************
    HOWTO:
    Copy this file to locale/displayL10n_custom.h
    and modify it
*************************************************************************************/
// Language: Bosnian
// IETF BCP 47: "bs-BA"
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

const char jan[] PROGMEM = "Januar";
const char feb[] PROGMEM = "Februar";
const char mar[] PROGMEM = "Mart";
const char apr[] PROGMEM = "April";
const char may[] PROGMEM = "Maj";
const char jun[] PROGMEM = "Jun";
const char jul[] PROGMEM = "Jul";
const char aug[] PROGMEM = "Avgust";
const char sep[] PROGMEM = "Septembar";
const char oct[] PROGMEM = "Oktobar";
const char nov[] PROGMEM = "Novembar";
const char dec[] PROGMEM = "Decembar";

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
const char* const mnths[]   PROGMEM = { jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };
const char* const wind[]    PROGMEM = { wn_N, wn_NNE, wn_NE, wn_ENE, wn_E, wn_ESE, wn_SE, wn_SSE, wn_S, wn_SSW, wn_SW, wn_WSW, wn_W, wn_WNW, wn_NW, wn_NNW, wn_N };

const char    const_PlReady[]    PROGMEM = "[spreman]";
const char  const_PlStopped[]    PROGMEM = "[zaustavljen]";
const char  const_PlConnect[]    PROGMEM = "[povezuje]";
const char  const_DlgVolume[]    PROGMEM = "GLASNOST";
const char    const_DlgLost[]    PROGMEM = "* NEMA VEZE *";
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
  const char        updFailed[]    PROGMEM = "Ažuriranje neuspješno";
#endif

const char weather_feelslike[]  PROGMEM = "osjeća se:";
const char weather_pressure[]   PROGMEM = "pritisak:";
const char weather_humidity[]   PROGMEM = "vlažnost:";
const char weather_wind[]       PROGMEM = "vjetar:";const char weather_loading[]    PROGMEM = "Preuzimanje vremenskih podataka...";

// WMO Weather Code Translations (for Open-Meteo)
const char w_clear_sky[]         PROGMEM = "Vedro nebo";
const char w_overcast[]          PROGMEM = "Oblačno";
const char w_foggy[]             PROGMEM = "Magla";
const char w_drizzle[]           PROGMEM = "Rosulja";
const char w_freezing_drizzle[]  PROGMEM = "Ledena rosulja";
const char w_rain[]              PROGMEM = "Kiša";
const char w_freezing_rain[]     PROGMEM = "Ledena kiša";
const char w_snow[]              PROGMEM = "Snijeg";
const char w_snow_grains[]       PROGMEM = "Zrnca snijega";
const char w_rain_showers[]      PROGMEM = "Pljuskovi";
const char w_snow_showers[]      PROGMEM = "Snijeg pljuskovi";
const char w_thunderstorm[]      PROGMEM = "Oluja";
const char w_thunderstorm_hail[] PROGMEM = "Oluja s grmljavinom";
#endif

