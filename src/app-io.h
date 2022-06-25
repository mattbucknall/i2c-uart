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


// Port B pin assignments
#define APP_IO_B_LED                (1 << 5)
#define APP_IO_B_XTAL1              (1 << 6)
#define APP_IO_B_XTAL2              (1 << 7)

#define APP_IO_B_UNUSED             ((1 << 4) | (1 << 3) | (1 << 2) | (1 << 1) | (1 << 0))


// Port C pin assignments
#define APP_IO_C_SDA                (1 << 4)
#define APP_IO_C_SCL                (1 << 5)

#define APP_IO_C_UNUSED             ((1 << 6) | (1 << 3) | (1 << 2) | (1 << 1) | (1 << 0))


// Port D Pin Assignments
#define APP_IO_D_RXD                (1 << 0)
#define APP_IO_D_TXD                (1 << 1)

#define APP_IO_D_UNUSED             ((1 << 7) | (1 << 6) | (1 << 5) | (1 << 4) | (1 << 3) | (1 << 2))


/**
* Initialises GPIO pins.
*/
void app_io_module_init(void);
