#include "DIO.h"

void DIO_init(int8 port, int8 pin, int8 dir) {

    set_bit(SYSCTL_RCGCGPIO_R, port);

    while (get_bit(SYSCTL_PRGPIO_R, port) == 0);

    switch (port) {

        case PORTA:
            dir == OUT ? set_bit(GPIO_PORTA_DIR_R, pin) : clr_bit(GPIO_PORTA_DIR_R, pin);
            set_bit(GPIO_PORTA_DEN_R, pin);
            break;

        case PORTB:
            dir == OUT ? set_bit(GPIO_PORTB_DIR_R, pin) : clr_bit(GPIO_PORTB_DIR_R, pin);
            set_bit(GPIO_PORTB_DEN_R, pin);
            break;

        case PORTC:
            dir == OUT ? set_bit(GPIO_PORTC_DIR_R, pin) : clr_bit(GPIO_PORTC_DIR_R, pin);
            set_bit(GPIO_PORTC_DEN_R, pin);
            break;

        case PORTD:
            dir == OUT ? set_bit(GPIO_PORTD_DIR_R, pin) : clr_bit(GPIO_PORTD_DIR_R, pin);
            set_bit(GPIO_PORTD_DEN_R, pin);
            break;

        case PORTE:
            dir == OUT ? set_bit(GPIO_PORTE_DIR_R, pin) : clr_bit(GPIO_PORTE_DIR_R, pin);
            set_bit(GPIO_PORTE_DEN_R, pin);
            break;

        case PORTF:
            set_bit(GPIO_PORTF_CR_R, pin); // TODO: Need to ask if required for other ports too...
            GPIO_PORTF_LOCK_R = 0x4C4F434B; // TODO: Need to ask if required for ports C & D too...
            dir == OUT ? set_bit(GPIO_PORTF_DIR_R, pin) : clr_bit(GPIO_PORTF_DIR_R, pin);
            set_bit(GPIO_PORTF_DEN_R, pin);
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

int8 read_pin(int8 port, int8 pin) {

    switch (port) {

        case PORTA: return get_bit(GPIO_PORTA_DATA_R, pin);
        case PORTB: return get_bit(GPIO_PORTB_DATA_R, pin);
        case PORTC: return get_bit(GPIO_PORTC_DATA_R, pin);
        case PORTD: return get_bit(GPIO_PORTD_DATA_R, pin);
        case PORTE: return get_bit(GPIO_PORTE_DATA_R, pin);
        case PORTF: return get_bit(GPIO_PORTF_DATA_R, pin);
        default: return 2;

    }
}

uint32 read_port(int8 port) {

    switch (port) {

        case PORTA: return GPIO_PORTA_DATA_R;
        case PORTB: return GPIO_PORTB_DATA_R;
        case PORTC: return GPIO_PORTC_DATA_R;
        case PORTD: return GPIO_PORTD_DATA_R;
        case PORTE: return GPIO_PORTE_DATA_R;
        case PORTF: return GPIO_PORTF_DATA_R;
        default: return 2;

    }
}
