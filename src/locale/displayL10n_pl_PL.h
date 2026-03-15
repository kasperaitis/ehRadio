#ifndef dsp_full_loc
#define dsp_full_loc
#include <pgmspace.h>
/*************************************************************************************
    HOWTO:
    Copy this file to locale/displayL10n_custom.h
    and modify it
*************************************************************************************/
// Language: Polish
// IETF BCP 47: "pl-PL"
const char mon[] PROGMEM = "pn";
const char tue[] PROGMEM = "wt";
const char wed[] PROGMEM = "śr";
const char thu[] PROGMEM = "cz";
const char fri[] PROGMEM = "pt";
const char sat[] PROGMEM = "sb";
const char sun[] PROGMEM = "nd";

const char monf[] PROGMEM = "Poniedziałek";
const char tuef[] PROGMEM = "Wtorek";
const char wedf[] PROGMEM = "Środa";
const char thuf[] PROGMEM = "Czwartek";
const char frif[] PROGMEM = "Piątek";
const char satf[] PROGMEM = "Sobota";
const char sunf[] PROGMEM = "Niedziela";

const char jan[] PROGMEM = "Styczeń";
const char feb[] PROGMEM = "Luty";
const char mar[] PROGMEM = "Marzec";
const char apr[] PROGMEM = "Kwiecień";
const char may[] PROGMEM = "Maj";
const char jun[] PROGMEM = "Czerwiec";
const char jul[] PROGMEM = "Lipiec";
const char aug[] PROGMEM = "Sierpień";
const char sep[] PROGMEM = "Wrzesień";
const char oct[] PROGMEM = "Październik";
const char nov[] PROGMEM = "Listopad";
const char dec[] PROGMEM = "Grudzień";

const char wn_N[]      PROGMEM = "PÓŁNOC";
const char wn_NNE[]    PROGMEM = "NNE";
const char wn_NE[]     PROGMEM = "NE";
const char wn_ENE[]    PROGMEM = "ENE";
const char wn_E[]      PROGMEM = "WSCHÓD";
const char wn_ESE[]    PROGMEM = "ESE";
const char wn_SE[]     PROGMEM = "SE";
const char wn_SSE[]    PROGMEM = "SSE";
const char wn_S[]      PROGMEM = "POŁUDNIE";
const char wn_SSW[]    PROGMEM = "SSW";
const char wn_SW[]     PROGMEM = "SW";
const char wn_WSW[]    PROGMEM = "WSW";
const char wn_W[]      PROGMEM = "ZACHÓD";
const char wn_WNW[]    PROGMEM = "WNW";
const char wn_NW[]     PROGMEM = "NW";
const char wn_NNW[]    PROGMEM = "NNW";

const char* const dow[]     PROGMEM = { sun, mon, tue, wed, thu, fri, sat };
const char* const dowf[]    PROGMEM = { sunf, monf, tuef, wedf, thuf, frif, satf };
const char* const mnths[]   PROGMEM = { jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };
const char* const wind[]    PROGMEM = { wn_N, wn_NNE, wn_NE, wn_ENE, wn_E, wn_ESE, wn_SE, wn_SSE, wn_S, wn_SSW, wn_SW, wn_WSW, wn_W, wn_WNW, wn_NW, wn_NNW, wn_N };

const char    const_PlReady[]    PROGMEM = "[gotowy]";
const char  const_PlStopped[]    PROGMEM = "[zatrzymany]";
const char  const_PlConnect[]    PROGMEM = "[łączenie]";
const char  const_DlgVolume[]    PROGMEM = "GŁOŚNOŚĆ";
const char    const_DlgLost[]    PROGMEM = "* BRAK POŁĄCZENIA *";
const char  const_DlgUpdate[]    PROGMEM = "* AKTUALIZACJA *";
const char const_DlgNextion[]    PROGMEM = "NEXTION";
const char  const_waitForSD[]    PROGMEM = "INDEKS SD";

const char        apNameTxt[]    PROGMEM = "NAZWA AP";
#ifdef AP_PASSWORD
  const char        apPassTxt[]    PROGMEM = "HASŁO";
#else
  const char        apPassTxt[]    PROGMEM = "BRAK HASŁA";
#endif

const char       bootstrFmt[]    PROGMEM = "Wi-fi: %s";
const char        apSettFmt[]    PROGMEM = "POŁĄCZ I OTWÓRZ HTTP://%s/";

#ifdef UPDATEURL
  const char      updFirmware[]    PROGMEM = "Aktualizacja oprogramowania";
  const char         updFiles[]    PROGMEM = "Aktualizacja plików";
  const char        updFailed[]    PROGMEM = "Aktualizacja nie powiodła się";
#endif

const char weather_feelslike[]  PROGMEM = "odczuwalna:";
const char weather_pressure[]   PROGMEM = "ciśnienie:";
const char weather_humidity[]   PROGMEM = "wilgotność:";
const char weather_wind[]       PROGMEM = "wiatr:";

#endif

