/*
Copyright 2025 saifymatteo <dev@saifulmashuri.com>
*/

#pragma once

#include_next <mcuconf.h>

// Set up SPI
#undef RP_SPI_USE_SPI0
#define RP_SPI_USE_SPI0 TRUE

#undef RP_PWM_USE_PWM0
#define RP_PWM_USE_PWM0 TRUE
