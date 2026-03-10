#ifndef _display_l10n_h
#define _display_l10n_h
namespace LANG{
//==================================================
#if L10N_LANGUAGE==be_BY  // Belarusian
  #define L10N_PATH "../../locale/displayL10n_be_BY.h"
#elif L10N_LANGUAGE==bg_BG  // Bulgarian
  #define L10N_PATH "../../locale/displayL10n_bg_BG.h"
#elif L10N_LANGUAGE==bs_BA  // Bosnian
  #define L10N_PATH "../../locale/displayL10n_bs_BA.h"
#elif L10N_LANGUAGE==cs_CZ  // Czech
  #define L10N_PATH "../../locale/displayL10n_cs_CZ.h"
#elif L10N_LANGUAGE==da_DK  // Danish
  #define L10N_PATH "../../locale/displayL10n_da_DK.h"
#elif L10N_LANGUAGE==de_DE  // German
  #define L10N_PATH "../../locale/displayL10n_de_DE.h"
#elif L10N_LANGUAGE==el_GR  // Greek
  #define L10N_PATH "../../locale/displayL10n_el_GR.h"
#elif L10N_LANGUAGE==en_US  // English
  #define L10N_PATH "../../locale/displayL10n_en_US.h"
#elif L10N_LANGUAGE==es_ES  // Spanish
  #define L10N_PATH "../../locale/displayL10n_es_ES.h"
#elif L10N_LANGUAGE==et_EE  // Estonian
  #define L10N_PATH "../../locale/displayL10n_et_EE.h"
#elif L10N_LANGUAGE==fi_FI  // Finnish
  #define L10N_PATH "../../locale/displayL10n_fi_FI.h"
#elif L10N_LANGUAGE==fr_FR  // French
  #define L10N_PATH "../../locale/displayL10n_fr_FR.h"
#elif L10N_LANGUAGE==hr_HR  // Croatian
  #define L10N_PATH "../../locale/displayL10n_hr_HR.h"
#elif L10N_LANGUAGE==hu_HU  // Hungarian
  #define L10N_PATH "../../locale/displayL10n_hu_HU.h"
#elif L10N_LANGUAGE==is_IS  // Icelandic
  #define L10N_PATH "../../locale/displayL10n_is_IS.h"
#elif L10N_LANGUAGE==kk_KZ  // Kazakh
  #define L10N_PATH "../../locale/displayL10n_kk_KZ.h"
#elif L10N_LANGUAGE==ky_KG  // Kyrgyz
  #define L10N_PATH "../../locale/displayL10n_ky_KG.h"
#elif L10N_LANGUAGE==lt_LT  // Lithuanian
  #define L10N_PATH "../../locale/displayL10n_lt_LT.h"
#elif L10N_LANGUAGE==lv_LV  // Latvian
  #define L10N_PATH "../../locale/displayL10n_lv_LV.h"
#elif L10N_LANGUAGE==me_ME  // Montenegrin
  #define L10N_PATH "../../locale/displayL10n_me_ME.h"
#elif L10N_LANGUAGE==mk_MK  // Macedonian
  #define L10N_PATH "../../locale/displayL10n_mk_MK.h"
#elif L10N_LANGUAGE==mn_MN  // Mongolian
  #define L10N_PATH "../../locale/displayL10n_mn_MN.h"
#elif L10N_LANGUAGE==nl_NL  // Dutch
  #define L10N_PATH "../../locale/displayL10n_nl_NL.h"
#elif L10N_LANGUAGE==no_NO  // Norwegian
  #define L10N_PATH "../../locale/displayL10n_no_NO.h"
#elif L10N_LANGUAGE==pl_PL  // Polish
  #define L10N_PATH "../../locale/displayL10n_pl_PL.h"
#elif L10N_LANGUAGE==pt_PT  // Portuguese
  #define L10N_PATH "../../locale/displayL10n_pt_PT.h"
#elif L10N_LANGUAGE==ro_RO  // Romanian
  #define L10N_PATH "../../locale/displayL10n_ro_RO.h"
#elif L10N_LANGUAGE==ru_RU  // Russian
  #define L10N_PATH "../../locale/displayL10n_ru_RU.h"
#elif L10N_LANGUAGE==sk_SK  // Slovak
  #define L10N_PATH "../../locale/displayL10n_sk_SK.h"
#elif L10N_LANGUAGE==sl_SI  // Slovenian
  #define L10N_PATH "../../locale/displayL10n_sl_SI.h"
#elif L10N_LANGUAGE==sr_RS  // Serbian
  #define L10N_PATH "../../locale/displayL10n_sr_RS.h"
#elif L10N_LANGUAGE==sv_SE  // Swedish
  #define L10N_PATH "../../locale/displayL10n_sv_SE.h"
#elif L10N_LANGUAGE==tg_TJ  // Tajik
  #define L10N_PATH "../../locale/displayL10n_tg_TJ.h"
#elif L10N_LANGUAGE==tr_TR  // Turkish
  #define L10N_PATH "../../locale/displayL10n_tr_TR.h"
#elif L10N_LANGUAGE==uk_UA  // Ukrainian
  #define L10N_PATH "../../locale/displayL10n_uk_UA.h"
#elif L10N_LANGUAGE==uz_UZ  // Uzbek
  #define L10N_PATH "../../locale/displayL10n_uz_UZ.h"
#else  // fallback
  #define L10N_PATH "../../locale/displayL10n_en_US.h"
#endif

#if __has_include("../../locale/displayL10n_custom.h")
  #include "../../locale/displayL10n_custom.h"
#else
  #include L10N_PATH
#endif
//==================================================
}

#endif // _display_l10n_h
