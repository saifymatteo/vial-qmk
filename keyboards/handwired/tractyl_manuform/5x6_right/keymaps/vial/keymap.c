/*
 * Copyright 2025 saifymatteo <dev@saifulmashuri.com>
 */

#include QMK_KEYBOARD_H
#include "os_detection.h"

#if __has_include("keymap.h")
#    include "keymap.h"
#endif

// ---------------- INITIALISATION --------------------------------------------------------------

os_variant_t current_os = OS_UNSURE;

uint32_t cancel_haptic(uint32_t trigger_time, void *cb_arg) {
    gpio_write_pin_low(GP13);
    return 0;
}

uint32_t custom_os_settings(uint32_t trigger_time, void *cb_arg) {
    current_os        = detected_host_os();
    uint16_t retry_ms = 500;

    if (current_os != OS_UNSURE) {
        retry_ms = 0;
    }

    return retry_ms;
}

void keyboard_pre_init_user(void) {
    // Haptic motor PIN
    gpio_set_pin_output(GP13);
}

void keyboard_post_init_user(void) {
    // Enable console debug
    debug_enable = true;
    debug_matrix = true;

    // Register deferred callback for OS Detection
    defer_exec(1000, custom_os_settings, NULL);
}

// ---------------- LAYER --------------------------------------------------------------

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {[0] = LAYOUT_5x6_right(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_DEL, KC_TAB, KC_Q, KC_W, KC_F, KC_P, KC_B, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_BSLS, KC_BSPC, KC_A, KC_R, KC_S, KC_T, KC_G, KC_M, KC_N, KC_E, KC_I, KC_O, KC_QUOT, KC_APP, KC_Z, KC_X, KC_C, KC_D, KC_V, KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, DF(1), KC_LCTL, KC_LGUI, KC_HOME, KC_END, KC_LSFT, KC_SPC, KC_RSFT, KC_ENT, KC_LALT, KC_ENT, TT(2), TT(3), TT(3), TT(2)),
                                                              [1] = LAYOUT_5x6_right(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_TRNS, KC_TRNS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_TRNS, KC_TRNS, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, DF(0), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
                                                              [2] = LAYOUT_5x6_right(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, AU_TOGG, KC_PSCR, KC_INS, KC_SCRL, KC_PAUS, KC_NUM, KC_TRNS, KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_VOLU, KC_GRV, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_TRNS, KC_TRNS, KC_F5, KC_F6, KC_F7, KC_F8, KC_VOLD, KC_F20, KC_LEFT, KC_UP, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_F9, KC_F10, KC_F11, KC_F12, KC_MUTE, KC_TILD, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP, KC_PGDN, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
                                                              [3] = LAYOUT_5x6_right(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MS_BTN4, MS_BTN5, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, SNIPING_MODE, DRAGSCROLL_MODE, KC_TRNS, KC_TRNS, MS_BTN1, MS_BTN3, MS_BTN2, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)};

// ---------------- ENCODER --------------------------------------------------------------

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {

};
#endif // defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)

// ---------------- OLED --------------------------------------------------------------

// Keyboard Matrix. Taken from [github](https://github.com/vuon0029/qmk/tree/master/keyboards/mechwild/mercutio/keymaps/dracutio)

// WPM and row/column texts
char text_wpm[10];
char text_row_col[13];

// Keyboard Matrix display
#define MATRIX_DISPLAY_X 49
#define MATRIX_DISPLAY_Y 25

// Keyboard Unit size
#define GAP 2
#define CUBE_NUMBER 4

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_180; // flips the display 180 degrees
    }

    return rotation;
}

// Sync actions from master to slave
bool should_process_keypress(void) {
    return true;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        // Render Keyboard Box
        oled_set_cursor(0, 0);
        for (uint8_t x = 0; x < MATRIX_DISPLAY_X; x++) {
            oled_write_pixel(x, 0, true);
        }
        for (uint8_t y = 0; y < MATRIX_DISPLAY_Y; y++) {
            oled_write_pixel(0, y, true);
        }
        for (uint8_t x = 0; x < MATRIX_DISPLAY_X; x++) {
            oled_write_pixel(x, MATRIX_DISPLAY_Y, true);
        }
        for (uint8_t y = 0; y < MATRIX_DISPLAY_Y; y++) {
            oled_write_pixel(MATRIX_DISPLAY_X, y, true);
        }

        // Render WPM text
        oled_set_cursor(10, 0);
        sprintf(text_wpm, "WPM: %03d", get_current_wpm());
        oled_write_ln(text_wpm, false);

        // Render Layers
        oled_set_cursor(10, 2);
        switch (get_highest_layer(layer_state | default_layer_state)) {
            case 0:
                oled_write_ln("Colemak-DH", false);
                break;
            case 1:
                oled_write_ln("QWERTY", false);
                break;
            case 2:
                oled_write_ln("Functions", false);
                break;
            case 3:
                oled_write_ln("Trackball", false);
                break;
            default:
                oled_write_ln("Undefined", false);
        }
    } else {
        // Pure animation
    }

    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Haptic trigger, immediate vibrate with 350ms duration
    gpio_write_pin_high(GP13);
    defer_exec(350, cancel_haptic, NULL);

    if (is_keyboard_master()) {
        // Row and column swapped based on config
        // - Max row = 12
        // - Max column = 6
        uint8_t row    = record->event.key.row;
        uint8_t column = record->event.key.col;

        // Render Row and Column text
        sprintf(text_row_col, "R-C: %d-%d", row, column);
        oled_set_cursor(10, 1);
        oled_write_ln(text_row_col, false);

        // Render keyboard state
        led_t state = host_keyboard_led_state();
        oled_set_cursor(10, 3);
        if (state.caps_lock) {
            oled_write_ln("Caps Lock", false);
        } else if (state.num_lock) {
            oled_write_ln("Num Lock", false);
        } else if (state.scroll_lock) {
            oled_write_ln("Scroll Lck", false);
        } else if (state.compose) {
            oled_write_ln("Compose", false);
        } else if (state.kana) {
            oled_write_ln("Kana", false);
        } else {
            oled_advance_page(true);
        }

        // Render keyboard tap, switch back the row/column on master side
        bool is_master = row >= 6;
        row            = is_master ? row - 6 : row;
        column         = is_master ? column + 6 : column;
        for (uint8_t x = (CUBE_NUMBER * row) + GAP; x < CUBE_NUMBER * (row + 1); x++) {
            for (uint8_t y = (CUBE_NUMBER * column) + GAP; y < CUBE_NUMBER * (column + 1); y++) {
                oled_write_pixel(y, x, record->event.pressed);
            }
        }
    }

    switch (keycode) {
        case KC_F20:
            // When keycode is pressed
            if (record->event.pressed) {
                if (current_os == OS_WINDOWS || current_os == OS_LINUX) {
                    // Windows | Open Task View
                    register_code(KC_LGUI);
                    register_code(KC_TAB);
                } else if (current_os == OS_MACOS) {
                    // MacOS | Open Mission Control
                    register_code(0xc1);
                }
            }
            // Clear all modifiers and keys currently pressed
            clear_keyboard();
            return false;
    }
    return true;
};

// END OF FILE
