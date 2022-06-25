# i2c-uart
Simple Arduino Nano based I2C-to-UART adapter.

## Why?
I needed a way to output debugging messages from a microcontroller that did not have any spare UART interfaces
available. I created this firmware so that I could hook am Arduino Nano into my target's I2C bus and use it to send
messages from the target's microcontroller to a terminal on a PC via the Nano's UART-over-USB interface.

## Connection

The Nano is connected to the target via the following pins:

- Pin 23/A4 (SDA)
- Pin 24/A5 (SCL)
- Pin 4 or 29 (GND)

## UART Interface

This firmware operates the Nano's UART at 76800 baud with an 8-bit word width, no parity and 1 stop bit. The baud rate
can be changed by modifying `APP_CONFIG_BAUD_RATE` in app-config.h 

## I2C Interface

The Nano's I2C interface operates in target mode<sup>1</sup> up to 400kHz and responds to the 7-bit address `1100011`
(this can be changed by modifying `APP_CONFIG_DEVICE_ADDRESS` in app-config.h). All bytes received on the I2C interface,
after the device address, are pushed into a 256 byte FIFO and then transmitted by the Nano's UART.

## Limitations

- No flow control implemented - If the FIFO overflows then data will be dropped.
- Communication is currently only one-way (I2C to UART).

## Compiling/Programming
The build scripts for this project are set up to compile the source code using avr-gcc + AVR Libc (only tested on Linux)
and to program the Nano using an AVR ISP MkII programming adapter via avrdude. The toolchain is assumed to be installed
under `/usr` (e.g. `/usr/bin/avr-gcc`). The following custom build targets are defined:

| Target          |Description|
|-----------------|-----------|
| `program`       |Programs the Nano's flash memory.|
| `program_fuses` |Sets the Nano's fuse bits.|
|`reset`|Resets the Nano.|
|`erase`|Erases the Nano's flash memory.|

## License

Copyright (C) 2022 Matthew T. Bucknall

Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF
THIS SOFTWARE.

<br/>
<sup>1. https://community.nxp.com/t5/Other-NXP-Products/Alternative-inclusive-terms-for-master-and-slave-in-I2S-I2C/td-p/1244999</sup>
