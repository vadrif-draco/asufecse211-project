#ifndef UART_H
#define UART_H

#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_memmap.h"
#include "driverlib/uart.h"
#include "driverlib/sysctl.h"

// There are two implementations in this project for UART0, RTL/TivaWare
// To pick either, define or undefine the following #define
// It configures its required includes and .c file accordingly
// All functions in this header file are implemented to provide the same functionality in both versions
//
// #define REGISTER_LEVEL_VERSION
#ifdef REGISTER_LEVEL_VERSION

#include "macros.h"
#include "tm4c123gh6pm.h"

#else

#include "driverlib/gpio.h"

#endif

// Initialization function
// Covers the full initialization of UART0 port and pins of concern
// Enables UART0 implicitly, uses GPIO pins A0 and A1 for Rx and Tx
// Sets up UART0 to use the provided baudrate value
//
void UART0_init(uint32_t baudrate);

// Blocking UART0 Rx command to receive one character
//
uint8_t UART0_receive_char();

// Blocking UART0 Tx command to send one character
//
void UART0_send_char(uint8_t);

// Blocking UART0 Tx command to send a string, character-by-character
void UART0_send_string(uint8_t*);

#endif /* UART_H */
