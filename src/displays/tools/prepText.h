#ifndef prepText_h
#define prepText_h

#include <Arduino.h>
#include "../../core/options.h"

// Dispatcher for text preprocessing based on display type
// Routes to appropriate text conversion function

#ifdef PRINT_FIX
  #include "printFix.h"
  inline char* prepText(const char* str, bool uppercase = false) {
    return printFix(str, uppercase);
  }
#elif defined(UTF8_RUS)
  #include "utf8Rus.h"
  inline char* prepText(const char* str, bool uppercase = false) {
    return utf8Rus(str, uppercase);
  }
#else
  inline char* prepText(const char* str, bool uppercase = false) {
    static char buf[BUFLEN];
    int i = 0;
    for (; i < BUFLEN - 1 && str[i]; i++) {
      buf[i] = uppercase ? toupper(str[i]) : str[i];
    }
    buf[i] = 0;
    return buf;
  }
#endif

#endif
