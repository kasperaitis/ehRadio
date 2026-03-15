#ifndef dsp_full_loc
#define dsp_full_loc
#include <pgmspace.h>
/*************************************************************************************
    HOWTO:
    Copy this file to locale/displayL10n_custom.h
    and modify it
*************************************************************************************/
// Language: Ukrainian
// IETF BCP 47: "uk-UA"
const char mon[] PROGMEM = "пн";
const char tue[] PROGMEM = "вт";
const char wed[] PROGMEM = "ср";
const char thu[] PROGMEM = "чт";
const char fri[] PROGMEM = "пт";
const char sat[] PROGMEM = "сб";
const char sun[] PROGMEM = "нд";

const char monf[] PROGMEM = "Понеділок";
const char tuef[] PROGMEM = "Вівторок";
const char wedf[] PROGMEM = "Середа";
const char thuf[] PROGMEM = "Четвер";
const char frif[] PROGMEM = "П'ятниця";
const char satf[] PROGMEM = "Субота";
const char sunf[] PROGMEM = "Неділя";

const char jan[] PROGMEM = "січня";
const char feb[] PROGMEM = "лютого";
const char mar[] PROGMEM = "березня";
const char apr[] PROGMEM = "квітня";
const char may[] PROGMEM = "травня";
const char jun[] PROGMEM = "червня";
const char jul[] PROGMEM = "липня";
const char aug[] PROGMEM = "серпня";
const char sep[] PROGMEM = "вересня";
const char oct[] PROGMEM = "жовтня";
const char nov[] PROGMEM = "листопада";
const char dec[] PROGMEM = "грудня";

const char wn_N[]      PROGMEM = "Північ";
const char wn_NNE[]    PROGMEM = "ППС";
const char wn_NE[]     PROGMEM = "ПС";
const char wn_ENE[]    PROGMEM = "СПС";
const char wn_E[]      PROGMEM = "Схід";
const char wn_ESE[]    PROGMEM = "СЮС";
const char wn_SE[]     PROGMEM = "ЮС";
const char wn_SSE[]    PROGMEM = "ЮЮС";
const char wn_S[]      PROGMEM = "Південь";
const char wn_SSW[]    PROGMEM = "ЮЮЗ";
const char wn_SW[]     PROGMEM = "ЮЗ";
const char wn_WSW[]    PROGMEM = "ЗЮЗ";
const char wn_W[]      PROGMEM = "Захід";
const char wn_WNW[]    PROGMEM = "ЗПН";
const char wn_NW[]     PROGMEM = "ЗП";
const char wn_NNW[]    PROGMEM = "ППН";

const char* const dow[]     PROGMEM = { sun, mon, tue, wed, thu, fri, sat };
const char* const dowf[]    PROGMEM = { sunf, monf, tuef, wedf, thuf, frif, satf };
const char* const mnths[]   PROGMEM = { jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };
const char* const wind[]    PROGMEM = { wn_N, wn_NNE, wn_NE, wn_ENE, wn_E, wn_ESE, wn_SE, wn_SSE, wn_S, wn_SSW, wn_SW, wn_WSW, wn_W, wn_WNW, wn_NW, wn_NNW, wn_N };

const char    const_PlReady[]    PROGMEM = "[готово]";
const char  const_PlStopped[]    PROGMEM = "[зупинено]";
const char  const_PlConnect[]    PROGMEM = "[підключення]";
const char  const_DlgVolume[]    PROGMEM = "ГОЛОСНІСТЬ";
const char    const_DlgLost[]    PROGMEM = "* ВТРАТА З'ЄДНАННЯ *";
const char  const_DlgUpdate[]    PROGMEM = "* ОНОВЛЕННЯ *";
const char const_DlgNextion[]    PROGMEM = "NEXTION";
const char  const_waitForSD[]    PROGMEM = "ІНДЕКСУВАННЯ SD";

const char        apNameTxt[]    PROGMEM = "ІМ'Я AP";
#ifdef AP_PASSWORD
  const char        apPassTxt[]    PROGMEM = "ПАРОЛЬ";
#else
  const char        apPassTxt[]    PROGMEM = "БЕЗ ПАРОЛЯ";
#endif

const char       bootstrFmt[]    PROGMEM = "Wi-fi: %s";
const char        apSettFmt[]    PROGMEM = "ПІДКЛЮЧІТЬСЯ ТА ВІДКРИЙТЕ HTTP://%s/";

#ifdef UPDATEURL
  const char      updFirmware[]    PROGMEM = "Оновлення прошивки";
  const char         updFiles[]    PROGMEM = "Оновлення файлів";
  const char        updFailed[]    PROGMEM = "Оновлення не вдалося";
#endif

const char weather_feelslike[]  PROGMEM = "відчувається:";
const char weather_pressure[]   PROGMEM = "тиск:";
const char weather_humidity[]   PROGMEM = "вологість:";
const char weather_wind[]       PROGMEM = "вітер:";

#endif

