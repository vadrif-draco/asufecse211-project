#include "tm4c123gh6pm.h" // Header file containing pointer typedefs to all usable addresses of the microcontroller
#include "MCAL/DIO/DIO.h" // Header file containing the DIO abstraction layer functions and definitions
#include <stdint.h> // Header file containing standard data types used in the above header file


int main() {

    DIO_init(PORTF, 1, OUT);
    DIO_init(PORTF, 2, OUT);
    DIO_init(PORTF, 3, OUT);

    while (1) {

        for (int pin = 1; pin <= 3; pin++) {

            for (volatile int i = 0; i < 256000; i++);
            write_pin(GPIO_PORTF_DATA_R, pin, HIGH);

        }

        for (volatile int i = 0; i < 512000; i++);
        write_pin(GPIO_PORTF_DATA_R, 1, LOW);
        write_pin(GPIO_PORTF_DATA_R, 2, LOW);
        write_pin(GPIO_PORTF_DATA_R, 3, LOW);

    }

    return 0;

}


// Old manual code w/o abstraction layers
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
