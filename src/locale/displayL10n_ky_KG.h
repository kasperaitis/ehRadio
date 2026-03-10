#ifndef dsp_full_loc
#define dsp_full_loc
#include <pgmspace.h>
/*************************************************************************************
    HOWTO:
    Copy this file to locale/displayL10n_custom.h
    and modify it
*************************************************************************************/
// Language: Kyrgyz
// IETF BCP 47: "ky-KG"
const char mon[] PROGMEM = "дш";
const char tue[] PROGMEM = "сш";
const char wed[] PROGMEM = "чш";
const char thu[] PROGMEM = "пш";
const char fri[] PROGMEM = "жм";
const char sat[] PROGMEM = "шб";
const char sun[] PROGMEM = "як";

const char monf[] PROGMEM = "дүйшөмбү";
const char tuef[] PROGMEM = "шейшемби";
const char wedf[] PROGMEM = "шершемби";
const char thuf[] PROGMEM = "бейшемби";
const char frif[] PROGMEM = "жума";
const char satf[] PROGMEM = "ишемби";
const char sunf[] PROGMEM = "жаңы";

const char jan[] PROGMEM = "январь";
const char feb[] PROGMEM = "февраль";
const char mar[] PROGMEM = "март";
const char apr[] PROGMEM = "апрель";
const char may[] PROGMEM = "май";
const char jun[] PROGMEM = "июнь";
const char jul[] PROGMEM = "июль";
const char aug[] PROGMEM = "август";
const char sep[] PROGMEM = "сентябрь";
const char octt[] PROGMEM = "октябрь";
const char nov[] PROGMEM = "ноябрь";
const char decc[] PROGMEM = "декабрь";

const char wn_N[]      PROGMEM = "Т";
const char wn_NNE[]    PROGMEM = "ТТШ";
const char wn_NE[]     PROGMEM = "ТШ";
const char wn_ENE[]    PROGMEM = "ШТШ";
const char wn_E[]      PROGMEM = "Ш";
const char wn_ESE[]    PROGMEM = "ШЖТ";
const char wn_SE[]     PROGMEM = "ЖШ";
const char wn_SSE[]    PROGMEM = "ЖЖШ";
const char wn_S[]      PROGMEM = "Ж";
const char wn_SSW[]    PROGMEM = "ЖЖБ";
const char wn_SW[]     PROGMEM = "ЖБ";
const char wn_WSW[]    PROGMEM = "БЖБ";
const char wn_W[]      PROGMEM = "Б";
const char wn_WNW[]    PROGMEM = "ББЖ";
const char wn_NW[]     PROGMEM = "БТ";
const char wn_NNW[]    PROGMEM = "ТБТ";

const char* const dow[]     PROGMEM = { sun, mon, tue, wed, thu, fri, sat };
const char* const dowf[]    PROGMEM = { sunf, monf, tuef, wedf, thuf, frif, satf };
const char* const mnths[]   PROGMEM = { jan, feb, mar, apr, may, jun, jul, aug, sep, octt, nov, decc };
const char* const wind[]    PROGMEM = { wn_N, wn_NNE, wn_NE, wn_ENE, wn_E, wn_ESE, wn_SE, wn_SSE, wn_S, wn_SSW, wn_SW, wn_WSW, wn_W, wn_WNW, wn_NW, wn_NNW, wn_N };

const char    const_PlReady[]    PROGMEM = "[дайын]";
const char  const_PlStopped[]    PROGMEM = "[токтотулган]";
const char  const_PlConnect[]    PROGMEM = "[туташтырылууда]";
const char  const_DlgVolume[]    PROGMEM = "КҮЧ";
const char    const_DlgLost[]    PROGMEM = "* УЛАНЫШ ЖОК *";
const char  const_DlgUpdate[]    PROGMEM = "* ЖАҢЫРТЫЛУУДA *";
const char const_DlgNextion[]    PROGMEM = "NEXTION";
const char const_getWeather[]    PROGMEM = "";
const char  const_waitForSD[]    PROGMEM = "SD ИНДЕКС";

const char        apNameTxt[]    PROGMEM = "AP АТЫ";
#ifdef AP_PASSWORD
  const char        apPassTxt[]    PROGMEM = "КУПИЯ";
#else
  const char        apPassTxt[]    PROGMEM = "КУПИЯСЫЗ";
#endif

const char       bootstrFmt[]    PROGMEM = "Wi-fi: %s";
const char        apSettFmt[]    PROGMEM = "ТУТАШЫҢЫЗ ЖАНА HTTP://%s/ АЧЫҢЫЗ";

#ifdef UPDATEURL
  const char      updFirmware[]    PROGMEM = "Фирма жаңылануусу";
  const char         updFiles[]    PROGMEM = "Талап кылынган файлдар жаңыланууда";
  const char        updFailed[]    PROGMEM = "Жаңылоо ийгиликсиз аяктады";
#endif

#if EXT_WEATHER
const char       weatherFmt[]    PROGMEM = "%s, %.1f\011C \007 сезим: %.1f\011C \007 басым: %d гПа \007 нымдуулук: %s%% \007 шамал: %.1f m/s [%s]";
#else
const char       weatherFmt[]    PROGMEM = "%s, %.1f\011C \007 басым: %d гПа \007 нымдуулук: %s%%";
#endif
const char     weatherUnits[]    PROGMEM = "metric";   /* standard, metric, imperial */
const char      weatherLang[]    PROGMEM = "en";       /* https://openweathermap.org/current#multi */

#endif

