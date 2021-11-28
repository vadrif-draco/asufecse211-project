#include "KeyPad.h"

static int8 assigned_input_port = 0;
static int8 assigned_output_port = 0;

void KeyPad_init(int8 input_port, int8 output_port) {

    assigned_input_port = input_port;
    assigned_output_port = output_port;

    for (int i = 0; i <= 3; ++i) // columns
        DIO_init_f(assigned_input_port, i, IN, PUR);

    for (int i = 4; i <= 7; ++i) // rows
        DIO_init_f(assigned_output_port, i, OUT, ODR);

    // - such that as long as the switches hardwired to them are pulled-up the board provides VCC to them
    // - otherwise once switch is pressed they get short-circuited to GND

}

uint8 KeyPad_read() {

    const uint8 KEYS[4][4] = { {'1', '2', '3', '+'},
                               {'4', '5', '6', '-'},
                               {'7', '8', '9', '/'},
                               {'*', '0', '#', '='} };

    // Ground all output pins
    for (int i = 4; i <= 7; ++i)
        write_pin(assigned_output_port, i, LOW);

    // If the output port is four ones, this means no key is down, return 0
    if ((read_port(assigned_input_port) & 0xF) == 0xF) return 0;

    // Otherwise, key was pressed, delay to debounce then re-check to make sure
    delay(16000);
    if ((read_port(assigned_input_port) & 0xF) == 0xF) return 0;

    for (int i = 0; i <= 3; ++i) {

        // Set all output pins back HIGH (HIGH + Open-Drain = Float)
        for (int j = 4; j <= 7; ++j)
            write_pin(assigned_output_port, j, HIGH);

        // Output pins are 4-7 inclusive, the iterator i is 0-3, so we need offset +4
        write_pin(assigned_output_port, i + 4, LOW); // Ground the i'th row represented by pin i + 4

        for (int j = 0; j <= 3; ++j) {

            // Check if any of its pins are shortcircuited to GND cause if so THAT IS THE ONE!!!!!
            if (read_pin(assigned_input_port, j) == 0) {

                // Then wait until key is released, then delay to debounce and return key
                while (!((read_port(assigned_input_port) & 0xF) == 0xF));
                delay(16000);
                return KEYS[i][j];

            }

        }

    }

    return 0;

}