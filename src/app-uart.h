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

#include <stdint.h>


/**
 * Initialises UART driver.
 */
void app_uart_module_init(void);


/**
 * Pushes a byte into driver's transmit FIFO.
 *
 * @param value     Byte value to push into fifo.
 */
inline static void app_uart_push(uint8_t value);


#ifndef _DOXYGEN

// ******** PRIVATE ********

#include <avr/io.h>

#include "app-led.h"


extern volatile uint8_t priv_app_uart_queue[256];
extern volatile uint8_t priv_app_uart_head;


inline static void app_uart_push(uint8_t value) {
    priv_app_uart_queue[priv_app_uart_head++] = value;
    UCSR0B = (1 << UDRIE0) | (1 << TXEN0);
    app_led_flash();
}

#endif // _DOXYGEN
