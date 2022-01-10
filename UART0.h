#ifndef UART_H
#define UART_H

#define REGISTER_LEVEL_VERSION
#ifdef REGISTER_LEVEL_VERSION

#include "macros.h"
#include "tm4c123gh6pm.h"

#endif

#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_memmap.h"
#include "driverlib/uart.h"
#include "driverlib/sysctl.h"

void UART0_init(uint32_t baudrate);
void UART0_send_string(uint8_t*);
void UART0_send_char(uint8_t);
uint8_t UART0_receive_char();

#endif /* UART_H */
