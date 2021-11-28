#include "MCAL/DIO/DIO.h" // Header file containing the DIO abstraction layer functions and definitions
#include "HAL/KeyPad.h" // Header file containg
#include "HAL/LCD.h"
#include "queue.h"
#include <stdio.h> // TODO: Remove when you buy an LCD

void lab3B_task2();
void lab3R_task1();
void lab4A_task1();
void lab4A_task2();
void lab4R_task1();
void lab4R_task2();
void lab5B_task1();
void lab5B_task2();

void main() {

    // lab3B_task2();
    // lab3R_task1();
    // lab4A_task1();
    // lab4A_task2();
    // lab4R_task1();
    // lab4R_task2();
    // lab5B_task1();
    lab5B_task2();

}

void lab5B_task2() {

    KeyPad_init(PORTE, PORTC);
    LCD_init(); // boom
    QueuePtr queue = create_empty_queue();

    while (1) {

        uint8 key = 0;

        // Keep trying to read until you receive an '='
        while (key != '=') {

            key = KeyPad_read();

            if (key != 0) {

                LCD_data(key);
                enqueue(queue, key);

            }

        }

        // ACTUAL ARITHMETIC LOGIC

        uint32 operand1 = 0;
        uint8 operator = '0';
        uint32 operand2 = 0;

        while (!(is_empty(queue))) {

            key = front(queue);
            if (!(key >= '0' && key <= '9')) break;

            operand1 *= 10;
            operand1 += (uint32) (key - '0');
            dequeue(queue);

        }

        operator = front(queue);
        dequeue(queue);

        while (!(is_empty(queue))) {

            key = front(queue);
            if (!(key >= '0' && key <= '9')) break;

            operand2 *= 10;
            operand2 += (uint32) (key - '0');
            dequeue(queue);

        }

        uint32 result = 0;

        switch (operator) {

            case '+':
                result = operand1 + operand2;
                break;

            case '-':
                result = operand1 - operand2;
                break;

            case '/':
                if (operand2) result = operand1 / operand2;
                break;

            case '*':
                result = operand1 * operand2;
                break;

        }

        printf("%d\n\nExpression evaluated.\nTry another!\n\n", result);
        clear_queue(queue);

    }

}

void lab5B_task1() {

    KeyPad_init(PORTE, PORTC);
    LCD_init(); // boom
    while (1) LCD_data(KeyPad_read());

}

// TODO: Need to look into the functions below for anything that needs to be PUR

void lab4R_task2() {

    uint8 led_state = 0; // 0 = all, 1 = R, 2 = G, 3 = B
    uint8 switch0_held = 0;
    uint8 switch4_held = 0;

    while (1) {

        // If PORTF pin0/4 (aka switch1/2) is off (pull-up mode)...
        if (read_pin(PORTF, 0) == PULOW) {

            delay(80000); // Delay to soft-debounce then re-check; if still off, remove "held" state
            if (read_pin(PORTF, 0) == PULOW) switch0_held = 0;

        }

        if (read_pin(PORTF, 4) == PULOW) {

            delay(80000);
            if (read_pin(PORTF, 0) == PULOW) switch4_held = 0;

        }

        // If PORTF pin0/4 (aka switch1/2) is on (pull-up mode) for the first time (i.e., not currently held)
        // Perform the soft-debounce check, set their "held" state, then toggle their respective LED (red, blue)
        if (read_pin(PORTF, 0) == PUHIGH && !switch0_held) {

            delay(80000);
            if (read_pin(PORTF, 0) == PUHIGH && !switch0_held) {

                switch0_held = 1;
                led_state = (led_state + 1) % 4;

            }

        }

        if (read_pin(PORTF, 4) == PUHIGH && !switch4_held) {

            delay(80000);
            if (read_pin(PORTF, 4) == PUHIGH && !switch4_held) {

                switch4_held = 1;
                led_state = (led_state + 4 - 1) % 4;

            }

        }

        if (switch0_held && switch4_held) led_state = 0;

        // In addition, according to led_state, decide which LED(s) to turn on
        switch (led_state) {

            case 0: write_port(PORTF, 0xE); break;
            case 1: write_port(PORTF, 0x2); break;
            case 2: write_port(PORTF, 0x8); break;
            case 3: write_port(PORTF, 0x4); break;
            default: break;

        }

    }

}

void lab4R_task1() {

#define SIZE 10

    int arr[SIZE];
    for (int i = 0; i < SIZE; ++i) arr[i] = i;

    uint8 a_switch_is_held = 0;

    while (1) {

        // Iterate over all integers
        for (int i = 0; i < SIZE; ++i) {

            // Hold while a switch is held
            while (a_switch_is_held) {

                // Once both switches are released
                if (read_pin(PORTF, 0) == PULOW && read_pin(PORTF, 4) == PULOW) {

                    delay(80000); // Delay to debounce then reset the held state
                    if (read_pin(PORTF, 0) == PULOW && read_pin(PORTF, 4) == PULOW) a_switch_is_held = 0;

                }

            }

            write_port(PORTF, 0); // Reset LEDs after releasing all pressed switches

            // Hold while no switch is held
            while (!a_switch_is_held) {

                // Once a switch is pressed
                if (read_pin(PORTF, 0) == PUHIGH || read_pin(PORTF, 4) == PUHIGH) {

                    delay(80000); // Delay to debounce
                    if (read_pin(PORTF, 0) == PUHIGH || read_pin(PORTF, 4) == PUHIGH) {

                        // Then write to the appropriate LED in PORTF based on the rightmost bit, set the held state, then break out
                        write_port(PORTF, (arr[i] & 1) ? 0x2 : 0x4);
                        a_switch_is_held = 1;
                        break;

                    }

                }

            }

        }

    }

}

