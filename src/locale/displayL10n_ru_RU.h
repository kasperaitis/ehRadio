#ifndef dsp_full_loc
#define dsp_full_loc
#include <pgmspace.h>
/*************************************************************************************
    HOWTO:
    Copy this file to locale/displayL10n_custom.h
    and modify it
*************************************************************************************/
// Language: Russian
// IETF BCP 47: "ru-RU"
const char mon[] PROGMEM = "пн";
const char tue[] PROGMEM = "вт";
const char wed[] PROGMEM = "ср";
const char thu[] PROGMEM = "чт";
const char fri[] PROGMEM = "пт";
const char sat[] PROGMEM = "сб";
const char sun[] PROGMEM = "вс";

const char monf[] PROGMEM = "понедельник";
const char tuef[] PROGMEM = "вторник";
const char wedf[] PROGMEM = "среда";
const char thuf[] PROGMEM = "четверг";
const char frif[] PROGMEM = "пятница";
const char satf[] PROGMEM = "суббота";
const char sunf[] PROGMEM = "воскресенье";

const char jan[] PROGMEM = "января";
const char feb[] PROGMEM = "февраля";
const char mar[] PROGMEM = "марта";
const char apr[] PROGMEM = "апреля";
const char may[] PROGMEM = "мая";
const char jun[] PROGMEM = "июня";
const char jul[] PROGMEM = "июля";
const char aug[] PROGMEM = "августа";
const char sep[] PROGMEM = "сентября";
const char oct[] PROGMEM = "октября";
const char nov[] PROGMEM = "ноября";
const char dec[] PROGMEM = "декабря";

const char wn_N[]      PROGMEM = "СЕВЕР";
const char wn_NNE[]    PROGMEM = "ССВ";
const char wn_NE[]     PROGMEM = "СВ";
const char wn_ENE[]    PROGMEM = "ВСВ";
const char wn_E[]      PROGMEM = "ВОСТОК";
const char wn_ESE[]    PROGMEM = "ВЮВ";
const char wn_SE[]     PROGMEM = "ЮВ";
const char wn_SSE[]    PROGMEM = "ЮЮВ";
const char wn_S[]      PROGMEM = "ЮГ";
const char wn_SSW[]    PROGMEM = "ЮЮЗ";
const char wn_SW[]     PROGMEM = "ЮЗ";
const char wn_WSW[]    PROGMEM = "ЗЮЗ";
const char wn_W[]      PROGMEM = "ЗАПАД";
const char wn_WNW[]    PROGMEM = "ЗСЗ";
const char wn_NW[]     PROGMEM = "СЗ";
const char wn_NNW[]    PROGMEM = "ССЗ";

const char* const dow[]     PROGMEM = { sun, mon, tue, wed, thu, fri, sat };
const char* const dowf[]    PROGMEM = { sunf, monf, tuef, wedf, thuf, frif, satf };
const char* const mnths[]   PROGMEM = { jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };
const char* const wind[]    PROGMEM = { wn_N, wn_NNE, wn_NE, wn_ENE, wn_E, wn_ESE, wn_SE, wn_SSE, wn_S, wn_SSW, wn_SW, wn_WSW, wn_W, wn_WNW, wn_NW, wn_NNW, wn_N };

const char    const_PlReady[]    PROGMEM = "[готов]";
const char  const_PlStopped[]    PROGMEM = "[остановлено]";
const char  const_PlConnect[]    PROGMEM = "[соединение]";
const char  const_DlgVolume[]    PROGMEM = "ГРОМКОСТЬ";
const char    const_DlgLost[]    PROGMEM = "ОТКЛЮЧЕНО";
const char  const_DlgUpdate[]    PROGMEM = "ОБНОВЛЕНИЕ";
const char const_DlgNextion[]    PROGMEM = "NEXTION";
const char  const_waitForSD[]    PROGMEM = "ИНДЕКС SD";

const char        apNameTxt[]    PROGMEM = "ТОЧКА ДОСТУПА";
#ifdef AP_PASSWORD
  const char        apPassTxt[]    PROGMEM = "ПАРОЛЬ";
#else
  const char        apPassTxt[]    PROGMEM = "НЕТ ПАРОЛЯ";
#endif
const char       bootstrFmt[]    PROGMEM = "Соединяюсь с %s";
const char        apSettFmt[]    PROGMEM = "ПОДКЛЮЧИТЕСЬ И ОТКРОЙТЕ HTTP://%s/";

#ifdef UPDATEURL
  const char      updFirmware[]    PROGMEM = "Обновление прошивки";
  const char         updFiles[]    PROGMEM = "Обновление файлов";
  const char        updFailed[]    PROGMEM = "Обновление не удалось";
#endif

const char weather_feelslike[]  PROGMEM = "ощущается:";
const char weather_pressure[]   PROGMEM = "давление:";
const char weather_humidity[]   PROGMEM = "влажность:";
const char weather_wind[]       PROGMEM = "ветер:";

#endif

