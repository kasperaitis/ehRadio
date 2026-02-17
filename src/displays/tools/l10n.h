#ifndef _display_l10n_h
#define _display_l10n_h
namespace LANG{
//==================================================

#ifndef L10N_LANGUAGE
  #define L10N_PATH "../../locale/displayL10n_en.h"
#else
  #if L10N_LANGUAGE==RU
    #define L10N_PATH "../../locale/displayL10n_ru.h"
  //#elif L10N_LANGUAGE==CA
    //#define L10N_PATH "../../locale/displayL10n_ca.h"
  #else
    #define L10N_PATH "../../locale/displayL10n_en.h"
  #endif
#endif

#if __has_include("../../locale/displayL10n_custom.h")
  #include "../../locale/displayL10n_custom.h"
#else
  #include L10N_PATH
#endif
//==================================================
}
#endif
