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
    // debug_matrix = true;
    // debug_keyboard = true;
    // debug_mouse = true;

    // Register deferred callback for OS Detection
    defer_exec(1000, custom_os_settings, NULL);
}

// Sync actions from master to slave
bool should_process_keypress(void) {
    return true;
}

// ---------------- LAYER --------------------------------------------------------------

enum custom_keycodes {
    ALT_GUI = SAFE_RANGE,
    ZOOM,
};

KEYCODE_STRING_NAMES_USER(KEYCODE_STRING_NAME(ALT_GUI), KEYCODE_STRING_NAME(ZOOM), KEYCODE_STRING_NAME(KC_APP), );

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {[0] = LAYOUT_5x6_right(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_DEL, KC_TAB, KC_Q, KC_W, KC_F, KC_P, KC_B, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_BSLS, KC_BSPC, LSFT_T(KC_A), LALT_T(KC_R), LGUI_T(KC_S), LCTL_T(KC_T), KC_G, KC_M, RCTL_T(KC_N), RGUI_T(KC_E), RALT_T(KC_I), RSFT_T(KC_O), KC_QUOT, KC_APP, KC_Z, KC_X, KC_C, KC_D, KC_V, KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, DF(1), ALT_GUI, KC_LCTL, KC_LGUI, KC_HOME, KC_END, ZOOM, KC_LSFT, KC_SPC, KC_RSFT, KC_ENT, KC_LALT, KC_ENT, TT(2), TT(3), TT(3), TT(2)),
                                                              [1] = LAYOUT_5x6_right(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_TRNS, KC_TRNS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_TRNS, KC_TRNS, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, DF(0), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
                                                              [2] = LAYOUT_5x6_right(QK_REBOOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR, KC_INS, KC_SCRL, KC_PAUS, KC_NUM, QK_BOOTLOADER, KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_TRNS, KC_GRV, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_TRNS, KC_TRNS, KC_F5, KC_F6, KC_F7, KC_F8, KC_TRNS, ALT_GUI, KC_LEFT, KC_UP, KC_DOWN, KC_RGHT, KC_TRNS, EE_CLR, KC_F9, KC_F10, KC_F11, KC_F12, AU_TOGG, KC_TILD, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, DB_TOGG, KC_MUTE, KC_TRNS, KC_TRNS, KC_PGUP, KC_PGDN, KC_MEDIA_PLAY_PAUSE, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
                                                              [3] = LAYOUT_5x6_right(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MS_BTN4, MS_BTN5, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, SNIPING_MODE, DRAGSCROLL_MODE, KC_TRNS, KC_TRNS, MS_BTN1, MS_BTN3, MS_BTN2, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LCTL(KC_A), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, QK_BOOTLOADER, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)};

// ---------------- ENCODER --------------------------------------------------------------

// Alt (Windows) / Command (MacOS)
// Taken from [reddit](https://www.reddit.com/r/MechanicalKeyboards/comments/s52e51/added_alttab_to_my_rotary_encoder_on_my_qmk_board/)
bool     is_alt_tab_active       = false;
bool     is_alt_shift_tab_active = false;
uint16_t alt_tab_timer           = 0;

// Note: current keyboard and RP2040 does not support ENCODER_MAP_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    bool is_master_right = index == 1; // Master (right) encoder
    bool is_slave_left   = index == 0; // Slave (left) encoder

    if (is_slave_left) {
        if (clockwise) {
            print("Slave encoder: clockwise\n");
        } else {
            print("Slave encoder: counter clockwise\n");
        }
    } else if (is_master_right) {
        if (clockwise) {
            print("Master encoder: clockwise\n");
        } else {
            print("Master encoder: counter clockwise\n");
        }
    }

    switch (get_highest_layer(layer_state | default_layer_state)) {
        case 0:
            // Alt tab / shift alt tab || OS zoom in / out
            if (is_slave_left) {
                // Windows: Alt tab (need to hold alt)
                // MacOS: Command tab (need to hold command)
                register_code(current_os == OS_MACOS ? KC_LEFT_CTRL : KC_LALT);
                if (clockwise) {
                    if (!is_alt_tab_active) {
                        is_alt_tab_active = true;
                    }
                    alt_tab_timer = timer_read();
                    tap_code(KC_TAB);
                } else {
                    if (!is_alt_shift_tab_active) {
                        is_alt_shift_tab_active = true;
                    }
                    alt_tab_timer = timer_read();
                    tap_code16(LSFT(KC_TAB));
                }
            } else if (is_master_right) {
                // Windows: Magnifier - Windows plus/minus sign
                // MacOS: Zoom - Option (Alt) Command plus/minus sign | Need to enable "Use keyboard shortcuts to zoom"
                // Linux: Zoom (Gnome) - Super Alt plus/minus sign
                if (clockwise) {
                    if (current_os == OS_WINDOWS) {
                        tap_code16(LGUI(KC_KP_PLUS));
                    } else if (current_os == OS_LINUX) {
                        tap_code16(LAG(KC_KP_PLUS));
                    } else if (current_os == OS_MACOS) {
                        tap_code16(LCA(KC_KP_PLUS));
                    }
                } else {
                    if (current_os == OS_WINDOWS) {
                        tap_code16(LGUI(KC_KP_MINUS));
                    } else if (current_os == OS_LINUX) {
                        tap_code16(LAG(KC_KP_MINUS));
                    } else if (current_os == OS_MACOS) {
                        tap_code16(LCA(KC_KP_MINUS));
                    }
                }
            }
            break;
        case 1:
            // Alt tab / shift alt tab || OS zoom in / out
            if (is_slave_left) {
                // Windows: Alt tab (need to hold alt)
                // MacOS: Command tab (need to hold command)
                register_code(current_os == OS_MACOS ? KC_LEFT_CTRL : KC_LALT);
                if (clockwise) {
                    if (!is_alt_tab_active) {
                        is_alt_tab_active = true;
                    }
                    alt_tab_timer = timer_read();
                    tap_code(KC_TAB);
                } else {
                    if (!is_alt_shift_tab_active) {
                        is_alt_shift_tab_active = true;
                    }
                    alt_tab_timer = timer_read();
                    tap_code16(LSFT(KC_TAB));
                }
            } else if (is_master_right) {
                // Windows: Magnifier - Windows plus/minus sign
                // MacOS: Zoom - Option (Alt) Command plus/minus sign | Need to enable "Use keyboard shortcuts to zoom"
                // Linux: Zoom (Gnome) - Super Alt plus/minus sign
                if (clockwise) {
                    if (current_os == OS_WINDOWS) {
                        tap_code16(LGUI(KC_KP_PLUS));
                    } else if (current_os == OS_LINUX) {
                        tap_code16(LAG(KC_KP_PLUS));
                    } else if (current_os == OS_MACOS) {
                        tap_code16(LCA(KC_KP_PLUS));
                    }
                } else {
                    if (current_os == OS_WINDOWS) {
                        tap_code16(LGUI(KC_KP_MINUS));
                    } else if (current_os == OS_LINUX) {
                        tap_code16(LAG(KC_KP_MINUS));
                    } else if (current_os == OS_MACOS) {
                        tap_code16(LCA(KC_KP_MINUS));
                    }
                }
            }
            break;
        case 2:
            // Volume up / down || Media Previous / Media Next
            if (is_slave_left) {
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
            } else if (is_master_right) {
                if (clockwise) {
                    tap_code(KC_MEDIA_NEXT_TRACK);
                } else {
                    tap_code(KC_MEDIA_PREV_TRACK);
                }
            }
            break;
        case 3:
            // Move cursor one word left / right || Page up / page down
            if (is_slave_left) {
                if (clockwise) {
                    tap_code16(current_os == OS_MACOS ? LALT(KC_RIGHT) : LCTL(KC_RIGHT));
                } else {
                    tap_code16(current_os == OS_MACOS ? LALT(KC_LEFT) : LCTL(KC_LEFT));
                }
            } else if (is_master_right) {
                if (clockwise) {
                    tap_code(KC_PAGE_UP);
                } else {
                    tap_code(KC_PAGE_DOWN);
                }
            }
            break;
    }

    return false;
}

// ---------------- OLED --------------------------------------------------------------

// Keyboard Matrix. Taken from [github](https://github.com/vuon0029/qmk/tree/master/keyboards/mechwild/mercutio/keymaps/dracutio)
// Bongo cat OLED. Taken from [github](https://github.com/nwii/oledbongocat)

// Custom animation guide:
// 1. Get a any video or gif
// 2. To convert video to gif, use this: `ffmpeg -i <video-file> -vf "fps=10" -loop 0 <gif-output>`
// 3. Convert from Gif. [github](https://github.com/AskMeAboutBirds/qmk-oled-animation-compressor)

// WPM and row/column texts
char text_wpm[10];
char text_row_col[13];

// Keyboard Matrix display
#define MATRIX_DISPLAY_X 36
#define MATRIX_DISPLAY_Y 18

// Keyboard Unit size
#define GAP 1
#define CUBE_NUMBER 3

// Bongo cat
#define TAP_FRAMES 2
#define ANIMATION_FRAME_DURATION 200 // how long each frame lasts in ms
#define ANIMATION_SIZE 1024          // number of bytes in array, minimize for adequate firmware size, max is 1024

// Bongo cat variables
uint32_t animation_timer   = 0;
uint8_t  current_tap_frame = 0;

// Bongo cat animations
static const char PROGMEM bongo_tap[TAP_FRAMES][ANIMATION_SIZE] = {
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x40, 0x40, 0x20, 0x20, 0x10, 0x08, 0x04, 0x02, 0x04, 0x08, 0x10, 0x10, 0x20, 0x20, 0x40, 0x40, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xc1, 0x01, 0x01, 0x02, 0x02, 0x04, 0x04, 0x04, 0x04, 0x02, 0x02, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x40, 0x80, 0x80, 0x40, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x64, 0x18, 0x04, 0x12, 0xc2, 0xca, 0x24, 0x88, 0xf0, 0x80, 0x80, 0x40, 0x40, 0x40, 0x40, 0x20, 0x20, 0x20, 0x20, 0x10, 0x10, 0x10, 0x10, 0x08, 0x08, 0x08, 0x08, 0x04, 0x04, 0x04, 0x04, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x18, 0x06, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x83, 0x83, 0x40, 0x40, 0x40, 0x40, 0x20, 0x21, 0x21, 0x20, 0x10, 0x10, 0x10, 0x10, 0x08, 0x08, 0x08, 0x08, 0x04, 0x04, 0x04, 0x04, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x40, 0x40, 0x40, 0x40, 0x20, 0x20, 0x20, 0x20, 0x10, 0x10, 0x10, 0x10, 0x08, 0x0f, 0x08, 0x08, 0x04, 0x04, 0x04, 0x04, 0x02, 0x04, 0x08, 0x10, 0x10, 0x20, 0x20, 0x40, 0x40, 0x41, 0x42, 0x24, 0x98, 0xc0, 0x88, 0x88, 0x8c, 0x9c, 0x1c, 0x1e, 0x0e, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x40, 0x40, 0x20, 0x20, 0x10, 0x08, 0x04, 0x02, 0x04, 0x08, 0x10, 0x10, 0x20, 0x20, 0x40, 0x40, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xc1, 0x01, 0x01, 0x02, 0x02, 0x04, 0x84, 0x44, 0x44, 0x42, 0x82, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x40, 0x80, 0x80, 0x40, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x04, 0x08, 0x08, 0x10, 0x20, 0x40, 0x80, 0x80, 0x80, 0x80, 0x40, 0x40, 0x40, 0x40, 0x20, 0x20, 0x20, 0x20, 0x10, 0x10, 0x10, 0x10, 0x08, 0x08, 0x08, 0x08, 0x04, 0x04, 0x04, 0x04, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x18, 0x06, 0x01, 0x00, 0x00, 0x0c, 0x03, 0x00, 0x02, 0x18, 0x19, 0x00, 0x05, 0xfe, 0x80, 0x83, 0x83, 0x40, 0x40, 0x40, 0x40, 0x20, 0x21, 0x21, 0x20, 0x10, 0x10, 0x10, 0x10, 0x08, 0x08, 0x08, 0x08, 0x04, 0x04, 0x04, 0x04, 0x04, 0x08, 0x30, 0x40, 0x80, 0x80, 0x00, 0x00, 0x01, 0x86, 0x98, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x40, 0x40, 0x40, 0x40, 0x20, 0x20, 0x20, 0x20, 0x10, 0x10, 0x10, 0x10, 0x08, 0x0f, 0x08, 0x08, 0x04, 0x04, 0x04, 0x04, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x0f, 0x0f, 0x07, 0x03, 0x03, 0x61, 0xf0, 0xf8, 0xfc, 0x60, 0x01, 0x01, 0x01, 0x3c, 0x78, 0xf8, 0xf0, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
};

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_180; // flips the display 180 degrees
    }

    return rotation;
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
        oled_set_cursor(8, 0);
        sprintf(text_wpm, "WPM: %03d", get_current_wpm());
        oled_write_ln(text_wpm, false);

        // Render OS
        oled_set_cursor(8, 1);
        switch (current_os) {
            case OS_LINUX:
                oled_write_ln("OS : Linux", false);
                break;
            case OS_WINDOWS:
                oled_write_ln("OS : Windows", false);
                break;
            case OS_MACOS:
                oled_write_ln("OS : MacOS", false);
                break;
            case OS_IOS:
                oled_write_ln("OS : iOS", false);
                break;
            case OS_UNSURE:
                oled_write_ln("OS : Unsure", false);
                break;
        }

        // Render Layers
        oled_set_cursor(8, 2);
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
        // Render bongo cat
        if (timer_elapsed32(animation_timer) > ANIMATION_FRAME_DURATION) {
            animation_timer = timer_read32();

            current_tap_frame = (current_tap_frame + 1) % TAP_FRAMES;
            oled_write_raw_P(bongo_tap[abs((TAP_FRAMES - 1) - current_tap_frame)], ANIMATION_SIZE);
        }
    }

    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Debug keycodes
    printf("Key: %s\n", get_keycode_string(keycode));
    switch (current_os) {
        case OS_LINUX:
            printf("OS: Linux\n");
            break;
        case OS_WINDOWS:
            printf("OS: Windows\n");
            break;
        case OS_MACOS:
            printf("OS: MacOS\n");
            break;
        case OS_IOS:
            printf("OS: iOS\n");
            break;
        case OS_UNSURE:
            printf("OS: Unsure\n");
            break;
    }

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
        sprintf(text_row_col, "R%02d-C%d", row, column);
        oled_set_cursor(0, 3);
        oled_write_ln(text_row_col, false);

        // Render current key name
        oled_set_cursor(8, 3);
        oled_write_ln(get_keycode_string(keycode), false);

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
        case ALT_GUI:
            if (record->event.pressed) {
                if (current_os == OS_WINDOWS || current_os == OS_LINUX) {
                    // Windows | Open Task View
                    tap_code16(LGUI(KC_TAB));
                } else if (current_os == OS_MACOS) {
                    // MacOS | Open Mission Control
                    tap_code(KC_MISSION_CONTROL);
                }
            }
            break;
        case ZOOM:
            if (record->event.pressed) {
                if (current_os == OS_WINDOWS) {
                    // Windows | Cancel Magnifier
                    tap_code16(LGUI(KC_ESC));
                } else if (current_os == OS_LINUX) {
                    // Linux | Toggle Zoom (Gnome)
                    tap_code16(LAG(KC_8));
                } else if (current_os == OS_MACOS) {
                    // MacOS | Toggle Zoom
                    tap_code16(LCA(KC_8));
                }
            }
    }
    return true;
};

void matrix_scan_user(void) {
    // ALT key hold timer
    if (is_alt_tab_active | is_alt_shift_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 500) {
            unregister_code(current_os == OS_MACOS ? KC_LEFT_CTRL : KC_LALT);
            is_alt_tab_active       = false;
            is_alt_shift_tab_active = false;
        }
    }
};

// END OF FILE
