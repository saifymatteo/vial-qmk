/*
Copyright 2025 saifymatteo <dev@saifulmashuri.com>
*/

#pragma once

#include_next <mcuconf.h>

// SPI | Trackball
#undef RP_SPI_USE_SPI0
#define RP_SPI_USE_SPI0 TRUE

// PWM | Audio
#undef RP_PWM_USE_PWM0
#define RP_PWM_USE_PWM0 TRUE

// I2C | OLED
#undef RP_I2C_USE_I2C0
#define RP_I2C_USE_I2C0 TRUE
