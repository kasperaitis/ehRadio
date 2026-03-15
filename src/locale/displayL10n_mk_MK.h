#ifndef dsp_full_loc
#define dsp_full_loc
#include <pgmspace.h>
/*************************************************************************************
    HOWTO:
    Copy this file to locale/displayL10n_custom.h
    and modify it
*************************************************************************************/
// Language: Macedonian
// IETF BCP 47: "mk-MK"
const char mon[] PROGMEM = "по";
const char tue[] PROGMEM = "вт";
const char wed[] PROGMEM = "ср";
const char thu[] PROGMEM = "че";
const char fri[] PROGMEM = "пе";
const char sat[] PROGMEM = "са";
const char sun[] PROGMEM = "не";

const char monf[] PROGMEM = "понеделник";
const char tuef[] PROGMEM = "вторник";
const char wedf[] PROGMEM = "среда";
const char thuf[] PROGMEM = "четврток";
const char frif[] PROGMEM = "петок";
const char satf[] PROGMEM = "сабота";
const char sunf[] PROGMEM = "недела";

const char jan[] PROGMEM = "јануари";
const char feb[] PROGMEM = "февруари";
const char mar[] PROGMEM = "март";
const char apr[] PROGMEM = "април";
const char may[] PROGMEM = "мај";
const char jun[] PROGMEM = "јуни";
const char jul[] PROGMEM = "јули";
const char aug[] PROGMEM = "август";
const char sep[] PROGMEM = "септември";
const char oct[] PROGMEM = "октомври";
const char nov[] PROGMEM = "ноември";
const char dec[] PROGMEM = "декември";

const char wn_N[]      PROGMEM = "СЕВ";
const char wn_NNE[]    PROGMEM = "ССВ";
const char wn_NE[]     PROGMEM = "СВ";
const char wn_ENE[]    PROGMEM = "ВСВ";
const char wn_E[]      PROGMEM = "ИСТ";
const char wn_ESE[]    PROGMEM = "ИЈВ";
const char wn_SE[]     PROGMEM = "ЈИ";
const char wn_SSE[]    PROGMEM = "ЈЈИ";
const char wn_S[]      PROGMEM = "ЈУГ";
const char wn_SSW[]    PROGMEM = "ЈЈЗ";
const char wn_SW[]     PROGMEM = "ЈЗ";
const char wn_WSW[]    PROGMEM = "ЗЈЗ";
const char wn_W[]      PROGMEM = "ЗАП";
const char wn_WNW[]    PROGMEM = "ЗСЗ";
const char wn_NW[]     PROGMEM = "СЗ";
const char wn_NNW[]    PROGMEM = "ССЗ";

const char* const dow[]     PROGMEM = { sun, mon, tue, wed, thu, fri, sat };
const char* const dowf[]    PROGMEM = { sunf, monf, tuef, wedf, thuf, frif, satf };
const char* const mnths[]   PROGMEM = { jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };
const char* const wind[]    PROGMEM = { wn_N, wn_NNE, wn_NE, wn_ENE, wn_E, wn_ESE, wn_SE, wn_SSE, wn_S, wn_SSW, wn_SW, wn_WSW, wn_W, wn_WNW, wn_NW, wn_NNW, wn_N };

const char    const_PlReady[]    PROGMEM = "[спремно]";
const char  const_PlStopped[]    PROGMEM = "[запрено]";
const char  const_PlConnect[]    PROGMEM = "[се поврзува]";
const char  const_DlgVolume[]    PROGMEM = "ЈАЧИНА";
const char    const_DlgLost[]    PROGMEM = "* ПРЕКИНАТО *";
const char  const_DlgUpdate[]    PROGMEM = "* АЖУРИРАЊЕ *";
const char const_DlgNextion[]    PROGMEM = "NEXTION";
const char  const_waitForSD[]    PROGMEM = "ИНДЕКС SD";

const char        apNameTxt[]    PROGMEM = "ИМЕ AP";
#ifdef AP_PASSWORD
  const char        apPassTxt[]    PROGMEM = "ЛОЗИНКА";
#else
  const char        apPassTxt[]    PROGMEM = "БЕЗ ЛОЗИНКA";
#endif

const char       bootstrFmt[]    PROGMEM = "Wi-fi: %s";
const char        apSettFmt[]    PROGMEM = "ПОВРЗЕТЕ СЕ И ОТВОРЕТЕ HTTP://%s/";

#ifdef UPDATEURL
  const char      updFirmware[]    PROGMEM = "Ажурирање на фирмвер";
  const char         updFiles[]    PROGMEM = "Ажурирање на датотеки";
  const char        updFailed[]    PROGMEM = "Ажурирање не успеа";
#endif

const char weather_feelslike[]  PROGMEM = "чувствува:";
const char weather_pressure[]   PROGMEM = "притисок:";
const char weather_humidity[]   PROGMEM = "влажност:";
const char weather_wind[]       PROGMEM = "ветер:";

#endif

