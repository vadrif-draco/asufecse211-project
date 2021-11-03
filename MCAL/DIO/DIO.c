#include "DIO.h"

void DIO_init(int8 port, int8 pin, int8 dir) {

    set_bit(SYSCTL_RCGCGPIO_R, port);

    while (get_bit(SYSCTL_PRGPIO_R, port) == 0);

    switch (port) {

        case PORTA:
            dir == IN ? set_bit(GPIO_PORTA_DIR_R, pin) : clr_bit(GPIO_PORTA_DIR_R, pin);
            set_bit(GPIO_PORTA_DEN_R, pin);
            break;

        case PORTB:
            dir == IN ? set_bit(GPIO_PORTB_DIR_R, pin) : clr_bit(GPIO_PORTB_DIR_R, pin);
            set_bit(GPIO_PORTB_DEN_R, pin);
            break;

        case PORTC:
            dir == IN ? set_bit(GPIO_PORTC_DIR_R, pin) : clr_bit(GPIO_PORTC_DIR_R, pin);
            set_bit(GPIO_PORTC_DEN_R, pin);
            break;

        case PORTD:
            dir == IN ? set_bit(GPIO_PORTD_DIR_R, pin) : clr_bit(GPIO_PORTD_DIR_R, pin);
            set_bit(GPIO_PORTD_DEN_R, pin);
            break;

        case PORTE:
            dir == IN ? set_bit(GPIO_PORTE_DIR_R, pin) : clr_bit(GPIO_PORTE_DIR_R, pin);
            set_bit(GPIO_PORTE_DEN_R, pin);
            break;

        case PORTF:
            dir == IN ? set_bit(GPIO_PORTF_DIR_R, pin) : clr_bit(GPIO_PORTF_DIR_R, pin);
            set_bit(GPIO_PORTF_DEN_R, pin);
            GPIO_PORTF_CR_R = 0x1F; // FIXME: This should be done using set_bit for the specific pin
            // TODO: Also do it for the other ports if required - not sure if it is; need to ask...
            GPIO_PORTF_LOCK_R = 0x4C4F434B; // TODO: Need to ask if required for ports C & D too...
            break;

    }

}

void write_pin(int8 port, int8 pin, int8 value) {

    switch (port) {

        case PORTA: value == HIGH ? set_bit(GPIO_PORTA_DATA_R, pin) : clr_bit(GPIO_PORTA_DATA_R, pin); break;
        case PORTB: value == HIGH ? set_bit(GPIO_PORTB_DATA_R, pin) : clr_bit(GPIO_PORTB_DATA_R, pin); break;
        case PORTC: value == HIGH ? set_bit(GPIO_PORTC_DATA_R, pin) : clr_bit(GPIO_PORTC_DATA_R, pin); break;
        case PORTD: value == HIGH ? set_bit(GPIO_PORTD_DATA_R, pin) : clr_bit(GPIO_PORTD_DATA_R, pin); break;
        case PORTE: value == HIGH ? set_bit(GPIO_PORTE_DATA_R, pin) : clr_bit(GPIO_PORTE_DATA_R, pin); break;
        case PORTF: value == HIGH ? set_bit(GPIO_PORTF_DATA_R, pin) : clr_bit(GPIO_PORTF_DATA_R, pin); break;

    }

}

void write_port(int8 port, uint32 value) {

    switch (port) {

        case PORTA: GPIO_PORTA_DATA_R = value; break;
        case PORTB: GPIO_PORTB_DATA_R = value; break;
        case PORTC: GPIO_PORTC_DATA_R = value; break;
        case PORTD: GPIO_PORTD_DATA_R = value; break;
        case PORTE: GPIO_PORTE_DATA_R = value; break;
        case PORTF: GPIO_PORTF_DATA_R = value; break;

    }

}