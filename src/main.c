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
#include <avr/power.h>
#include <avr/wdt.h>
#include <stdnoreturn.h>

#include "app-i2c.h"
#include "app-io.h"
#include "app-led.h"
#include "app-uart.h"


static void noreturn main_loop(void) {
    for (;;) {
        // reset watchdog timer
        wdt_reset();

        // TODO: sleep when not handling interrupts
    }
}


int main(void) {
    // enable watchdog timer
    wdt_enable(WDTO_250MS);

    // disable all peripherals (drivers will enable the peripherals they use)
    power_all_disable();

    // initialise drivers
    app_io_module_init();
    app_led_module_init();
    app_uart_module_init();
    app_i2c_module_init();

    // enable interrupts
    sei();

    // enter main loop (never returns)
    main_loop();
}
