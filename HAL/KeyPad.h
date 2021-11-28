#ifndef KEYPAD_H
#define KEYPAD_H

#include "../MCAL/DIO/DIO.h"

void KeyPad_init(int8 input_port, int8 output_port);
uint8 KeyPad_read();

#endif /* KEYPAD_H */
