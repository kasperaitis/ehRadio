#ifndef dsp_full_loc
#define dsp_full_loc
#include <pgmspace.h>
/*************************************************************************************
    HOWTO:
    Copy this file to locale/displayL10n_custom.h
    and modify it
*************************************************************************************/
// Language: Dutch
// IETF BCP 47: "nl-NL"
const char mon[] PROGMEM = "ma";
const char tue[] PROGMEM = "di";
const char wed[] PROGMEM = "wo";
const char thu[] PROGMEM = "do";
const char fri[] PROGMEM = "vr";
const char sat[] PROGMEM = "za";
const char sun[] PROGMEM = "zo";

const char monf[] PROGMEM = "Maandag";
const char tuef[] PROGMEM = "Dinsdag";
const char wedf[] PROGMEM = "Woensdag";
const char thuf[] PROGMEM = "Donderdag";
const char frif[] PROGMEM = "Vrijdag";
const char satf[] PROGMEM = "Zaterdag";
const char sunf[] PROGMEM = "Zondag";

const char jan[] PROGMEM = "Januari";
const char feb[] PROGMEM = "Februari";
const char mar[] PROGMEM = "Maart";
const char apr[] PROGMEM = "April";
const char may[] PROGMEM = "Mei";
const char jun[] PROGMEM = "Juni";
const char jul[] PROGMEM = "Juli";
const char aug[] PROGMEM = "Augustus";
const char sep[] PROGMEM = "September";
const char oct[] PROGMEM = "Oktober";
const char nov[] PROGMEM = "November";
const char dec[] PROGMEM = "December";

const char wn_N[]      PROGMEM = "NOORD";
const char wn_NNE[]    PROGMEM = "NNE";
const char wn_NE[]     PROGMEM = "NE";
const char wn_ENE[]    PROGMEM = "ENE";
const char wn_E[]      PROGMEM = "OOST";
const char wn_ESE[]    PROGMEM = "ESE";
const char wn_SE[]     PROGMEM = "SE";
const char wn_SSE[]    PROGMEM = "SSE";
const char wn_S[]      PROGMEM = "ZUID";
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

const char    const_PlReady[]    PROGMEM = "[klaar]";
const char  const_PlStopped[]    PROGMEM = "[gestopt]";
const char  const_PlConnect[]    PROGMEM = "[verbinden]";
const char  const_DlgVolume[]    PROGMEM = "VOLUME";
const char    const_DlgLost[]    PROGMEM = "* GEEN VERBINDING *";
const char  const_DlgUpdate[]    PROGMEM = "* BIJWERKEN *";
const char const_DlgNextion[]    PROGMEM = "NEXTION";
const char  const_waitForSD[]    PROGMEM = "INDEX SD";

const char        apNameTxt[]    PROGMEM = "AP NAAM";
#ifdef AP_PASSWORD
  const char        apPassTxt[]    PROGMEM = "WACHTWOORD";
#else
  const char        apPassTxt[]    PROGMEM = "ZONDER WACHTWOORD";
#endif

const char       bootstrFmt[]    PROGMEM = "Wi-fi: %s";
const char        apSettFmt[]    PROGMEM = "VERBIND & OPEN HTTP://%s/";

#ifdef UPDATEURL
  const char      updFirmware[]    PROGMEM = "Firmware bijwerken";
  const char         updFiles[]    PROGMEM = "Bestanden bijwerken";
  const char        updFailed[]    PROGMEM = "Bijwerken mislukt";
#endif

const char weather_feelslike[]  PROGMEM = "gevoelstemperatuur:";
const char weather_pressure[]   PROGMEM = "druk:";
const char weather_humidity[]   PROGMEM = "vochtigheid:";
const char weather_wind[]       PROGMEM = "wind:";

#endif

