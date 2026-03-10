#ifndef dsp_full_loc
#define dsp_full_loc
#include <pgmspace.h>
/*************************************************************************************
    HOWTO:
    Copy this file to locale/displayL10n_custom.h
    and modify it
*************************************************************************************/
// Language: Greek
// IETF BCP 47: "el-GR"
const char mon[] PROGMEM = "Δε";
const char tue[] PROGMEM = "Τρ";
const char wed[] PROGMEM = "Τε";
const char thu[] PROGMEM = "Πέ";
const char fri[] PROGMEM = "Πα";
const char sat[] PROGMEM = "Σά";
const char sun[] PROGMEM = "Κυ";

const char monf[] PROGMEM = "Δευτέρα";
const char tuef[] PROGMEM = "Τρίτη";
const char wedf[] PROGMEM = "Τετάρτη";
const char thuf[] PROGMEM = "Πέμπτη";
const char frif[] PROGMEM = "Παρασκευή";
const char satf[] PROGMEM = "Σάββατο";
const char sunf[] PROGMEM = "Κυριακή";

const char jan[] PROGMEM = "Ιανουάριος";
const char feb[] PROGMEM = "Φεβρουάριος";
const char mar[] PROGMEM = "Μάρτιος";
const char apr[] PROGMEM = "Απρίλιος";
const char may[] PROGMEM = "Μάιος";
const char jun[] PROGMEM = "Ιούνιος";
const char jul[] PROGMEM = "Ιούλιος";
const char aug[] PROGMEM = "Αύγουστος";
const char sep[] PROGMEM = "Σεπτέμβριος";
const char octt[] PROGMEM = "Οκτώβριος";
const char nov[] PROGMEM = "Νοέμβριος";
const char decc[] PROGMEM = "Δεκέμβριος";

const char wn_N[]      PROGMEM = "ΒΟΡΡΑΣ";
const char wn_NNE[]    PROGMEM = "NNE";
const char wn_NE[]     PROGMEM = "NE";
const char wn_ENE[]    PROGMEM = "ENE";
const char wn_E[]      PROGMEM = "ΑΝΑΤΟΛΗ";
const char wn_ESE[]    PROGMEM = "ESE";
const char wn_SE[]     PROGMEM = "SE";
const char wn_SSE[]    PROGMEM = "SSE";
const char wn_S[]      PROGMEM = "ΝΟΤΟΣ";
const char wn_SSW[]    PROGMEM = "SSW";
const char wn_SW[]     PROGMEM = "SW";
const char wn_WSW[]    PROGMEM = "WSW";
const char wn_W[]      PROGMEM = "ΔΥΣΗ";
const char wn_WNW[]    PROGMEM = "WNW";
const char wn_NW[]     PROGMEM = "NW";
const char wn_NNW[]    PROGMEM = "NNW";

const char* const dow[]     PROGMEM = { sun, mon, tue, wed, thu, fri, sat };
const char* const dowf[]    PROGMEM = { sunf, monf, tuef, wedf, thuf, frif, satf };
const char* const mnths[]   PROGMEM = { jan, feb, mar, apr, may, jun, jul, aug, sep, octt, nov, decc };
const char* const wind[]    PROGMEM = { wn_N, wn_NNE, wn_NE, wn_ENE, wn_E, wn_ESE, wn_SE, wn_SSE, wn_S, wn_SSW, wn_SW, wn_WSW, wn_W, wn_WNW, wn_NW, wn_NNW, wn_N };

const char    const_PlReady[]    PROGMEM = "[έτοιμο]";
const char  const_PlStopped[]    PROGMEM = "[σταματημένο]";
const char  const_PlConnect[]    PROGMEM = "[σύνδεση]";
const char  const_DlgVolume[]    PROGMEM = "ΕΝΤΑΣΗ";
const char    const_DlgLost[]    PROGMEM = "* ΧΩΡΙΣ ΣΥΝΔΕΣΗ *";
const char  const_DlgUpdate[]    PROGMEM = "* ΕΝΗΜΈΡΩΣΗ *";
const char const_DlgNextion[]    PROGMEM = "NEXTION";
const char const_getWeather[]    PROGMEM = "";
const char  const_waitForSD[]    PROGMEM = "ΕΥΡΕΤΗΡΙΟ SD";

const char        apNameTxt[]    PROGMEM = "ΟΝΟΜΑ AP";
#ifdef AP_PASSWORD
  const char        apPassTxt[]    PROGMEM = "ΚΩΔΙΚΟΣ";
#else
  const char        apPassTxt[]    PROGMEM = "ΧΩΡΙΣ ΚΩΔΙΚΟ";
#endif

const char       bootstrFmt[]    PROGMEM = "Wi-fi: %s";
const char        apSettFmt[]    PROGMEM = "ΣΥΝΔΕΘΕΙΤΕ & ΑΝΟΙΞΤΕ HTTP://%s/";

#ifdef UPDATEURL
  const char      updFirmware[]    PROGMEM = "Ενημέρωση υλικολογισμικού";
  const char         updFiles[]    PROGMEM = "Ενημέρωση αρχείων";
  const char        updFailed[]    PROGMEM = "Αποτυχία ενημέρωσης";  // translated from "Updating Files"
#endif

#if EXT_WEATHER
const char       weatherFmt[]    PROGMEM = "%s, %.1f\011C \007 αίσθηση: %.1f\011C \007 πίεση: %d hPa \007 υγρασία: %s%% \007 άνεμος: %.1f m/s [%s]";
#else
const char       weatherFmt[]    PROGMEM = "%s, %.1f\011C \007 πίεση: %d hPa \007 υγρασία: %s%%";
#endif
const char     weatherUnits[]    PROGMEM = "metric";   /* standard, metric, imperial */
const char      weatherLang[]    PROGMEM = "el";       /* https://openweathermap.org/current#multi */

#endif

