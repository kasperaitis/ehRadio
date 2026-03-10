/*
 * Copyright (c) 2026 Aivaras Kasperaitis (@kasperaitis)
 * SPDX-License-Identifier: GPL-3.0-only
 */

#ifndef UTF8LATIN_H
#define UTF8LATIN_H

#include "Arduino.h"
#include "../../core/options.h"

// Convert UTF-8 text to GLCD font character indices for Latin codepage.
// Maps Latin Extended characters to custom font glyphs (0x80-0xBF range).
// Transliterates Cyrillic characters to ASCII as fallback for mixed-script metadata.
// Use when L10N_CODEPAGE == L10N_CP_LATIN.
char* utf8Latin(const char* str, bool uppercase);

#include "utf8_common.h"
#endif // UTF8LATIN_H
