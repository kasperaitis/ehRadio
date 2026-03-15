#ifndef dsp_full_loc
#define dsp_full_loc
#include <pgmspace.h>
/*************************************************************************************
    HOWTO:
    Copy this file to locale/displayL10n_custom.h
    and modify it
*************************************************************************************/
// Language: Bulgarian
// IETF BCP 47: "bg-BG"
const char mon[] PROGMEM = "пн";
const char tue[] PROGMEM = "вт";
const char wed[] PROGMEM = "ср";
const char thu[] PROGMEM = "чт";
const char fri[] PROGMEM = "пт";
const char sat[] PROGMEM = "сб";
const char sun[] PROGMEM = "нд";

const char monf[] PROGMEM = "Понеделник";
const char tuef[] PROGMEM = "Вторник";
const char wedf[] PROGMEM = "Сряда";
const char thuf[] PROGMEM = "Четвъртък";
const char frif[] PROGMEM = "Петък";
const char satf[] PROGMEM = "Събота";
const char sunf[] PROGMEM = "Неделя";

const char jan[] PROGMEM = "Януари";
const char feb[] PROGMEM = "Февруари";
const char mar[] PROGMEM = "Март";
const char apr[] PROGMEM = "Април";
const char may[] PROGMEM = "Май";
const char jun[] PROGMEM = "Юни";
const char jul[] PROGMEM = "Юли";
const char aug[] PROGMEM = "Август";
const char sep[] PROGMEM = "Септември";
const char oct[] PROGMEM = "Октомври";
const char nov[] PROGMEM = "Ноември";
const char dec[] PROGMEM = "Декември";

const char wn_N[]      PROGMEM = "СЕВЕР";
const char wn_NNE[]    PROGMEM = "NNE";
const char wn_NE[]     PROGMEM = "NE";
const char wn_ENE[]    PROGMEM = "ENE";
const char wn_E[]      PROGMEM = "ИЗТОК";
const char wn_ESE[]    PROGMEM = "ESE";
const char wn_SE[]     PROGMEM = "SE";
const char wn_SSE[]    PROGMEM = "SSE";
const char wn_S[]      PROGMEM = "ЮГ";
const char wn_SSW[]    PROGMEM = "SSW";
const char wn_SW[]     PROGMEM = "SW";
const char wn_WSW[]    PROGMEM = "WSW";
const char wn_W[]      PROGMEM = "ЗАПАД";
const char wn_WNW[]    PROGMEM = "WNW";
const char wn_NW[]     PROGMEM = "NW";
const char wn_NNW[]    PROGMEM = "NNW";

const char* const dow[]     PROGMEM = { sun, mon, tue, wed, thu, fri, sat };
const char* const dowf[]    PROGMEM = { sunf, monf, tuef, wedf, thuf, frif, satf };
const char* const mnths[]   PROGMEM = { jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };
const char* const wind[]    PROGMEM = { wn_N, wn_NNE, wn_NE, wn_ENE, wn_E, wn_ESE, wn_SE, wn_SSE, wn_S, wn_SSW, wn_SW, wn_WSW, wn_W, wn_WNW, wn_NW, wn_NNW, wn_N };

const char    const_PlReady[]    PROGMEM = "[готово]";
const char  const_PlStopped[]    PROGMEM = "[спряно]";
const char  const_PlConnect[]    PROGMEM = "[свързване]";
const char  const_DlgVolume[]    PROGMEM = "ГЛАСНОСТ";
const char    const_DlgLost[]    PROGMEM = "* НЯМА ВРЪЗКА *";
const char  const_DlgUpdate[]    PROGMEM = "* АКТУАЛИЗАЦИЯ *";
const char const_DlgNextion[]    PROGMEM = "NEXTION";
const char  const_waitForSD[]    PROGMEM = "ИНДЕКС SD";

const char        apNameTxt[]    PROGMEM = "ИМЕ AP";
#ifdef AP_PASSWORD
  const char        apPassTxt[]    PROGMEM = "ПАРОЛА";
#else
  const char        apPassTxt[]    PROGMEM = "БЕЗ ПАРОЛА";
#endif

const char       bootstrFmt[]    PROGMEM = "Wi-fi: %s";
const char        apSettFmt[]    PROGMEM = "СВЪРЖЕТЕ СЕ & ОТВОРЕТЕ HTTP://%s/";

#ifdef UPDATEURL
  const char      updFirmware[]    PROGMEM = "Актуализиране на фърмуера";
  const char         updFiles[]    PROGMEM = "Актуализиране на файлове";
  const char        updFailed[]    PROGMEM = "Актуализиране неуспешно";
#endif

const char weather_feelslike[]  PROGMEM = "усеща се:";
const char weather_pressure[]   PROGMEM = "налягане:";
const char weather_humidity[]   PROGMEM = "влажност:";
const char weather_wind[]       PROGMEM = "вятър:";


#endif