void lab4A_task2() {

    uint8 led_state = 0; // 0 = all, 1 = R, 2 = G, 3 = B
    uint8 switch0_held = 0;
    uint8 switch4_held = 0;

    while (1) {

        // If PORTF pin0/4 (aka switch1/2) is off (pull-up mode)...
        if (read_pin(PORTF, 0) == PULOW) {

            delay(80000); // Delay to soft-debounce then re-check; if still off, remove "held" state
            if (read_pin(PORTF, 0) == PULOW) switch0_held = 0;

        }

        if (read_pin(PORTF, 4) == PULOW) {

            delay(80000);
            if (read_pin(PORTF, 0) == PULOW) switch4_held = 0;

        }

        // If PORTF pin0/4 (aka switch1/2) is on (pull-up mode) for the first time (i.e., not currently held)
        // Perform the soft-debounce check, set their "held" state, then toggle their respective LED (red, blue)
        if (read_pin(PORTF, 0) == PUHIGH && !switch0_held) {

            delay(80000);
            if (read_pin(PORTF, 0) == PUHIGH && !switch0_held) {

                switch0_held = 1;
                led_state = (led_state + 1) % 4;

            }

        }

        if (read_pin(PORTF, 4) == PUHIGH && !switch4_held) {

            delay(80000);
            if (read_pin(PORTF, 4) == PUHIGH && !switch4_held) {

                switch4_held = 1;
                led_state = (led_state + 4 - 1) % 4;

            }

        }

        // In addition, according to led_state, decide which LED(s) to turn on
        switch (led_state) {

            case 0: write_port(PORTF, 0xE); break;
            case 1: write_port(PORTF, 0x2); break;
            case 2: write_port(PORTF, 0x8); break;
            case 3: write_port(PORTF, 0x4); break;
            default: break;

        }

    }

}

void lab4A_task1() {

    int8 switch0_held = 0;
    int8 switch4_held = 0;

    while (1) {

        // If PORTF pin0/4 (aka switch1/2) is off (pull-up mode)...
        if (read_pin(PORTF, 0) == PULOW) {

            delay(80000); // Delay to soft-debounce then re-check; if still off, remove "held" state
            if (read_pin(PORTF, 0) == PULOW) switch0_held = 0;

        }

        if (read_pin(PORTF, 4) == PULOW) {

            delay(80000);
            if (read_pin(PORTF, 0) == PULOW) switch4_held = 0;

        }

        // Write on PORTF pin3 (green LED) HIGH if both switches are held, otherwise LOW
        write_pin(PORTF, 3, switch0_held && switch4_held ? HIGH : LOW);

        // If PORTF pin0/4 (aka switch1/2) is on (pull-up mode) for the first time (i.e., not currently held)
        // Perform the soft-debounce check, set their "held" state, then toggle their respective LED (red, blue)
        if (read_pin(PORTF, 0) == PUHIGH && !switch0_held) {

            delay(80000);
            if (read_pin(PORTF, 0) == PUHIGH && !switch0_held) {

                switch0_held = 1;
                tgl_bit(GPIO_PORTF_DATA_R, 1); // TODO: Needs to be abstracted in MCAL layer

            }

        }

        if (read_pin(PORTF, 4) == PUHIGH && !switch4_held) {

            delay(80000);
            if (read_pin(PORTF, 4) == PUHIGH && !switch4_held) {

                switch4_held = 1;
                tgl_bit(GPIO_PORTF_DATA_R, 2); // TODO: Needs to be abstracted in MCAL layer

            }

        }

    }

}

void lab3R_task1() {

    while (1) {

        write_pin(PORTF, 1, !read_pin(PORTF, 0));
        write_pin(PORTF, 2, !read_pin(PORTF, 4));

    }

}

void lab3B_task2() {

    while (1) {

        for (int pin = 1; pin <= 3; pin++) {

            write_pin(PORTF, pin, HIGH);
            for (volatile int i = 0; i < 256000; i++); // delay

        }

        for (int pin = 1; pin <= 3; pin++) write_pin(PORTF, pin, LOW);
        for (volatile int i = 0; i < 512000; i++); // delay

    }

}


// Old manual code w/o abstraction layers - Lab 3A_task1 + 3A_task2
// int main() {

//     SYSCTL_RCGCGPIO_R |= 0x20; // Activating the clock on Port F
//     while ((SYSCTL_PRGPIO_R & 0x20) == 0); // Ensure activation
//     GPIO_PORTF_LOCK_R = 0x4C4F434B; // Unlock port F registers
//     GPIO_PORTF_CR_R = 0x1F; // Allow changes in first 5 pins
//     GPIO_PORTF_DIR_R = 0xE; // Set direction of LED pins out
//     GPIO_PORTF_PUR_R = 0x11; // Setting switches as pull-up
//     GPIO_PORTF_DEN_R = 0x1F; // Enabling digital operations

//     while (1) { // System infinite loop

//         for (int j = 0; j < 8; j++) { // Looping through the eight states of RGB

//             for (volatile long long int i = 0; i < 256000; i++); // With delay
//             GPIO_PORTF_DATA_R += 0x2;

//         }
//         // Then, after a longer delay, turn all the lights off
//         for (volatile long long int i = 0; i < 512000; i++);
//         GPIO_PORTF_DATA_R &= !(0xE);

//     }

//     return 0;

// }
