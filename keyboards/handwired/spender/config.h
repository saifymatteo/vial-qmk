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

// Audio Clicky | Keypress Sound
#define AUDIO_CLICKY
#define AUDIO_CLICKY_FREQ_RANDOMNESS 1.0f
