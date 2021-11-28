// Include Guard
#ifndef DIO_H
#define DIO_H

#include "../../tm4c123gh6pm.h"
#include "../../macros.h"
#include "../../types.h"
#include <stdint.h>

#define PORTA   0
#define PORTB   1
#define PORTC   2
#define PORTD   3
#define PORTE   4
#define PORTF   5
#define IN      1
#define OUT     0
#define LOW     0
#define HIGH    1
#define PULOW   1 // Pull-up low
#define PUHIGH  0 // Pull-up high
#define ODR     0x50C // Register 14: GPIO Open Drain Select (GPIOODR), offset 0x50C
#define PUR     0x510 // Register 15: GPIO Pull-Up Select (GPIOPUR), offset 0x510
#define PDR     0x514 // Register 16: GPIO Pull-Down Select (GPIOPDR), offset 0x514

void DIO_init(int8 port, int8 pin, int8 dir);
void DIO_init_f(int8 port, int8 pin, int8 dir, uint16 flag);
void write_pin(int8 port, int8 pin, int8 value);
void write_port(int8 port, uint32 value);

int8 read_pin(int8 port, int8 pin);
uint32 read_port(int8 port);

#endif // DIO_H