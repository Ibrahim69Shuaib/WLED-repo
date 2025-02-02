#pragma once

#include "driver/uart.h"

// Define missing UART signals if not present
#ifndef UART_SIGNAL_TXD_INV
#define UART_SIGNAL_TXD_INV (0x1 << 0)
#endif

#ifndef UART_SIGNAL_RXD_INV
#define UART_SIGNAL_RXD_INV (0x1 << 1)
#endif

#ifndef UART_SIGNAL_RTS_INV
#define UART_SIGNAL_RTS_INV (0x1 << 2)
#endif

#ifndef UART_SIGNAL_CTS_INV
#define UART_SIGNAL_CTS_INV (0x1 << 3)
#endif