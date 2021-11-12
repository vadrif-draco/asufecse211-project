#include "MCAL/DIO/DIO.h" // Header file containing the DIO abstraction layer functions and definitions

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

void lab3R_task1() {

    while (1) {

        write_pin(PORTF, 1, !read_pin(PORTF, 0));
        write_pin(PORTF, 2, !read_pin(PORTF, 4));

    }

}

void lab4A_task1() {

    int8 switch0_held = 0;
    int8 switch4_held = 0;

    while (1) {

        // If PORTF pin0/4 (aka switch1/2) is off (pull-up mode)...
        if (read_pin(PORTF, 0) == PUOFF) {

            delay(80000); // Delay to soft-debounce then re-check; if still off, remove "held" state
            if (read_pin(PORTF, 0) == PUOFF) switch0_held = 0;

        }

        if (read_pin(PORTF, 4) == PUOFF) {

            delay(80000);
            if (read_pin(PORTF, 0) == PUOFF) switch4_held = 0;

        }

        // Write on PORTF pin3 (green LED) HIGH if both switches are held, otherwise LOW
        write_pin(PORTF, 3, switch0_held && switch4_held ? HIGH : LOW);

        // If PORTF pin0/4 (aka switch1/2) is on (pull-up mode) for the first time (i.e., not currently held)
        // Perform the soft-debounce check, set their "held" state, then toggle their respective LED (red, blue)
        if (read_pin(PORTF, 0) == PUON && !switch0_held) {

            delay(80000);
            if (read_pin(PORTF, 0) == PUON && !switch0_held) {

                switch0_held = 1;
                tgl_bit(GPIO_PORTF_DATA_R, 1); // TODO: Needs to be abstracted in MCAL layer

            }

        }

        if (read_pin(PORTF, 4) == PUON && !switch4_held) {

            delay(80000);
            if (read_pin(PORTF, 4) == PUON && !switch4_held) {

                switch4_held = 1;
                tgl_bit(GPIO_PORTF_DATA_R, 2); // TODO: Needs to be abstracted in MCAL layer

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
        if (read_pin(PORTF, 0) == PUOFF) {

            delay(80000); // Delay to soft-debounce then re-check; if still off, remove "held" state
            if (read_pin(PORTF, 0) == PUOFF) switch0_held = 0;

        }

        if (read_pin(PORTF, 4) == PUOFF) {

            delay(80000);
            if (read_pin(PORTF, 0) == PUOFF) switch4_held = 0;

        }

        // If PORTF pin0/4 (aka switch1/2) is on (pull-up mode) for the first time (i.e., not currently held)
        // Perform the soft-debounce check, set their "held" state, then toggle their respective LED (red, blue)
        if (read_pin(PORTF, 0) == PUON && !switch0_held) {

            delay(80000);
            if (read_pin(PORTF, 0) == PUON && !switch0_held) {

                switch0_held = 1;
                led_state = (led_state + 1) % 4;

            }

        }

        if (read_pin(PORTF, 4) == PUON && !switch4_held) {

            delay(80000);
            if (read_pin(PORTF, 4) == PUON && !switch4_held) {

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

void main() {

    for (int pin = 1; pin <= 3; pin++) DIO_init(PORTF, pin, OUT); // LED pins
    DIO_init(PORTF, 0, IN); DIO_init(PORTF, 4, IN); // Switch pins
    GPIO_PORTF_PUR_R = 0x11; // It would be more logical to use PDR here...
    //...but the launchpad's switch is hard-wired to be set in pull-up mode
    // TODO: Need to abstract this register assignment in the MCAL layer

    lab3B_task2();
    // lab3R_task1();
    // lab4A_task1();
    // lab4A_task2();

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
