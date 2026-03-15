#ifndef dsp_full_loc
#define dsp_full_loc
#include <pgmspace.h>
/*************************************************************************************
    HOWTO:
    Copy this file to locale/displayL10n_custom.h
    and modify it
*************************************************************************************/
// Language: French
// IETF BCP 47: "fr-FR"
const char mon[] PROGMEM = "lu";
const char tue[] PROGMEM = "ma";
const char wed[] PROGMEM = "me";
const char thu[] PROGMEM = "je";
const char fri[] PROGMEM = "ve";
const char sat[] PROGMEM = "sa";
const char sun[] PROGMEM = "di";

const char monf[] PROGMEM = "Lundi";
const char tuef[] PROGMEM = "Mardi";
const char wedf[] PROGMEM = "Mercredi";
const char thuf[] PROGMEM = "Jeudi";
const char frif[] PROGMEM = "Vendredi";
const char satf[] PROGMEM = "Samedi";
const char sunf[] PROGMEM = "Dimanche";

const char jan[] PROGMEM = "Janvier";
const char feb[] PROGMEM = "Février";
const char mar[] PROGMEM = "Mars";
const char apr[] PROGMEM = "Avril";
const char may[] PROGMEM = "Mai";
const char jun[] PROGMEM = "Juin";
const char jul[] PROGMEM = "Juillet";
const char aug[] PROGMEM = "Août";
const char sep[] PROGMEM = "Septembre";
const char oct[] PROGMEM = "Octobre";
const char nov[] PROGMEM = "Novembre";
const char dec[] PROGMEM = "Décembre";

const char wn_N[]      PROGMEM = "NORD";
const char wn_NNE[]    PROGMEM = "NNE";
const char wn_NE[]     PROGMEM = "NE";
const char wn_ENE[]    PROGMEM = "ENE";
const char wn_E[]      PROGMEM = "EST";
const char wn_ESE[]    PROGMEM = "ESE";
const char wn_SE[]     PROGMEM = "SE";
const char wn_SSE[]    PROGMEM = "SSE";
const char wn_S[]      PROGMEM = "SUD";
const char wn_SSW[]    PROGMEM = "SSW";
const char wn_SW[]     PROGMEM = "SW";
const char wn_WSW[]    PROGMEM = "WSW";
const char wn_W[]      PROGMEM = "OUEST";
const char wn_WNW[]    PROGMEM = "WNW";
const char wn_NW[]     PROGMEM = "NW";
const char wn_NNW[]    PROGMEM = "NNW";

const char* const dow[]     PROGMEM = { sun, mon, tue, wed, thu, fri, sat };
const char* const dowf[]    PROGMEM = { sunf, monf, tuef, wedf, thuf, frif, satf };
const char* const mnths[]   PROGMEM = { jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };
const char* const wind[]    PROGMEM = { wn_N, wn_NNE, wn_NE, wn_ENE, wn_E, wn_ESE, wn_SE, wn_SSE, wn_S, wn_SSW, wn_SW, wn_WSW, wn_W, wn_WNW, wn_NW, wn_NNW, wn_N };

const char    const_PlReady[]    PROGMEM = "[prêt]";
const char  const_PlStopped[]    PROGMEM = "[arrêt]";
const char  const_PlConnect[]    PROGMEM = "[connexion]";
const char  const_DlgVolume[]    PROGMEM = "VOLUME";
const char    const_DlgLost[]    PROGMEM = "* CONNEXION PERDUE *";
const char  const_DlgUpdate[]    PROGMEM = "* MISE À JOUR *";
const char const_DlgNextion[]    PROGMEM = "NEXTION";
const char  const_waitForSD[]    PROGMEM = "INDEXATION SD";

const char        apNameTxt[]    PROGMEM = "NOM AP";
#ifdef AP_PASSWORD
  const char        apPassTxt[]    PROGMEM = "MOT DE PASSE";
#else
  const char        apPassTxt[]    PROGMEM = "SANS MOT DE PASSE";
#endif

const char       bootstrFmt[]    PROGMEM = "Wi-fi: %s";
const char        apSettFmt[]    PROGMEM = "CONNECTEZ-VOUS & OUVREZ HTTP://%s/";

#ifdef UPDATEURL
  const char      updFirmware[]    PROGMEM = "Mise à jour du firmware";
  const char         updFiles[]    PROGMEM = "Mise à jour des fichiers";
  const char        updFailed[]    PROGMEM = "Échec de la mise à jour";
#endif

const char weather_feelslike[]  PROGMEM = "ressenti:";
const char weather_pressure[]   PROGMEM = "pression:";
const char weather_humidity[]   PROGMEM = "humidité:";
const char weather_wind[]       PROGMEM = "vent:";

#endif

