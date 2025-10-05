/*
 * Copyright 2025 saifymatteo <dev@saifulmashuri.com>
 */

#include QMK_KEYBOARD_H
#include "os_detection.h"

#if __has_include("keymap.h")
#    include "keymap.h"
#endif

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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Haptic trigger, immediate vibrate with 350ms duration
    gpio_write_pin_high(GP13);
    defer_exec(350, cancel_haptic, NULL);

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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {[0] = LAYOUT_5x6_right(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_DEL, KC_TAB, KC_Q, KC_W, KC_F, KC_P, KC_B, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_BSLS, KC_BSPC, KC_A, KC_R, KC_S, KC_T, KC_G, KC_M, KC_N, KC_E, KC_I, KC_O, KC_QUOT, KC_APP, KC_Z, KC_X, KC_C, KC_D, KC_V, KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, DF(1), KC_LCTL, KC_LGUI, KC_HOME, KC_END, KC_LSFT, KC_SPC, KC_RSFT, KC_ENT, KC_LALT, KC_ENT, TT(2), TT(3), TT(3), TT(2)),
                                                              [1] = LAYOUT_5x6_right(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_TRNS, KC_TRNS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_TRNS, KC_TRNS, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, DF(0), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
                                                              [2] = LAYOUT_5x6_right(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, AU_TOGG, KC_PSCR, KC_INS, KC_SCRL, KC_PAUS, KC_NUM, KC_TRNS, KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_VOLU, KC_GRV, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_TRNS, KC_TRNS, KC_F5, KC_F6, KC_F7, KC_F8, KC_VOLD, KC_F20, KC_LEFT, KC_UP, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_F9, KC_F10, KC_F11, KC_F12, KC_MUTE, KC_TILD, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP, KC_PGDN, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
                                                              [3] = LAYOUT_5x6_right(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MS_BTN4, MS_BTN5, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, SNIPING_MODE, DRAGSCROLL_MODE, KC_TRNS, KC_TRNS, MS_BTN1, MS_BTN3, MS_BTN2, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)};

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {

};
#endif // defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)

// END OF FILE
