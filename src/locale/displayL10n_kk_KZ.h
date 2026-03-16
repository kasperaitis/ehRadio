#ifndef dsp_full_loc
#define dsp_full_loc
#include <pgmspace.h>
/*************************************************************************************
    HOWTO:
    Copy this file to locale/displayL10n_custom.h
    and modify it
*************************************************************************************/
// Language: Kazakh
// IETF BCP 47: "kk-KZ"
const char mon[] PROGMEM = "дс";
const char tue[] PROGMEM = "ср";
const char wed[] PROGMEM = "сш";
const char thu[] PROGMEM = "бт";
const char fri[] PROGMEM = "жм";
const char sat[] PROGMEM = "сн";
const char sun[] PROGMEM = "жк";

const char monf[] PROGMEM = "дүйсенбі";
const char tuef[] PROGMEM = "сейсенбі";
const char wedf[] PROGMEM = "сәрсенбі";
const char thuf[] PROGMEM = "бейсенбі";
const char frif[] PROGMEM = "жұма";
const char satf[] PROGMEM = "сенбі";
const char sunf[] PROGMEM = "жексенбі";

const char jan[] PROGMEM = "қаңтар";
const char feb[] PROGMEM = "Ақпан";
const char mar[] PROGMEM = "наурыз";
const char apr[] PROGMEM = "сәуір";
const char may[] PROGMEM = "мамыр";
const char jun[] PROGMEM = "маусым";
const char jul[] PROGMEM = "шілде";
const char aug[] PROGMEM = "тамыз";
const char sep[] PROGMEM = "қыркүйек";
const char oct[] PROGMEM = "қазан";
const char nov[] PROGMEM = "қараша";
const char dec[] PROGMEM = "желтоқсан";

const char wn_N[]      PROGMEM = "Солтүстік";
const char wn_NNE[]    PROGMEM = "ССШ";
const char wn_NE[]     PROGMEM = "СШ";
const char wn_ENE[]    PROGMEM = "ШСШ";
const char wn_E[]      PROGMEM = "Шығыс";
const char wn_ESE[]    PROGMEM = "ШЖС";
const char wn_SE[]     PROGMEM = "ЖШ";
const char wn_SSE[]    PROGMEM = "ЖЖШ";
const char wn_S[]      PROGMEM = "Оңтүстік";
const char wn_SSW[]    PROGMEM = "ЖЖБ";
const char wn_SW[]     PROGMEM = "ЖБ";
const char wn_WSW[]    PROGMEM = "БЖБ";
const char wn_W[]      PROGMEM = "Батыс";
const char wn_WNW[]    PROGMEM = "ББЖ";
const char wn_NW[]     PROGMEM = "БС";
const char wn_NNW[]    PROGMEM = "СБС";

const char* const dow[]     PROGMEM = { sun, mon, tue, wed, thu, fri, sat };
const char* const dowf[]    PROGMEM = { sunf, monf, tuef, wedf, thuf, frif, satf };
const char* const mnths[]   PROGMEM = { jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };
const char* const wind[]    PROGMEM = { wn_N, wn_NNE, wn_NE, wn_ENE, wn_E, wn_ESE, wn_SE, wn_SSE, wn_S, wn_SSW, wn_SW, wn_WSW, wn_W, wn_WNW, wn_NW, wn_NNW, wn_N };

const char    const_PlReady[]    PROGMEM = "[дайын]";
const char  const_PlStopped[]    PROGMEM = "[тоқтатылды]";
const char  const_PlConnect[]    PROGMEM = "[қосылуда]";
const char  const_DlgVolume[]    PROGMEM = "КҮШІ";
const char    const_DlgLost[]    PROGMEM = "* ҚОСЫЛЫС ЖОҚ *";
const char  const_DlgUpdate[]    PROGMEM = "* ЖАҢАРТЫЛУДА *";
const char const_DlgNextion[]    PROGMEM = "NEXTION";
const char  const_waitForSD[]    PROGMEM = "SD ИНДЕКС";

const char        apNameTxt[]    PROGMEM = "AP АТАУЫ";
#ifdef AP_PASSWORD
  const char        apPassTxt[]    PROGMEM = "ҚҰПИЯ";
#else
  const char        apPassTxt[]    PROGMEM = "ҚҰПИЯСЫЗ";
#endif

const char       bootstrFmt[]    PROGMEM = "Wi-fi: %s";
const char        apSettFmt[]    PROGMEM = "ҚОСЫЛЫҢЫЗ ЖӘНЕ HTTP://%s/ ашыңыз";

#ifdef UPDATEURL
  const char      updFirmware[]    PROGMEM = "Фирма жаңарту";
  const char         updFiles[]    PROGMEM = "Қажетті файлдар жаңартылуда";
  const char        updFailed[]    PROGMEM = "Жаңарту сәтсіз аяқталды";
#endif

const char weather_feelslike[]  PROGMEM = "сезіледі:";
const char weather_pressure[]   PROGMEM = "қысым:";
const char weather_humidity[]   PROGMEM = "ылғал:";
const char weather_wind[]       PROGMEM = "жел:";
const char weather_loading[]    PROGMEM = "Ауа райы деректерін жүктеу...";

// WMO Weather Code Translations (for Open-Meteo)
const char w_clear_sky[]         PROGMEM = "Ашық аспан";
const char w_overcast[]          PROGMEM = "Бұлтты";
const char w_foggy[]             PROGMEM = "Тұман";
const char w_drizzle[]           PROGMEM = "Сіркіреу";
const char w_freezing_drizzle[]  PROGMEM = "Үсіп тұрған сіркіреу";
const char w_rain[]              PROGMEM = "Жаңбыр";
const char w_freezing_rain[]     PROGMEM = "Үсіп тұрған жаңбыр";
const char w_snow[]              PROGMEM = "Қар";
const char w_snow_grains[]       PROGMEM = "Қар тәншелері";
const char w_rain_showers[]      PROGMEM = "Жаңбырлы нөсер";
const char w_snow_showers[]      PROGMEM = "Қарлы нөсер";
const char w_thunderstorm[]      PROGMEM = "Най бұркау";
const char w_thunderstorm_hail[] PROGMEM = "Бұркау мен бұршақ";

#endif

