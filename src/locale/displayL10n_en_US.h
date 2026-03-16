#ifndef dsp_full_loc
#define dsp_full_loc
#include <pgmspace.h>
/*************************************************************************************
    HOWTO:
    Copy this file to locale/displayL10n_custom.h
    and modify it
*************************************************************************************/
// Language: US English
// IETF BCP 47: "en-US"
const char mon[] PROGMEM = "Mo";
const char tue[] PROGMEM = "Tu";
const char wed[] PROGMEM = "We";
const char thu[] PROGMEM = "Th";
const char fri[] PROGMEM = "Fr";
const char sat[] PROGMEM = "Sa";
const char sun[] PROGMEM = "Su";

const char monf[] PROGMEM = "Monday";
const char tuef[] PROGMEM = "Tuesday";
const char wedf[] PROGMEM = "Wednesday";
const char thuf[] PROGMEM = "Thursday";
const char frif[] PROGMEM = "Friday";
const char satf[] PROGMEM = "Saturday";
const char sunf[] PROGMEM = "Sunday";

const char jan[] PROGMEM = "January";
const char feb[] PROGMEM = "February";
const char mar[] PROGMEM = "March";
const char apr[] PROGMEM = "April";
const char may[] PROGMEM = "May";
const char jun[] PROGMEM = "June";
const char jul[] PROGMEM = "July";
const char aug[] PROGMEM = "August";
const char sep[] PROGMEM = "September";
const char oct[] PROGMEM = "October";
const char nov[] PROGMEM = "November";
const char dec[] PROGMEM = "December";

const char wn_N[]      PROGMEM = "NORTH";
const char wn_NNE[]    PROGMEM = "NNE";
const char wn_NE[]     PROGMEM = "NE";
const char wn_ENE[]    PROGMEM = "ENE";
const char wn_E[]      PROGMEM = "EAST";
const char wn_ESE[]    PROGMEM = "ESE";
const char wn_SE[]     PROGMEM = "SE";
const char wn_SSE[]    PROGMEM = "SSE";
const char wn_S[]      PROGMEM = "SOUTH";
const char wn_SSW[]    PROGMEM = "SSW";
const char wn_SW[]     PROGMEM = "SW";
const char wn_WSW[]    PROGMEM = "WSW";
const char wn_W[]      PROGMEM = "WEST";
const char wn_WNW[]    PROGMEM = "WNW";
const char wn_NW[]     PROGMEM = "NW";
const char wn_NNW[]    PROGMEM = "NNW";

const char* const dow[]     PROGMEM = { sun, mon, tue, wed, thu, fri, sat };
const char* const dowf[]    PROGMEM = { sunf, monf, tuef, wedf, thuf, frif, satf };
const char* const mnths[]   PROGMEM = { jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };
const char* const wind[]    PROGMEM = { wn_N, wn_NNE, wn_NE, wn_ENE, wn_E, wn_ESE, wn_SE, wn_SSE, wn_S, wn_SSW, wn_SW, wn_WSW, wn_W, wn_WNW, wn_NW, wn_NNW, wn_N };

const char    const_PlReady[]    PROGMEM = "[ready]";
const char  const_PlStopped[]    PROGMEM = "[stopped]";
const char  const_PlConnect[]    PROGMEM = "[connecting]";
const char  const_DlgVolume[]    PROGMEM = "VOLUME";
const char    const_DlgLost[]    PROGMEM = "* LOST *";
const char  const_DlgUpdate[]    PROGMEM = "* UPDATING *";
const char const_DlgNextion[]    PROGMEM = "NEXTION";
const char  const_waitForSD[]    PROGMEM = "INDEX SD";

const char        apNameTxt[]    PROGMEM = "AP NAME";
#ifdef AP_PASSWORD
  const char        apPassTxt[]    PROGMEM = "PASSWORD";
#else
  const char        apPassTxt[]    PROGMEM = "NO PASSWORD";
#endif

const char       bootstrFmt[]    PROGMEM = "Wi-fi: %s";
const char        apSettFmt[]    PROGMEM = "CONNECT & OPEN HTTP://%s/";

#ifdef UPDATEURL
  const char      updFirmware[]    PROGMEM = "Updating Firmware";
  const char         updFiles[]    PROGMEM = "Updating Files";
  const char        updFailed[]    PROGMEM = "Update Failed";
#endif

const char weather_feelslike[]  PROGMEM = "feels like:";
const char weather_pressure[]   PROGMEM = "pressure:";
const char weather_humidity[]   PROGMEM = "humidity:";
const char weather_wind[]       PROGMEM = "wind:";
const char weather_loading[]    PROGMEM = "Getting current weather...";

// WMO Weather Code Translations (for Open-Meteo)
const char w_clear_sky[]         PROGMEM = "Clear sky";
const char w_overcast[]          PROGMEM = "Overcast";
const char w_foggy[]             PROGMEM = "Fog";
const char w_drizzle[]           PROGMEM = "Drizzle";
const char w_freezing_drizzle[]  PROGMEM = "Freezing drizzle";
const char w_rain[]              PROGMEM = "Rain";
const char w_freezing_rain[]     PROGMEM = "Freezing rain";
const char w_snow[]              PROGMEM = "Snow";
const char w_snow_grains[]       PROGMEM = "Snow grains";
const char w_rain_showers[]      PROGMEM = "Rain showers";
const char w_snow_showers[]      PROGMEM = "Snow showers";
const char w_thunderstorm[]      PROGMEM = "Thunderstorm";
const char w_thunderstorm_hail[] PROGMEM = "Thunderstorm with hail";

#endif

