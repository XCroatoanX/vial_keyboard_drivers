#pragma once

#include "quantum.h"

/* settings */
#define MIN_WALK_SPEED      10
#define MIN_RUN_SPEED       40

/* advanced settings */
#define ANIM_FRAME_DURATION 200  // how long each frame lasts in ms
#define ANIM_SIZE           96   // number of bytes in array

/* timers */
extern uint32_t anim_timer;
extern uint32_t anim_sleep;

/* current frame */
extern uint8_t current_frame;

/* status variables */
extern int   current_wpm;
extern led_t led_usb_state;

extern bool isSneaking;
extern bool isJumping;
extern bool showedJump;

/* function declarations */
void render_luna(int LUNA_X, int LUNA_Y);
bool process_record_luna(uint16_t keycode, keyrecord_t *record);