#ifndef dsp_full_loc
#define dsp_full_loc
#include <pgmspace.h>
/*************************************************************************************
    HOWTO:
    Copy this file to locale/displayL10n_custom.h
    and modify it
*************************************************************************************/
// Language: Mongolian
// IETF BCP 47: "mn-MN"
const char mon[] PROGMEM = "Дш";
const char tue[] PROGMEM = "Мя";
const char wed[] PROGMEM = "Лх";
const char thu[] PROGMEM = "Пү";
const char fri[] PROGMEM = "Ба";
const char sat[] PROGMEM = "Бн";
const char sun[] PROGMEM = "Ня";

const char monf[] PROGMEM = "Даваа";
const char tuef[] PROGMEM = "Мягмар";
const char wedf[] PROGMEM = "Лхагва";
const char thuf[] PROGMEM = "Пүрэв";
const char frif[] PROGMEM = "Баасан";
const char satf[] PROGMEM = "Бямба";
const char sunf[] PROGMEM = "Ням";

const char jan[] PROGMEM = "1-р сар";
const char feb[] PROGMEM = "2-р сар";
const char mar[] PROGMEM = "3-р сар";
const char apr[] PROGMEM = "4-р сар";
const char may[] PROGMEM = "5-р сар";
const char jun[] PROGMEM = "6-р сар";
const char jul[] PROGMEM = "7-р сар";
const char aug[] PROGMEM = "8-р сар";
const char sep[] PROGMEM = "9-р сар";
const char oct[] PROGMEM = "10-р сар";
const char nov[] PROGMEM = "11-р сар";
const char dec[] PROGMEM = "12-р сар";

const char wn_N[]      PROGMEM = "Хойд";
const char wn_NNE[]    PROGMEM = "ХХУ";
const char wn_NE[]     PROGMEM = "ХУ";
const char wn_ENE[]    PROGMEM = "УХУ";
const char wn_E[]      PROGMEM = "Зүүн";
const char wn_ESE[]    PROGMEM = "УӨУ";
const char wn_SE[]     PROGMEM = "ӨУ";
const char wn_SSE[]    PROGMEM = "ӨӨУ";
const char wn_S[]      PROGMEM = "Өмнөд";
const char wn_SSW[]    PROGMEM = "ӨӨБ";
const char wn_SW[]     PROGMEM = "ӨБ";
const char wn_WSW[]    PROGMEM = "БӨБ";
const char wn_W[]      PROGMEM = "Баруун";
const char wn_WNW[]    PROGMEM = "ББӨ";
const char wn_NW[]     PROGMEM = "БХ";
const char wn_NNW[]    PROGMEM = "ХБХ";

const char* const dow[]     PROGMEM = { sun, mon, tue, wed, thu, fri, sat };
const char* const dowf[]    PROGMEM = { sunf, monf, tuef, wedf, thuf, frif, satf };
const char* const mnths[]   PROGMEM = { jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };
const char* const wind[]    PROGMEM = { wn_N, wn_NNE, wn_NE, wn_ENE, wn_E, wn_ESE, wn_SE, wn_SSE, wn_S, wn_SSW, wn_SW, wn_WSW, wn_W, wn_WNW, wn_NW, wn_NNW, wn_N };

const char    const_PlReady[]    PROGMEM = "[бэлэн]";
const char  const_PlStopped[]    PROGMEM = "[зогссон]";
const char  const_PlConnect[]    PROGMEM = "[холбож байна]";
const char  const_DlgVolume[]    PROGMEM = "ЧАНГАР";
const char    const_DlgLost[]    PROGMEM = "* ХОЛБОО АЛДСАН *";
const char  const_DlgUpdate[]    PROGMEM = "* ШИНЭЧЛЭЖ БАЙНА *";
const char const_DlgNextion[]    PROGMEM = "NEXTION";
const char  const_waitForSD[]    PROGMEM = "SD ИНДЕКС";

const char        apNameTxt[]    PROGMEM = "AP НЭР";
#ifdef AP_PASSWORD
  const char        apPassTxt[]    PROGMEM = "НУУЦ ҮГ";
#else
  const char        apPassTxt[]    PROGMEM = "НУУЦ ҮГГҮЙ";
#endif

const char       bootstrFmt[]    PROGMEM = "Wi-fi: %s";
const char        apSettFmt[]    PROGMEM = "ХОЛБОГДОЖ HTTP://%s/ -г НЭЭ";

#ifdef UPDATEURL
  const char      updFirmware[]    PROGMEM = "Фирмварыг шинэчлэж байна";
  const char         updFiles[]    PROGMEM = "Файлуудыг шинэчлэж байна";
  const char        updFailed[]    PROGMEM = "Шинэчлэлт амжилтгүй боллоо";
#endif

const char weather_feelslike[]  PROGMEM = "мэдрэх:";
const char weather_pressure[]   PROGMEM = "даралт:";
const char weather_humidity[]   PROGMEM = "чийгшил:";
const char weather_wind[]       PROGMEM = "салхи:";

#endif

