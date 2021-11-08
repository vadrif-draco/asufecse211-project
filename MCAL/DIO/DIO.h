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

void DIO_init(int8 port, int8 pin, int8 dir);
void write_pin(int8 port, int8 pin, int8 value);
void write_port(int8 port, uint32 value);

int8 read_pin(int8 port, int8 pin);
uint32 read_port(int8 port);

#endif // DIO_H