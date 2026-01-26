#include "luna.h"

/* settings */
#define MIN_WALK_SPEED      10
#define MIN_RUN_SPEED       40

/* advanced settings */
#define ANIM_FRAME_DURATION 200
#define ANIM_SIZE           96

/* timers */
static uint32_t anim_timer = 0;

/* current frame */
static uint8_t current_frame = 0;

/* status variables */
static uint8_t current_wpm = 0;
static led_t  led_usb_state;

static bool isSneaking = false;
static bool isJumping  = false;
static bool showedJump = true;

/* logic */
void render_luna(int LUNA_X, int LUNA_Y) {
    /* Sit */
    static const char PROGMEM sit[2][ANIM_SIZE] = {
        // ...existing code...
    };

    /* Walk */
    static const char PROGMEM walk[2][ANIM_SIZE] = {
        // ...existing code...
    };

    /* Run */
    static const char PROGMEM run[2][ANIM_SIZE] = {
        // ...existing code...
    };

    /* Bark */
    static const char PROGMEM bark[2][ANIM_SIZE] = {
        // ...existing code...
    };

    /* Sneak */
    static const char PROGMEM sneak[2][ANIM_SIZE] = {
        // ...existing code...
    };

    /* animation */
    void animate_luna(void) {
        /* jump */
        if (isJumping || !showedJump) {
            /* clear */
            oled_set_cursor(LUNA_X, LUNA_Y + 2);
            oled_write("     ", false);

            oled_set_cursor(LUNA_X, LUNA_Y - 1);

            showedJump = true;
        } else {
            /* clear */
            oled_set_cursor(LUNA_X, LUNA_Y - 1);
            oled_write("     ", false);

            oled_set_cursor(LUNA_X, LUNA_Y);
        }

        /* switch frame */
        current_frame = (current_frame + 1) % 2;

        /* current status */
        if (led_usb_state.caps_lock) {
            oled_write_raw_P(bark[current_frame], ANIM_SIZE);
        } else if (isSneaking) {
            oled_write_raw_P(sneak[current_frame], ANIM_SIZE);
        } else if (current_wpm <= MIN_WALK_SPEED) {
            oled_write_raw_P(sit[current_frame], ANIM_SIZE);
        } else if (current_wpm <= MIN_RUN_SPEED) {
            oled_write_raw_P(walk[current_frame], ANIM_SIZE);
        } else {
            oled_write_raw_P(run[current_frame], ANIM_SIZE);
        }
    }

#    if OLED_TIMEOUT > 0
    if (last_input_activity_elapsed() > OLED_TIMEOUT && last_led_activity_elapsed() > OLED_TIMEOUT) {
        oled_off();
        return;
    } else {
        oled_on();
    }
#    endif

    if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
        anim_timer = timer_read32();
        animate_luna();
    }
}

void pet_update_state(uint8_t wpm, led_t led_state) {
    current_wpm   = wpm;
    led_usb_state = led_state;
}

bool pet_process_record(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case KC_LCTL:
    case KC_RCTL:
        isSneaking = record->event.pressed;
        break;
    case KC_SPC:
        if (record->event.pressed) {
            isJumping  = true;
            showedJump = false;
        } else {
            isJumping = false;
        }
        break;
    default:
        break;
    }
    return true;
}