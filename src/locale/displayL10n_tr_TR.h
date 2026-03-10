#ifndef dsp_full_loc
#define dsp_full_loc
#include <pgmspace.h>
/*************************************************************************************
    HOWTO:
    Copy this file to locale/displayL10n_custom.h
    and modify it
*************************************************************************************/
// Language: Turkish
// IETF BCP 47: "tr-TR"
const char mon[] PROGMEM = "pa";
const char tue[] PROGMEM = "sa";
const char wed[] PROGMEM = "çe";
const char thu[] PROGMEM = "pe";
const char fri[] PROGMEM = "cu";
const char sat[] PROGMEM = "cz";
const char sun[] PROGMEM = "pa";

const char monf[] PROGMEM = "Pazartesi";
const char tuef[] PROGMEM = "Salı";
const char wedf[] PROGMEM = "Çarşamba";
const char thuf[] PROGMEM = "Perşembe";
const char frif[] PROGMEM = "Cuma";
const char satf[] PROGMEM = "Cumartesi";
const char sunf[] PROGMEM = "Pazar";

const char jan[] PROGMEM = "Ocak";
const char feb[] PROGMEM = "Şubat";
const char mar[] PROGMEM = "Mart";
const char apr[] PROGMEM = "Nisan";
const char may[] PROGMEM = "Mayıs";
const char jun[] PROGMEM = "Haziran";
const char jul[] PROGMEM = "Temmuz";
const char aug[] PROGMEM = "Ağustos";
const char sep[] PROGMEM = "Eylül";
const char octt[] PROGMEM = "Ekim";
const char nov[] PROGMEM = "Kasım";
const char decc[] PROGMEM = "Aralık";

const char wn_N[]      PROGMEM = "KUZEY";
const char wn_NNE[]    PROGMEM = "NNE";
const char wn_NE[]     PROGMEM = "NE";
const char wn_ENE[]    PROGMEM = "ENE";
const char wn_E[]      PROGMEM = "DOĞU";
const char wn_ESE[]    PROGMEM = "ESE";
const char wn_SE[]     PROGMEM = "GD";
const char wn_SSE[]    PROGMEM = "SSE";
const char wn_S[]      PROGMEM = "GÜNEY";
const char wn_SSW[]    PROGMEM = "SSW";
const char wn_SW[]     PROGMEM = "SW";
const char wn_WSW[]    PROGMEM = "WSW";
const char wn_W[]      PROGMEM = "BATI";
const char wn_WNW[]    PROGMEM = "WNW";
const char wn_NW[]     PROGMEM = "NW";
const char wn_NNW[]    PROGMEM = "NNW";

const char* const dow[]     PROGMEM = { sun, mon, tue, wed, thu, fri, sat };
const char* const dowf[]    PROGMEM = { sunf, monf, tuef, wedf, thuf, frif, satf };
const char* const mnths[]   PROGMEM = { jan, feb, mar, apr, may, jun, jul, aug, sep, octt, nov, decc };
const char* const wind[]    PROGMEM = { wn_N, wn_NNE, wn_NE, wn_ENE, wn_E, wn_ESE, wn_SE, wn_SSE, wn_S, wn_SSW, wn_SW, wn_WSW, wn_W, wn_WNW, wn_NW, wn_NNW, wn_N };

const char    const_PlReady[]    PROGMEM = "[hazır]";
const char  const_PlStopped[]    PROGMEM = "[durduruldu]";
const char  const_PlConnect[]    PROGMEM = "[bağlanıyor]";
const char  const_DlgVolume[]    PROGMEM = "SES";
const char    const_DlgLost[]    PROGMEM = "* BAĞLANTI KESİLDİ *";
const char  const_DlgUpdate[]    PROGMEM = "* GÜNCELLENİYOR *";
const char const_DlgNextion[]    PROGMEM = "NEXTION";
const char const_getWeather[]    PROGMEM = "";
const char  const_waitForSD[]    PROGMEM = "SD İNDEKS";

const char        apNameTxt[]    PROGMEM = "AP ADI";
#ifdef AP_PASSWORD
  const char        apPassTxt[]    PROGMEM = "PAROLA";
#else
  const char        apPassTxt[]    PROGMEM = "PAROLASIZ";
#endif

const char       bootstrFmt[]    PROGMEM = "Wi-fi: %s";
const char        apSettFmt[]    PROGMEM = "BAĞLAN & AÇ HTTP://%s/";

#ifdef UPDATEURL
  const char      updFirmware[]    PROGMEM = "Firmware güncelleniyor";
  const char         updFiles[]    PROGMEM = "Dosyalar güncelleniyor";
  const char        updFailed[]    PROGMEM = "Güncelleme başarısız oldu";
#endif

#if EXT_WEATHER
const char       weatherFmt[]    PROGMEM = "%s, %.1f\011C \007 hissedilen: %.1f\011C \007 basınç: %d hPa \007 nem: %s%% \007 rüzgar: %.1f m/s [%s]";
#else
const char       weatherFmt[]    PROGMEM = "%s, %.1f\011C \007 basınç: %d hPa \007 nem: %s%%";
#endif
const char     weatherUnits[]    PROGMEM = "metric";   /* standard, metric, imperial */
const char      weatherLang[]    PROGMEM = "tr";       /* https://openweathermap.org/current#multi */

#endif

