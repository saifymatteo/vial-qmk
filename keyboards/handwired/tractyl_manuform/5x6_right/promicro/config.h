/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

//#undef USE_I2C
#define MASTER_RIGHT

/* PMW3360 Settings */
#define POINTING_DEVICE_CS_PIN B6

// For USB C Pro Micro
// #define SPLIT_USB_DETECT
// #define SPLIT_USB_TIMEOUT 2500
#define SPLIT_WATCHDOG_ENABLE

// Tapping Toggle feature TT(layer)
#define TAPPING_TOGGLE 3

// Trackball settings
#define CHARYBDIS_MINIMUM_DEFAULT_DPI 1000 // The minimum sensitivity in default mode.
// #define CHARYBDIS_DEFAULT_DPI_CONFIG_STEP 200 // Change of the sensitivity in cursor mode each time POINTER_DEFAULT_DPI_FORWARD/ REVERSE is pressed.
#define CHARYBDIS_MINIMUM_SNIPING_DPI 400 // The sensitivity in sniping mode.
// #define CHARYBDIS_SNIPING_DPI_CONFIG_STEP 200 // Change of the pointers sensitivity in sniping mode each time POINTER_SNIPING_DPI_FORWARD/ REVERSE is pressed.
#define CHARYBDIS_DRAGSCROLL_DPI 100 // The sensitivity in dragscroll mode.
// #define CHARYBDIS_DRAGSCROLL_REVERSE_X // Reverse the scroll direction in dragscroll mode for the x / y axis.
#define CHARYBDIS_DRAGSCROLL_REVERSE_Y // Reverse the scroll direction in dragscroll mode for the x / y axis.
// #define CHARYBDIS_CARRET_BUFFER 40 // The sensitivity in carret mode. Higher number means less sensitive.
// #define CHARYBDIS_CARRET_REVERSE_X / _Y // Reverse the direction in carret mode for the x / y axis.
// #define CHARYBDIS_POINTER_ACCELERATION_ENABLE // Enable pointer acceleration.
// #define CHARYBDIS_POINTER_ACCELERATION_FACTOR 24 // Amount of pointer acceleration.
// #define CUSTOM_FN_RIGHT / CUSTOM_FN_LEFT / _UP / _DOWN // Here you can define the keycode that gets executed in custom mode when the trackball is rotated to the right / left / up / down.
#define CHARYBDIS_CONFIG_SYNC // If you want/need to enable syncing of the charybdis config, such as to read the sniping or drag scroll modes on the other half (such as for displaying the status via rgb matrix, or added on screens, or what not), you can enabled this.
