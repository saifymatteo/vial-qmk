/*
Copyright 2025 saifymatteo <dev@saifulmashuri.com>
*/

#pragma once

// For OS Detection | helps with detection issue with KVM device
#define OS_DETECTION_KEYBOARD_RESET

// Tapping Toggle feature TT(layer)
#define TAPPING_TOGGLE 3

// Audio features
#define AUDIO_PIN B6 // Pin for audio output
#define AUDIO_DAC_SAMPLE_MAX 4095U

// Audio Song
#define STARTUP_SONG SONG(USSR_ANTHEM)

// Audio Clicky | Keypress Sound
#define AUDIO_CLICKY
#define AUDIO_CLICKY_FREQ_RANDOMNESS 1.0f

// I2C configuration (for OLED)
#define I2C1_SCL_PIN D0
#define I2C1_SDA_PIN D1

// OLED configuration
#define OLED_BRIGHTNESS 255 // from 0 to 255
#define OLED_DISPLAY_WIDTH 128
#define OLED_DISPLAY_HEIGHT 32

// Encoders
#define ENCODER_A_PINS {E7}
#define ENCODER_B_PINS {E6}
#define ENCODER_RESOLUTION 4

// Deferred Callbacks
#define MAX_DEFERRED_EXECUTORS 16

