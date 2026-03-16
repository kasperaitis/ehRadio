#ifndef dsp_full_loc
#define dsp_full_loc
#include <pgmspace.h>
/*************************************************************************************
    HOWTO:
    Copy this file to locale/displayL10n_custom.h
    and modify it
*************************************************************************************/
// Language: Spanish
// IETF BCP 47: "es-ES"
const char mon[] PROGMEM = "lu";
const char tue[] PROGMEM = "ma";
const char wed[] PROGMEM = "mi";
const char thu[] PROGMEM = "ju";
const char fri[] PROGMEM = "vi";
const char sat[] PROGMEM = "sa";
const char sun[] PROGMEM = "do";

const char monf[] PROGMEM = "Lunes";
const char tuef[] PROGMEM = "Martes";
const char wedf[] PROGMEM = "Miércoles";
const char thuf[] PROGMEM = "Jueves";
const char frif[] PROGMEM = "Viernes";
const char satf[] PROGMEM = "Sábado";
const char sunf[] PROGMEM = "Domingo";

const char jan[] PROGMEM = "Enero";
const char feb[] PROGMEM = "Febrero";
const char mar[] PROGMEM = "Marzo";
const char apr[] PROGMEM = "Abril";
const char may[] PROGMEM = "Mayo";
const char jun[] PROGMEM = "Junio";
const char jul[] PROGMEM = "Julio";
const char aug[] PROGMEM = "Agosto";
const char sep[] PROGMEM = "Septiembre";
const char oct[] PROGMEM = "Octubre";
const char nov[] PROGMEM = "Noviembre";
const char dec[] PROGMEM = "Diciembre";

const char wn_N[]      PROGMEM = "NORTE";
const char wn_NNE[]    PROGMEM = "NNE";
const char wn_NE[]     PROGMEM = "NE";
const char wn_ENE[]    PROGMEM = "ENE";
const char wn_E[]      PROGMEM = "ESTE";
const char wn_ESE[]    PROGMEM = "ESE";
const char wn_SE[]     PROGMEM = "SE";
const char wn_SSE[]    PROGMEM = "SSE";
const char wn_S[]      PROGMEM = "SUR";
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

const char    const_PlReady[]    PROGMEM = "[listo]";
const char  const_PlStopped[]    PROGMEM = "[detenido]";
const char  const_PlConnect[]    PROGMEM = "[conectando]";
const char  const_DlgVolume[]    PROGMEM = "VOLUMEN";
const char    const_DlgLost[]    PROGMEM = "* SIN CONEXIÓN *";
const char  const_DlgUpdate[]    PROGMEM = "* ACTUALIZANDO *";
const char const_DlgNextion[]    PROGMEM = "NEXTION";
const char  const_waitForSD[]    PROGMEM = "INDICE SD";

const char        apNameTxt[]    PROGMEM = "NOMBRE AP";
#ifdef AP_PASSWORD
  const char        apPassTxt[]    PROGMEM = "CONTRASEÑA";
#else
  const char        apPassTxt[]    PROGMEM = "SIN CONTRASEÑA";
#endif

const char       bootstrFmt[]    PROGMEM = "Wi-fi: %s";
const char        apSettFmt[]    PROGMEM = "CONECTA Y ABRE HTTP://%s/";

#ifdef UPDATEURL
  const char      updFirmware[]    PROGMEM = "Actualizando firmware";
  const char         updFiles[]    PROGMEM = "Actualizando archivos";
  const char        updFailed[]    PROGMEM = "Actualización fallida";
#endif

const char weather_feelslike[]  PROGMEM = "sensación:";
const char weather_pressure[]   PROGMEM = "presión:";
const char weather_humidity[]   PROGMEM = "humedad:";
const char weather_wind[]       PROGMEM = "viento:";
const char weather_loading[]    PROGMEM = "Obteniendo datos del tiempo...";

// WMO Weather Code Translations (for Open-Meteo)
const char w_clear_sky[]         PROGMEM = "Cielo despejado";
const char w_overcast[]          PROGMEM = "Nublado";
const char w_foggy[]             PROGMEM = "Niebla";
const char w_drizzle[]           PROGMEM = "Llovizna";
const char w_freezing_drizzle[]  PROGMEM = "Llovizna helada";
const char w_rain[]              PROGMEM = "Lluvia";
const char w_freezing_rain[]     PROGMEM = "Lluvia helada";
const char w_snow[]              PROGMEM = "Nieve";
const char w_snow_grains[]       PROGMEM = "Gránulos de nieve";
const char w_rain_showers[]      PROGMEM = "Chubascos";
const char w_snow_showers[]      PROGMEM = "Nevadas";
const char w_thunderstorm[]      PROGMEM = "Tormenta";
const char w_thunderstorm_hail[] PROGMEM = "Tormenta con granizo";

#endif

