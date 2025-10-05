/*
Copyright 2025 saifymatteo <dev@saifulmashuri.com>
*/

#pragma once

// PWM | Audio
#undef HAL_USE_PWM
#define HAL_USE_PWM TRUE

// SPI | Trackball
#define HAL_USE_SPI TRUE

// I2C | OLED
#define HAL_USE_I2C TRUE

#include_next <halconf.h>
