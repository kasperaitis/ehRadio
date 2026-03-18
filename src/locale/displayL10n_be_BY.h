#ifndef dsp_full_loc
#define dsp_full_loc
#include <pgmspace.h>
/*************************************************************************************
    HOWTO:
    Copy this file to locale/displayL10n_custom.h
    and modify it
*************************************************************************************/
// Language: Belarusian
// IETF BCP 47: "be-BY"
const char mon[] PROGMEM = "пн";
const char tue[] PROGMEM = "ат";
const char wed[] PROGMEM = "ср";
const char thu[] PROGMEM = "чц";
const char fri[] PROGMEM = "пт";
const char sat[] PROGMEM = "сб";
const char sun[] PROGMEM = "нд";

const char monf[] PROGMEM = "панядзелак";
const char tuef[] PROGMEM = "аўторак";
const char wedf[] PROGMEM = "серада";
const char thuf[] PROGMEM = "чацвер";
const char frif[] PROGMEM = "пятніца";
const char satf[] PROGMEM = "субота";
const char sunf[] PROGMEM = "нядзеля";

const char jan[] PROGMEM = "студзеня";
const char feb[] PROGMEM = "лютага";
const char mar[] PROGMEM = "сакавіка";
const char apr[] PROGMEM = "красавіка";
const char may[] PROGMEM = "мая";
const char jun[] PROGMEM = "чэрвеня";
const char jul[] PROGMEM = "ліпеня";
const char aug[] PROGMEM = "жніўня";
const char sep[] PROGMEM = "верасня";
const char oct[] PROGMEM = "кастрычніка";
const char nov[] PROGMEM = "лістапада";
const char dec[] PROGMEM = "снежня";

const char wn_N[]      PROGMEM = "Поўнач";
const char wn_NNE[]    PROGMEM = "ППН";
const char wn_NE[]     PROGMEM = "ПВ";
const char wn_ENE[]    PROGMEM = "ВПВ";
const char wn_E[]      PROGMEM = "Усход";
const char wn_ESE[]    PROGMEM = "ВЮВ";
const char wn_SE[]     PROGMEM = "ЮВ";
const char wn_SSE[]    PROGMEM = "ЮПЮ";
const char wn_S[]      PROGMEM = "Поўдзень";
const char wn_SSW[]    PROGMEM = "ЮПЗ";
const char wn_SW[]     PROGMEM = "ЮЗ";
const char wn_WSW[]    PROGMEM = "ЗПЗ";
const char wn_W[]      PROGMEM = "Захад";
const char wn_WNW[]    PROGMEM = "ЗПС";
const char wn_NW[]     PROGMEM = "ПЗ";
const char wn_NNW[]    PROGMEM = "ППЗ";

const char* const dow[]     PROGMEM = { sun, mon, tue, wed, thu, fri, sat };
const char* const dowf[]    PROGMEM = { sunf, monf, tuef, wedf, thuf, frif, satf };
const char* const mnths[]   PROGMEM = { jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };
const char* const wind[]    PROGMEM = { wn_N, wn_NNE, wn_NE, wn_ENE, wn_E, wn_ESE, wn_SE, wn_SSE, wn_S, wn_SSW, wn_SW, wn_WSW, wn_W, wn_WNW, wn_NW, wn_NNW, wn_N };

const char    const_PlReady[]    PROGMEM = "[гатова]";
const char  const_PlStopped[]    PROGMEM = "[прыпынена]";
const char  const_PlConnect[]    PROGMEM = "[злучэнне]";
const char  const_DlgVolume[]    PROGMEM = "ГУЧНАСЦЬ";
const char    const_DlgLost[]    PROGMEM = "АДКЛЮЧАНА";
const char  const_DlgUpdate[]    PROGMEM = "АБНАЎЛЕННЕ";
const char const_DlgNextion[]    PROGMEM = "NEXTION";
const char  const_waitForSD[]    PROGMEM = "ЧАКАННЕ SD";

const char        apNameTxt[]    PROGMEM = "ТОЧКА ДАСТУПУ";
#ifdef AP_PASSWORD
  const char        apPassTxt[]    PROGMEM = "ПАРОЛЬ";
#else
  const char        apPassTxt[]    PROGMEM = "НЕТ ПАРОЛЯ";
#endif
const char       bootstrFmt[]    PROGMEM = "Злучаюся з %s";
const char        apSettFmt[]    PROGMEM = "ПАДКЛЮЧЫЦЕСЯ І АДКРЫЙЦЕ HTTP://%s/";

#ifdef UPDATEURL
  const char      updFirmware[]    PROGMEM = "Абнаўленне прашыўкі";
  const char         updFiles[]    PROGMEM = "Абнаўленне файлаў";
  const char        updFailed[]    PROGMEM = "Update failed";
#endif

const char weather_feelslike[]  PROGMEM = "адчуваецца:";
const char weather_pressure[]   PROGMEM = "ціск:";
const char weather_humidity[]   PROGMEM = "вільготнасць:";
const char weather_wind[]       PROGMEM = "вецер:";
const char weather_loading[]    PROGMEM = "Загрузка дадзеных пра надвор'е...";

// WMO Weather Code Translations (for Open-Meteo)
const char w_clear_sky[]         PROGMEM = "Яснае неба";
const char w_overcast[]          PROGMEM = "Аблочна";
const char w_foggy[]             PROGMEM = "Туман";
const char w_drizzle[]           PROGMEM = "Імжа";
const char w_freezing_drizzle[]  PROGMEM = "Лядзяная імжа";
const char w_rain[]              PROGMEM = "Дождж";
const char w_freezing_rain[]     PROGMEM = "Лядзяны дождж";
const char w_snow[]              PROGMEM = "Снег";
const char w_snow_grains[]       PROGMEM = "Снежная крупа";
const char w_rain_showers[]      PROGMEM = "Лівень";
const char w_snow_showers[]      PROGMEM = "Снегапад";
const char w_thunderstorm[]      PROGMEM = "Граза";
const char w_thunderstorm_hail[] PROGMEM = "Граза з градом";

#endif

