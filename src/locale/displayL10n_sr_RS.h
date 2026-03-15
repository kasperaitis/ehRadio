#ifndef dsp_full_loc
#define dsp_full_loc
#include <pgmspace.h>
/*************************************************************************************
    HOWTO:
    Copy this file to locale/displayL10n_custom.h
    and modify it
*************************************************************************************/
// Language: Serbian
// IETF BCP 47: "sr-RS"
const char mon[] PROGMEM = "пн";
const char tue[] PROGMEM = "вт";
const char wed[] PROGMEM = "ср";
const char thu[] PROGMEM = "чт";
const char fri[] PROGMEM = "пт";
const char sat[] PROGMEM = "сб";
const char sun[] PROGMEM = "нд";

const char monf[] PROGMEM = "понедељак";
const char tuef[] PROGMEM = "уторак";
const char wedf[] PROGMEM = "среда";
const char thuf[] PROGMEM = "четвртак";
const char frif[] PROGMEM = "петак";
const char satf[] PROGMEM = "субота";
const char sunf[] PROGMEM = "недеља";

const char jan[] PROGMEM = "јануар";
const char feb[] PROGMEM = "фебруар";
const char mar[] PROGMEM = "март";
const char apr[] PROGMEM = "април";
const char may[] PROGMEM = "мај";
const char jun[] PROGMEM = "јун";
const char jul[] PROGMEM = "јул";
const char aug[] PROGMEM = "август";
const char sep[] PROGMEM = "септембар";
const char oct[] PROGMEM = "октобар";
const char nov[] PROGMEM = "новембар";
const char dec[] PROGMEM = "децембар";

const char wn_N[]      PROGMEM = "СЕВ";
const char wn_NNE[]    PROGMEM = "ССВ";
const char wn_NE[]     PROGMEM = "СВ";
const char wn_ENE[]    PROGMEM = "ВСВ";
const char wn_E[]      PROGMEM = "ИСТОК";
const char wn_ESE[]    PROGMEM = "ВИСТ";
const char wn_SE[]     PROGMEM = "ЈУГОИСТОК";
const char wn_SSE[]    PROGMEM = "ЈЈИ";
const char wn_S[]      PROGMEM = "ЈУГ";
const char wn_SSW[]    PROGMEM = "ЈЈЗ";
const char wn_SW[]     PROGMEM = "ЈЗ";
const char wn_WSW[]    PROGMEM = "ЗЈЗ";
const char wn_W[]      PROGMEM = "ЗАПАД";
const char wn_WNW[]    PROGMEM = "ЗСЗ";
const char wn_NW[]     PROGMEM = "СЗ";
const char wn_NNW[]    PROGMEM = "ССЗ";

const char* const dow[]     PROGMEM = { sun, mon, tue, wed, thu, fri, sat };
const char* const dowf[]    PROGMEM = { sunf, monf, tuef, wedf, thuf, frif, satf };
const char* const mnths[]   PROGMEM = { jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };
const char* const wind[]    PROGMEM = { wn_N, wn_NNE, wn_NE, wn_ENE, wn_E, wn_ESE, wn_SE, wn_SSE, wn_S, wn_SSW, wn_SW, wn_WSW, wn_W, wn_WNW, wn_NW, wn_NNW, wn_N };

const char    const_PlReady[]    PROGMEM = "[спремно]";
const char  const_PlStopped[]    PROGMEM = "[заустављено]";
const char  const_PlConnect[]    PROGMEM = "[повезивање]";
const char  const_DlgVolume[]    PROGMEM = "ЈАЧИНА";
const char    const_DlgLost[]    PROGMEM = "* НИМА ВЕЗЕ *";
const char  const_DlgUpdate[]    PROGMEM = "* АЖУРИРАЊЕ *";
const char const_DlgNextion[]    PROGMEM = "NEXTION";
const char  const_waitForSD[]    PROGMEM = "ИНДЕКС SD";

const char        apNameTxt[]    PROGMEM = "ИМЕ AP";
#ifdef AP_PASSWORD
  const char        apPassTxt[]    PROGMEM = "ЛОЗИНКА";
#else
  const char        apPassTxt[]    PROGMEM = "БЕЗ ЛОЗИНКЕ";
#endif

const char       bootstrFmt[]    PROGMEM = "Wi-fi: %s";
const char        apSettFmt[]    PROGMEM = "ПОВЕЖИТЕ СЕ И ОТВОРИТЕ HTTP://%s/";

#ifdef UPDATEURL
  const char      updFirmware[]    PROGMEM = "Ажурирање фирмвера";
  const char         updFiles[]    PROGMEM = "Ажурирање фајлова";
  const char        updFailed[]    PROGMEM = "Ажурирање није успело";
#endif

const char weather_feelslike[]  PROGMEM = "осећај:";
const char weather_pressure[]   PROGMEM = "притисак:";
const char weather_humidity[]   PROGMEM = "влажност:";
const char weather_wind[]       PROGMEM = "ветар:";

#endif

