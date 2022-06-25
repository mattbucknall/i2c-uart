/*
 * i2c-uart
 *
 * Simple transmit-only I2C-to-UART adapter based on CH340 Arduino Nano clone.
 *
 * https://github.com/mattbucknall/i2c-uart
 *
 * Copyright (C) 2022 Matthew T. Bucknall
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR
 * IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#pragma once


/**
 * Initialises LED driver.
 */
void app_led_module_init(void);


/**
 * Momentarily illuminates LED.
 */
inline static void app_led_flash();


#ifndef _DOXYGEN

// ******** PRIVATE ********

#include <avr/io.h>

#include <stdint.h>

#include "app-io.h"


extern volatile uint8_t priv_app_led_counter;


inline static void app_led_flash() {
    // set led counter (decremented in TIMER0 overflow ISR)
    priv_app_led_counter = 4;

    // turn LED on
    PORTB = APP_IO_B_LED;
}

#endif // _DOXYGEN
