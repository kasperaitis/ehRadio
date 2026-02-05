#ifndef rgbled_h
#define rgbled_h
#pragma once
#include <Arduino.h>
#include "core/options.h"

void rgbled_init();
void rgbled_loop();
void rgbled_set(uint8_t r, uint8_t g, uint8_t b);
void rgbled_playing();
void rgbled_stopped();
void rgbled_trackchange();

bool rgbled_is_initialized();

#endif // rgbled_h
