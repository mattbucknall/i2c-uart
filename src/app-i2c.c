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

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/power.h>

#include "app-config.h"
#include "app-i2c.h"
#include "app-uart.h"


ISR(TWI_vect) {
    uint8_t status = TWSR & 0xF8;

    // decode status and perform any actions necessary to satisfy TWI operation
    switch(status) {
    case 0x80:
    case 0x88:
    case 0x90:
    case 0x98:
        // a byte has arrived, so push it into UART's FIFO
        app_uart_push(TWDR);
        break;

    case 0xA8:
    case 0xB0:
    case 0xB8:
        // firmware does nothing with I2C reads at the moment, so just provide TWI with null data
        TWDR = 0x00;
        break;

    default:
        // do nothing for other status codes
        break;
    }

    // clear TWI interrupt flag
    TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN) | (1 << TWIE);
}


void app_i2c_module_init(void) {
    // enable TWI clock
    power_twi_enable();

    // configure TWI (target mode)
    TWAR = APP_CONFIG_DEVICE_ADDRESS;
    TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN) | (1 << TWIE); // ack enabled, twi enabled, twi interrupt enabled
}
