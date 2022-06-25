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
#include "app-uart.h"


volatile uint8_t priv_app_uart_queue[256];
volatile uint8_t priv_app_uart_head;

static volatile uint8_t m_tail;


ISR(USART_UDRE_vect) {
    UDR0 = priv_app_uart_queue[m_tail++];

    if ( m_tail == priv_app_uart_head ) {
        UCSR0B = (1 << TXEN0);
    }
}


void app_uart_module_init(void) {
    // enable USART0 clock
    power_usart0_enable();

    // configure USART0
    UBRR0 = (TARGET_XTAL_FREQ / (8 * APP_CONFIG_BAUD_RATE)) - 1;
    UCSR0A = (1 << U2X0); // double speed
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8-bit, no parity, 1 stop bit
    UCSR0B = (1 << TXEN0); // transmitter enabled
}
