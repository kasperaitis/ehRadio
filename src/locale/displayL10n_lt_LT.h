#ifndef dsp_full_loc
#define dsp_full_loc
#include <pgmspace.h>
/*************************************************************************************
    HOWTO:
    Copy this file to locale/displayL10n_custom.h
    and modify it
*************************************************************************************/
// Language: Lithuanian
// IETF BCP 47: "lt-LT"
const char mon[] PROGMEM = "pr";
const char tue[] PROGMEM = "an";
const char wed[] PROGMEM = "tr";
const char thu[] PROGMEM = "kt";
const char fri[] PROGMEM = "pn";
const char sat[] PROGMEM = "št";
const char sun[] PROGMEM = "sk";

const char monf[] PROGMEM = "pirmadienis";
const char tuef[] PROGMEM = "antradienis";
const char wedf[] PROGMEM = "trečiadienis";
const char thuf[] PROGMEM = "ketvirtadienis";
const char frif[] PROGMEM = "penktadienis";
const char satf[] PROGMEM = "šeštadienis";
const char sunf[] PROGMEM = "sekmadienis";

const char jan[] PROGMEM = "sausio";
const char feb[] PROGMEM = "vasario";
const char mar[] PROGMEM = "kovo";
const char apr[] PROGMEM = "balandžio";
const char may[] PROGMEM = "gegužės";
const char jun[] PROGMEM = "birželio";
const char jul[] PROGMEM = "liepos";
const char aug[] PROGMEM = "rugpjūčio";
const char sep[] PROGMEM = "rugsėjo";
const char oct[] PROGMEM = "spalio";
const char nov[] PROGMEM = "lapkričio";
const char dec[] PROGMEM = "gruodžio";

const char wn_N[]      PROGMEM = "ŠIAURĖS";
const char wn_NNE[]    PROGMEM = "ŠŠR";
const char wn_NE[]     PROGMEM = "ŠR";
const char wn_ENE[]    PROGMEM = "RSR";
const char wn_E[]      PROGMEM = "RYTŲ";
const char wn_ESE[]    PROGMEM = "RPR";
const char wn_SE[]     PROGMEM = "PR";
const char wn_SSE[]    PROGMEM = "PPR";
const char wn_S[]      PROGMEM = "PIETŲ";
const char wn_SSW[]    PROGMEM = "PPV";
const char wn_SW[]     PROGMEM = "PV";
const char wn_WSW[]    PROGMEM = "VPV";
const char wn_W[]      PROGMEM = "VAKARŲ";
const char wn_WNW[]    PROGMEM = "VŠV";
const char wn_NW[]     PROGMEM = "ŠV";
const char wn_NNW[]    PROGMEM = "ŠŠV";

const char* const dow[]     PROGMEM = { sun, mon, tue, wed, thu, fri, sat };
const char* const dowf[]    PROGMEM = { sunf, monf, tuef, wedf, thuf, frif, satf };
const char* const mnths[]   PROGMEM = { jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };
const char* const wind[]    PROGMEM = { wn_N, wn_NNE, wn_NE, wn_ENE, wn_E, wn_ESE, wn_SE, wn_SSE, wn_S, wn_SSW, wn_SW, wn_WSW, wn_W, wn_WNW, wn_NW, wn_NNW, wn_N };

const char    const_PlReady[]    PROGMEM = "[paruošta]";
const char  const_PlStopped[]    PROGMEM = "[sustabdyta]";
const char  const_PlConnect[]    PROGMEM = "[jungiamasi]";
const char  const_DlgVolume[]    PROGMEM = "GARSAS";
const char    const_DlgLost[]    PROGMEM = "* ATSIJUNGĘS *";
const char  const_DlgUpdate[]    PROGMEM = "* Atnaujinama *";
const char const_DlgNextion[]    PROGMEM = "NEXTION";
const char  const_waitForSD[]    PROGMEM = "INDEKSUOJAMA SD";

const char        apNameTxt[]    PROGMEM = "TAŠKO VARDAS";
#ifdef AP_PASSWORD
  const char        apPassTxt[]    PROGMEM = "SLAPTAŽODIS";
#else
  const char        apPassTxt[]    PROGMEM = "BE SLAPTAŽODŽIO";
#endif

const char       bootstrFmt[]    PROGMEM = "Wi-fi: %s";
const char        apSettFmt[]    PROGMEM = "PRISIJUNKITE IR ATIDARYKITE HTTP://%s/";

#ifdef UPDATEURL
  const char      updFirmware[]    PROGMEM = "Atnaujinama programinė įranga";
  const char         updFiles[]    PROGMEM = "Atnaujinami failai";
  const char        updFailed[]    PROGMEM = "Atnaujinimas nepavyko";
#endif

const char weather_feelslike[]   PROGMEM = "jaučiasi:";
const char weather_pressure[]    PROGMEM = "slėgis:";
const char weather_humidity[]    PROGMEM = "drėgmė:";
const char weather_wind[]        PROGMEM = "vėjas:";
const char weather_loading[]     PROGMEM = "Gaunama dabartinė orų informacija...";

const char w_clear_sky[]         PROGMEM = "Giedras dangus";
const char w_overcast[]          PROGMEM = "Debesuota";
const char w_foggy[]             PROGMEM = "Rūkas";
const char w_drizzle[]           PROGMEM = "Dulksna";
const char w_freezing_drizzle[]  PROGMEM = "Šalanti dulksna";
const char w_rain[]              PROGMEM = "Lietus";
const char w_freezing_rain[]     PROGMEM = "Šalantis lietus";
const char w_snow[]              PROGMEM = "Sniegas";
const char w_snow_grains[]       PROGMEM = "Sniego grūdeliai";
const char w_rain_showers[]      PROGMEM = "Lietaus liūtys";
const char w_snow_showers[]      PROGMEM = "Sniego liūtys";
const char w_thunderstorm[]      PROGMEM = "Audra";
const char w_thunderstorm_hail[] PROGMEM = "Audra su kruša";

#endif

