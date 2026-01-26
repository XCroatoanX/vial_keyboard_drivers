#pragma once
#include "quantum.h"

void pet_update_state(uint8_t wpm, led_t led_state);
void render_luna(int LUNA_X, int LUNA_Y);
bool pet_process_record(uint16_t keycode, keyrecord_t *record);