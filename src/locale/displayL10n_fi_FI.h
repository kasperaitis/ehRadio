#ifndef dsp_full_loc
#define dsp_full_loc
#include <pgmspace.h>
/*************************************************************************************
    HOWTO:
    Copy this file to locale/displayL10n_custom.h
    and modify it
*************************************************************************************/
// Language: Finnish
// IETF BCP 47: "fi-FI"
const char mon[] PROGMEM = "ma";
const char tue[] PROGMEM = "ti";
const char wed[] PROGMEM = "ke";
const char thu[] PROGMEM = "to";
const char fri[] PROGMEM = "pe";
const char sat[] PROGMEM = "la";
const char sun[] PROGMEM = "su";

const char monf[] PROGMEM = "Maanantai";
const char tuef[] PROGMEM = "Tiistai";
const char wedf[] PROGMEM = "Keskiviikko";
const char thuf[] PROGMEM = "Torstai";
const char frif[] PROGMEM = "Perjantai";
const char satf[] PROGMEM = "Lauantai";
const char sunf[] PROGMEM = "Sunnuntai";

const char jan[] PROGMEM = "Tammikuu";
const char feb[] PROGMEM = "Helmikuu";
const char mar[] PROGMEM = "Maaliskuu";
const char apr[] PROGMEM = "Huhtikuu";
const char may[] PROGMEM = "Toukokuu";
const char jun[] PROGMEM = "Kesäkuu";
const char jul[] PROGMEM = "Heinäkuu";
const char aug[] PROGMEM = "Elokuu";
const char sep[] PROGMEM = "Syyskuu";
const char oct[] PROGMEM = "Lokakuu";
const char nov[] PROGMEM = "Marraskuu";
const char dec[] PROGMEM = "Joulukuu";

const char wn_N[]      PROGMEM = "POHJOINEN";
const char wn_NNE[]    PROGMEM = "NNE";
const char wn_NE[]     PROGMEM = "NE";
const char wn_ENE[]    PROGMEM = "ENE";
const char wn_E[]      PROGMEM = "ITÄ";
const char wn_ESE[]    PROGMEM = "ESE";
const char wn_SE[]     PROGMEM = "SE";
const char wn_SSE[]    PROGMEM = "SSE";
const char wn_S[]      PROGMEM = "ETELÄ";
const char wn_SSW[]    PROGMEM = "SSW";
const char wn_SW[]     PROGMEM = "SW";
const char wn_WSW[]    PROGMEM = "WSW";
const char wn_W[]      PROGMEM = "LÄNSI";
const char wn_WNW[]    PROGMEM = "WNW";
const char wn_NW[]     PROGMEM = "NW";
const char wn_NNW[]    PROGMEM = "NNW";

const char* const dow[]     PROGMEM = { sun, mon, tue, wed, thu, fri, sat };
const char* const dowf[]    PROGMEM = { sunf, monf, tuef, wedf, thuf, frif, satf };
const char* const mnths[]   PROGMEM = { jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };
const char* const wind[]    PROGMEM = { wn_N, wn_NNE, wn_NE, wn_ENE, wn_E, wn_ESE, wn_SE, wn_SSE, wn_S, wn_SSW, wn_SW, wn_WSW, wn_W, wn_WNW, wn_NW, wn_NNW, wn_N };

const char    const_PlReady[]    PROGMEM = "[valmis]";
const char  const_PlStopped[]    PROGMEM = "[pysäytetty]";
const char  const_PlConnect[]    PROGMEM = "[yhdistetään]";
const char  const_DlgVolume[]    PROGMEM = "ÄÄNENVOIMUUS";
const char    const_DlgLost[]    PROGMEM = "* YHTEYS KATKENNUT *";
const char  const_DlgUpdate[]    PROGMEM = "* PÄIVITETÄÄN *";
const char const_DlgNextion[]    PROGMEM = "NEXTION";
const char  const_waitForSD[]    PROGMEM = "INDEKSI SD";

const char        apNameTxt[]    PROGMEM = "AP NIMI";
#ifdef AP_PASSWORD
  const char        apPassTxt[]    PROGMEM = "SALASANA";
#else
  const char        apPassTxt[]    PROGMEM = "EI SALASANAA";
#endif

const char       bootstrFmt[]    PROGMEM = "Wi-fi: %s";
const char        apSettFmt[]    PROGMEM = "YHDISTÄ JA Avaa HTTP://%s/";

#ifdef UPDATEURL
  const char      updFirmware[]    PROGMEM = "Päivitetään laiteohjelmistoa";
  const char         updFiles[]    PROGMEM = "Päivitetään tiedostot";
  const char        updFailed[]    PROGMEM = "Päivitys epäonnistui";
#endif

const char weather_feelslike[]  PROGMEM = "tuntuu kuin:";
const char weather_pressure[]   PROGMEM = "paine:";
const char weather_humidity[]   PROGMEM = "kosteus:";
const char weather_wind[]       PROGMEM = "tuuli:";

#endif

