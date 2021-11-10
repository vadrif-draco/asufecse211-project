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

        if (read_pin(PORTF, 0) == OFF) 
        {
          DELAY(100000);
          if (read_pin(PORTF, 0) == OFF) 
          {
            switch0_held = 0;
          }
        }
        if (read_pin(PORTF, 4) == OFF) 
        {
          DELAY(100000);
          if (read_pin(PORTF, 4) == OFF) 
          {
            switch4_held = 0;
          }
        }
        // Green Stuff
        write_pin(PORTF, 3, read_pin(PORTF, 0) == ON && read_pin(PORTF, 4) == ON ? HIGH : LOW);
        
        if (read_pin(PORTF, 0) == ON && !switch0_held) {
          DELAY(100000);
          if(read_pin(PORTF, 0) == ON && !switch0_held)
          {
            tgl_bit(GPIO_PORTF_DATA_R, 1); 
            switch0_held = 1; 
          }
        }
        if (read_pin(PORTF, 4) == ON && !switch4_held) {
          DELAY(100000);
          if (read_pin(PORTF, 4) == ON && !switch4_held) {
            tgl_bit(GPIO_PORTF_DATA_R, 2); 
            switch4_held = 1;
          }
        }

    }

}

void lab4A_task2() {

    uint8 led_state = 0; // 0 = all, 1 = R, 2 = G, 3 = B
    uint8 switch0_held = 0;
    uint8 switch4_held = 0;

    while (1) {

        if (!read_pin(PORTF, 0)) 
        {
          DELAY(10000);
          if (!read_pin(PORTF, 0)) 
          {
            switch0_held = 0;
          }
        }
        if (!read_pin(PORTF, 4)) 
        {
          DELAY(10000);
          if (!read_pin(PORTF, 4)) 
          {
            switch4_held = 0;
          }
        }
        if (read_pin(PORTF, 0) && !switch0_held) { 
          DELAY(10000);
          if (read_pin(PORTF, 0) && !switch0_held) { 
            led_state = (led_state + 1) % 4;
            switch0_held = 1; 
          }

        }
        if (read_pin(PORTF, 4) && !switch4_held) { 
          DELAY(10000);
          if (read_pin(PORTF, 4) && !switch4_held) { 
            led_state = (led_state + 4 - 1) % 4;
            switch4_held = 1; 
          }
        }

        switch (led_state) {

            case 0: write_port(PORTF, 0xE); break;
            case 1: write_port(PORTF, 0x2); break;
            case 2: write_port(PORTF, 0x8); break;
            case 3: write_port(PORTF, 0x4); break;
            default: break;

        }

    }

}

int main() {
    for (int pin = 1; pin <= 3; pin++) DIO_init(PORTF, pin, OUT); // LED pins
    DIO_init(PORTF, 0, IN); DIO_init(PORTF, 4, IN); // Switch pins
    GPIO_PORTF_PUR_R |= 0x11; // HACK: PDR should be used, but it doesn't work

    // lab3B_task2();
    // lab3R_task1();
     // lab4A_task1();
    lab4A_task2();

    return 0;

}


// Old manual code w/o abstraction layers - Lab 3A_task1 + 3A_task2
// int main() {
//
//     SYSCTL_RCGCGPIO_R |= 0x20; // Activating the clock on Port F
//     while ((SYSCTL_PRGPIO_R & 0x20) == 0); // Ensure activation
//     GPIO_PORTF_LOCK_R = 0x4C4F434B; // Unlock port F registers
//     GPIO_PORTF_CR_R = 0x1F; // Allow changes in first 5 pins
//     GPIO_PORTF_DIR_R = 0xE; // Set direction of LED pins out
//     GPIO_PORTF_PDR_R = 0x11; // Setting switches as pull-up
//     GPIO_PORTF_DEN_R = 0x1F; // Enabling digital operations
//
//     while (1) { // System infinite loop
//        write_pin(PORTF, 1, !read_pin(PORTF, 0));
//     }
//
//     return 0;
//
// }