#ifndef dsp_full_loc
#define dsp_full_loc
#include <pgmspace.h>
/*************************************************************************************
    HOWTO:
    Copy this file to locale/displayL10n_custom.h
    and modify it
*************************************************************************************/
// Language: Swedish
// IETF BCP 47: "sv-SE"
const char mon[] PROGMEM = "må";
const char tue[] PROGMEM = "ti";
const char wed[] PROGMEM = "on";
const char thu[] PROGMEM = "to";
const char fri[] PROGMEM = "fr";
const char sat[] PROGMEM = "lö";
const char sun[] PROGMEM = "sö";

const char monf[] PROGMEM = "Måndag";
const char tuef[] PROGMEM = "Tisdag";
const char wedf[] PROGMEM = "Onsdag";
const char thuf[] PROGMEM = "Torsdag";
const char frif[] PROGMEM = "Fredag";
const char satf[] PROGMEM = "Lördag";
const char sunf[] PROGMEM = "Söndag";

const char jan[] PROGMEM = "Januari";
const char feb[] PROGMEM = "Februari";
const char mar[] PROGMEM = "Mars";
const char apr[] PROGMEM = "April";
const char may[] PROGMEM = "Maj";
const char jun[] PROGMEM = "Juni";
const char jul[] PROGMEM = "Juli";
const char aug[] PROGMEM = "Augusti";
const char sep[] PROGMEM = "September";
const char oct[] PROGMEM = "Oktober";
const char nov[] PROGMEM = "November";
const char dec[] PROGMEM = "December";

const char wn_N[]      PROGMEM = "NORD";
const char wn_NNE[]    PROGMEM = "NNE";
const char wn_NE[]     PROGMEM = "NE";
const char wn_ENE[]    PROGMEM = "ENE";
const char wn_E[]      PROGMEM = "ÖST";
const char wn_ESE[]    PROGMEM = "ESE";
const char wn_SE[]     PROGMEM = "SE";
const char wn_SSE[]    PROGMEM = "SSE";
const char wn_S[]      PROGMEM = "SYD";
const char wn_SSW[]    PROGMEM = "SSW";
const char wn_SW[]     PROGMEM = "SW";
const char wn_WSW[]    PROGMEM = "WSW";
const char wn_W[]      PROGMEM = "VÄST";
const char wn_WNW[]    PROGMEM = "WNW";
const char wn_NW[]     PROGMEM = "NW";
const char wn_NNW[]    PROGMEM = "NNW";

const char* const dow[]     PROGMEM = { sun, mon, tue, wed, thu, fri, sat };
const char* const dowf[]    PROGMEM = { sunf, monf, tuef, wedf, thuf, frif, satf };
const char* const mnths[]   PROGMEM = { jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };
const char* const wind[]    PROGMEM = { wn_N, wn_NNE, wn_NE, wn_ENE, wn_E, wn_ESE, wn_SE, wn_SSE, wn_S, wn_SSW, wn_SW, wn_WSW, wn_W, wn_WNW, wn_NW, wn_NNW, wn_N };

const char    const_PlReady[]    PROGMEM = "[redo]";
const char  const_PlStopped[]    PROGMEM = "[stoppad]";
const char  const_PlConnect[]    PROGMEM = "[ansluter]";
const char  const_DlgVolume[]    PROGMEM = "VOLYM";
const char    const_DlgLost[]    PROGMEM = "* ANSLUTNING FÖRLORAD *";
const char  const_DlgUpdate[]    PROGMEM = "* UPPDATERAR *";
const char const_DlgNextion[]    PROGMEM = "NEXTION";
const char  const_waitForSD[]    PROGMEM = "INDEXERA SD";

const char        apNameTxt[]    PROGMEM = "AP NAMN";
#ifdef AP_PASSWORD
  const char        apPassTxt[]    PROGMEM = "LÖSENORD";
#else
  const char        apPassTxt[]    PROGMEM = "INGET LÖSENORD";
#endif

const char       bootstrFmt[]    PROGMEM = "Wi-fi: %s";
const char        apSettFmt[]    PROGMEM = "ANSLUT OCH ÖPPNA HTTP://%s/";

#ifdef UPDATEURL
  const char      updFirmware[]    PROGMEM = "Uppdaterar firmware";
  const char         updFiles[]    PROGMEM = "Uppdaterar filer";
  const char        updFailed[]    PROGMEM = "Uppdatering misslyckades";
#endif

const char weather_feelslike[]  PROGMEM = "känns som:";
const char weather_pressure[]   PROGMEM = "tryck:";
const char weather_humidity[]   PROGMEM = "fuktighet:";
const char weather_wind[]       PROGMEM = "vind:";

#endif

