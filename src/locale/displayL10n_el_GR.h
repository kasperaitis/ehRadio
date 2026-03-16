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
const char oct[] PROGMEM = "Οκτώβριος";
const char nov[] PROGMEM = "Νοέμβριος";
const char dec[] PROGMEM = "Δεκέμβριος";

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
const char* const mnths[]   PROGMEM = { jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };
const char* const wind[]    PROGMEM = { wn_N, wn_NNE, wn_NE, wn_ENE, wn_E, wn_ESE, wn_SE, wn_SSE, wn_S, wn_SSW, wn_SW, wn_WSW, wn_W, wn_WNW, wn_NW, wn_NNW, wn_N };

const char    const_PlReady[]    PROGMEM = "[έτοιμο]";
const char  const_PlStopped[]    PROGMEM = "[σταματημένο]";
const char  const_PlConnect[]    PROGMEM = "[σύνδεση]";
const char  const_DlgVolume[]    PROGMEM = "ΕΝΤΑΣΗ";
const char    const_DlgLost[]    PROGMEM = "* ΧΩΡΙΣ ΣΥΝΔΕΣΗ *";
const char  const_DlgUpdate[]    PROGMEM = "* ΕΝΗΜΈΡΩΣΗ *";
const char const_DlgNextion[]    PROGMEM = "NEXTION";
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

const char weather_feelslike[]  PROGMEM = "αίσθηση:";
const char weather_pressure[]   PROGMEM = "πίεση:";
const char weather_humidity[]   PROGMEM = "υγρασία:";
const char weather_wind[]       PROGMEM = "άνεμος:";
const char weather_loading[]    PROGMEM = "Λήψη μετεωρολογικών δεδομένων...";

// WMO Weather Code Translations (for Open-Meteo)
const char w_clear_sky[]         PROGMEM = "Αίθριος ουρανός";
const char w_overcast[]          PROGMEM = "Συννεφιά";
const char w_foggy[]             PROGMEM = "Ομίχλη";
const char w_drizzle[]           PROGMEM = "Ψιλόβροχο";
const char w_freezing_drizzle[]  PROGMEM = "Ψυχρή ψιλή βροχή";
const char w_rain[]              PROGMEM = "Βροχή";
const char w_freezing_rain[]     PROGMEM = "Ψυχρή βροχή";
const char w_snow[]              PROGMEM = "Χιόνι";
const char w_snow_grains[]       PROGMEM = "Κόκκοι χιονιού";
const char w_rain_showers[]      PROGMEM = "Πρόσκαιρες βροχές";
const char w_snow_showers[]      PROGMEM = "Χιονόπτωση";
const char w_thunderstorm[]      PROGMEM = "Καταιγίδα";
const char w_thunderstorm_hail[] PROGMEM = "Καταιγίδα με χαλάζι";

#endif

