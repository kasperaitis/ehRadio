#ifndef dsp_full_loc
#define dsp_full_loc
#include <pgmspace.h>
/*************************************************************************************
    HOWTO:
    Copy this file to locale/displayL10n_custom.h
    and modify it
*************************************************************************************/
// Language: Tajik
// IETF BCP 47: "tg-TJ"
const char mon[] PROGMEM = "дш";
const char tue[] PROGMEM = "сш";
const char wed[] PROGMEM = "чш";
const char thu[] PROGMEM = "пш";
const char fri[] PROGMEM = "ҷм";
const char sat[] PROGMEM = "шб";
const char sun[] PROGMEM = "як";

const char monf[] PROGMEM = "душанбе";
const char tuef[] PROGMEM = "сешанбе";
const char wedf[] PROGMEM = "чоршанбе";
const char thuf[] PROGMEM = "панҷшанбе";
const char frif[] PROGMEM = "ҷумъа";
const char satf[] PROGMEM = "шанбе";
const char sunf[] PROGMEM = "якшанбе";

const char jan[] PROGMEM = "январ";
const char feb[] PROGMEM = "феврал";
const char mar[] PROGMEM = "март";
const char apr[] PROGMEM = "апрел";
const char may[] PROGMEM = "май";
const char jun[] PROGMEM = "июн";
const char jul[] PROGMEM = "июл";
const char aug[] PROGMEM = "август";
const char sep[] PROGMEM = "сентябр";
const char octt[] PROGMEM = "октябр";
const char nov[] PROGMEM = "ноябр";
const char decc[] PROGMEM = "декабр";

const char wn_N[]      PROGMEM = "Шимол";
const char wn_NNE[]    PROGMEM = "ШШШ";
const char wn_NE[]     PROGMEM = "ШШ";
const char wn_ENE[]    PROGMEM = "ВШШ";
const char wn_E[]      PROGMEM = "Шарқ";
const char wn_ESE[]    PROGMEM = "ВЖШ";
const char wn_SE[]     PROGMEM = "ЖШ";
const char wn_SSE[]    PROGMEM = "ЖЖШ";
const char wn_S[]      PROGMEM = "Жануб";
const char wn_SSW[]    PROGMEM = "ЖЖВ";
const char wn_SW[]     PROGMEM = "ЖВ";
const char wn_WSW[]    PROGMEM = "ЗЖВ";
const char wn_W[]      PROGMEM = "Ғарб";
const char wn_WNW[]    PROGMEM = "ББЖ";
const char wn_NW[]     PROGMEM = "БС";
const char wn_NNW[]    PROGMEM = "СБС";

const char* const dow[]     PROGMEM = { sun, mon, tue, wed, thu, fri, sat };
const char* const dowf[]    PROGMEM = { sunf, monf, tuef, wedf, thuf, frif, satf };
const char* const mnths[]   PROGMEM = { jan, feb, mar, apr, may, jun, jul, aug, sep, octt, nov, decc };
const char* const wind[]    PROGMEM = { wn_N, wn_NNE, wn_NE, wn_ENE, wn_E, wn_ESE, wn_SE, wn_SSE, wn_S, wn_SSW, wn_SW, wn_WSW, wn_W, wn_WNW, wn_NW, wn_NNW, wn_N };

const char    const_PlReady[]    PROGMEM = "[омодаги]";
const char  const_PlStopped[]    PROGMEM = "[хомӯш]";
const char  const_PlConnect[]    PROGMEM = "[пайвастшавӣ]";
const char  const_DlgVolume[]    PROGMEM = "ҲАЖМ";
const char    const_DlgLost[]    PROGMEM = "* АЛОҚА НЕСТ *";
const char  const_DlgUpdate[]    PROGMEM = "* НАВ КУНАНД *";
const char const_DlgNextion[]    PROGMEM = "NEXTION";
const char const_getWeather[]    PROGMEM = "";
const char  const_waitForSD[]    PROGMEM = "ИНДЕКС SD";

const char        apNameTxt[]    PROGMEM = "НОМИ AP";
#ifdef AP_PASSWORD
  const char        apPassTxt[]    PROGMEM = "РАҲЗАНД";
#else
  const char        apPassTxt[]    PROGMEM = "БЕ РАҲЗАНД";
#endif

const char       bootstrFmt[]    PROGMEM = "Wi-fi: %s";
const char        apSettFmt[]    PROGMEM = "ПАЙВАСТ ШАВД ВА HTTP://%s/-ро БИВОЗЕД";

#ifdef UPDATEURL
  const char      updFirmware[]    PROGMEM = "Навсозии фирмвар";
  const char         updFiles[]    PROGMEM = "Навсозии файлҳо";
  const char        updFailed[]    PROGMEM = "Навсозӣ ноком шуд";
#endif

#if EXT_WEATHER
const char       weatherFmt[]    PROGMEM = "%s, %.1f\011C \007 ҳиссияти: %.1f\011C \007 фишор: %d гПа \007 намӣ: %s%% \007 бод: %.1f m/s [%s]";
#else
const char       weatherFmt[]    PROGMEM = "%s, %.1f\011C \007 фишор: %d гПа \007 намӣ: %s%%";
#endif
const char     weatherUnits[]    PROGMEM = "metric";   /* standard, metric, imperial */
const char      weatherLang[]    PROGMEM = "en";       /* https://openweathermap.org/current#multi */

#endif

