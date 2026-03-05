/*
 * Copyright (c) 2026 Aivaras Kasperaitis (@kasperaitis)
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include "utf8To.h"
#include "Arduino.h"
#include <ctype.h>
#include "../../core/options.h"
#include "../dspcore.h"

#if (L10N_CODEPAGE==L10N_CP_CYRILLIC)
  #include "utf8Cyrillic.h"
#else
  #include "utf8Latin.h"
#endif

char* utf8To(const char* str, bool uppercase) {
#if (L10N_CODEPAGE==L10N_CP_CYRILLIC)
  return utf8Cyrillic(str, uppercase);
#else
  // Default: use extended mapper which covers many Latin-1 / Latin Extended / basic
  // Greek sequences and uppercasing rules. Falls back to leaving unknown UTF-8
  // sequences untouched.
  return utf8Latin(str, uppercase);
#endif
} 
