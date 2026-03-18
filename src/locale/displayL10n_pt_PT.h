#ifndef dsp_full_loc
#define dsp_full_loc
#include <pgmspace.h>
/*************************************************************************************
    HOWTO:
    Copy this file to locale/displayL10n_custom.h
    and modify it
*************************************************************************************/
// Language: Portuguese
// IETF BCP 47: "pt-PT"
const char mon[] PROGMEM = "se";
const char tue[] PROGMEM = "te";
const char wed[] PROGMEM = "qa";
const char thu[] PROGMEM = "qi";
const char fri[] PROGMEM = "sx";
const char sat[] PROGMEM = "sá";
const char sun[] PROGMEM = "do";

const char monf[] PROGMEM = "Segunda-feira";
const char tuef[] PROGMEM = "Terça-feira";
const char wedf[] PROGMEM = "Quarta-feira";
const char thuf[] PROGMEM = "Quinta-feira";
const char frif[] PROGMEM = "Sexta-feira";
const char satf[] PROGMEM = "Sábado";
const char sunf[] PROGMEM = "Domingo";

const char jan[] PROGMEM = "Janeiro";
const char feb[] PROGMEM = "Fevereiro";
const char mar[] PROGMEM = "Março";
const char apr[] PROGMEM = "Abril";
const char may[] PROGMEM = "Maio";
const char jun[] PROGMEM = "Junho";
const char jul[] PROGMEM = "Julho";
const char aug[] PROGMEM = "Agosto";
const char sep[] PROGMEM = "Setembro";
const char oct[] PROGMEM = "Outubro";
const char nov[] PROGMEM = "Novembro";
const char dec[] PROGMEM = "Dezembro";

const char wn_N[]      PROGMEM = "NORTE";
const char wn_NNE[]    PROGMEM = "NNE";
const char wn_NE[]     PROGMEM = "NE";
const char wn_ENE[]    PROGMEM = "ENE";
const char wn_E[]      PROGMEM = "LESTE";
const char wn_ESE[]    PROGMEM = "ESE";
const char wn_SE[]     PROGMEM = "SE";
const char wn_SSE[]    PROGMEM = "SSE";
const char wn_S[]      PROGMEM = "SUL";
const char wn_SSW[]    PROGMEM = "SSW";
const char wn_SW[]     PROGMEM = "SW";
const char wn_WSW[]    PROGMEM = "WSW";
const char wn_W[]      PROGMEM = "OESTE";
const char wn_WNW[]    PROGMEM = "WNW";
const char wn_NW[]     PROGMEM = "NW";
const char wn_NNW[]    PROGMEM = "NNW";

const char* const dow[]     PROGMEM = { sun, mon, tue, wed, thu, fri, sat };
const char* const dowf[]    PROGMEM = { sunf, monf, tuef, wedf, thuf, frif, satf };
const char* const mnths[]   PROGMEM = { jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };
const char* const wind[]    PROGMEM = { wn_N, wn_NNE, wn_NE, wn_ENE, wn_E, wn_ESE, wn_SE, wn_SSE, wn_S, wn_SSW, wn_SW, wn_WSW, wn_W, wn_WNW, wn_NW, wn_NNW, wn_N };

const char    const_PlReady[]    PROGMEM = "[pronto]";
const char  const_PlStopped[]    PROGMEM = "[parado]";
const char  const_PlConnect[]    PROGMEM = "[conectando]";
const char  const_DlgVolume[]    PROGMEM = "VOLUME";
const char    const_DlgLost[]    PROGMEM = "* SEM CONEXÃO *";
const char  const_DlgUpdate[]    PROGMEM = "* ATUALIZANDO *";
const char const_DlgNextion[]    PROGMEM = "NEXTION";
const char  const_waitForSD[]    PROGMEM = "INDICE SD";

const char        apNameTxt[]    PROGMEM = "NOME AP";
#ifdef AP_PASSWORD
  const char        apPassTxt[]    PROGMEM = "SENHA";
#else
  const char        apPassTxt[]    PROGMEM = "SEM SENHA";
#endif

const char       bootstrFmt[]    PROGMEM = "Wi-fi: %s";
const char        apSettFmt[]    PROGMEM = "CONECTE E ABRA HTTP://%s/";

#ifdef UPDATEURL
  const char      updFirmware[]    PROGMEM = "Atualizando firmware";
  const char         updFiles[]    PROGMEM = "Atualizando arquivos";
  const char        updFailed[]    PROGMEM = "Atualização falhou";
#endif

const char weather_feelslike[]  PROGMEM = "sensação:";
const char weather_pressure[]   PROGMEM = "pressão:";
const char weather_humidity[]   PROGMEM = "humidade:";
const char weather_wind[]       PROGMEM = "vento:";
const char weather_loading[]    PROGMEM = "A obter dados meteorológicos...";

// WMO Weather Code Translations (for Open-Meteo)
const char w_clear_sky[]         PROGMEM = "Céu limpo";
const char w_overcast[]          PROGMEM = "Nublado";
const char w_foggy[]             PROGMEM = "Nevoeiro";
const char w_drizzle[]           PROGMEM = "Chuvisco";
const char w_freezing_drizzle[]  PROGMEM = "Chuvisco gelado";
const char w_rain[]              PROGMEM = "Chuva";
const char w_freezing_rain[]     PROGMEM = "Chuva gelada";
const char w_snow[]              PROGMEM = "Neve";
const char w_snow_grains[]       PROGMEM = "Grãos de neve";
const char w_rain_showers[]      PROGMEM = "Aguaceiros";
const char w_snow_showers[]      PROGMEM = "Nevadas";
const char w_thunderstorm[]      PROGMEM = "Trovoada";
const char w_thunderstorm_hail[] PROGMEM = "Trovoada com granizo";

#endif

