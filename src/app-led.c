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

#include "app-led.h"


volatile uint8_t priv_app_led_counter;


ISR(TIMER0_OVF_vect) {
    // decrement led counter until it reaches zero, then turn LED off
    if ( priv_app_led_counter > 0 ) {
        priv_app_led_counter--;
    } else {
        PORTB = 0;
    }
}


void app_led_module_init(void) {
    // enable TIMER0 clock
    power_timer0_enable();

    // initialise timer for ~61Hz overflow interrupt
    TIFR0 = (1 << TOV0);    // clear overflow interrupt flag
    TIMSK0 = (1 << TOIE0);  // enable overflow interrupt
    TCCR0B = (1 << CS02) | (1 << CS00); // start timer with /1024 prescaler
}
