#pragma once

// Prevent multiple definitions
#ifndef DMX_SERIAL_INPUT_PIN
#define DMX_SERIAL_INPUT_PIN GPIO_NUM_16
#endif

#ifndef DMX_SERIAL_OUTPUT_PIN
#define DMX_SERIAL_OUTPUT_PIN GPIO_NUM_17
#endif

#ifndef DMX_SERIAL_IO_PIN
#define DMX_SERIAL_IO_PIN GPIO_NUM_4
#endif

// Add missing UART definitions if not present
#ifndef UART_SIGNAL_TXD_INV
#define UART_SIGNAL_TXD_INV (0x1 << 0)
#endif