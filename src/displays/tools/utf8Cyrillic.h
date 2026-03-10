/*
 * Copyright (c) 2026 Aivaras Kasperaitis (@kasperaitis)
 * SPDX-License-Identifier: GPL-3.0-only
 */

#ifndef UTF8CYRILLIC_H
#define UTF8CYRILLIC_H

#include "Arduino.h"
#include "../../core/options.h"

char* utf8Cyrillic(const char* str, bool uppercase);

#include "utf8_common.h"
#endif // UTF8CYRILLIC_H
