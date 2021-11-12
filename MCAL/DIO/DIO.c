#include "DIO.h"

void DIO_init(int8 port, int8 pin, int8 dir) {

    set_bit(SYSCTL_RCGCGPIO_R, port);

    while (get_bit(SYSCTL_PRGPIO_R, port) == 0);

    switch (port) {

        case PORTA:
            /*
            The GPIOLOCK register enables write access to the GPIOCR register.
            Writing 0x4C4F434B to the GPIOLOCK register unlocks the GPIOCR register.
            Writing any other value to the GPIOLOCK register re-enables the locked state.
            */
            GPIO_PORTA_LOCK_R = 0x4C4F434B;
            /*
            The GPIOCR register is the commit register.
            The value of the GPIOCR register determines...
            ...which bits of GPIOAFSEL/GPIOPUR/GPIOPDR/GPIODEN registers are committed...
            ...when a write to these registers is performed.

            If a bit in the GPIOCR register is cleared...
            ...the data being written to the corresponding bit in these registers...
            ...cannot be committed and retains its previous value.

            If a bit in the GPIOCR register is set...
            ...the data being written to the corresponding bit in these registers...
            ...is committed to the register and reflects the new value.
            */
            set_bit(GPIO_PORTA_CR_R, pin);
            // If pin to be initialized as output, set corresponding bit, otherwise clear bit.
            dir == OUT ? set_bit(GPIO_PORTA_DIR_R, pin) : clr_bit(GPIO_PORTA_DIR_R, pin);
            // Finally, enable digital operations on pin.
            set_bit(GPIO_PORTA_DEN_R, pin);
            break;

        case PORTB:
            GPIO_PORTB_LOCK_R = 0x4C4F434B;
            set_bit(GPIO_PORTB_CR_R, pin);
            dir == OUT ? set_bit(GPIO_PORTB_DIR_R, pin) : clr_bit(GPIO_PORTB_DIR_R, pin);
            set_bit(GPIO_PORTB_DEN_R, pin);
            break;

        case PORTC:
            GPIO_PORTC_LOCK_R = 0x4C4F434B;
            set_bit(GPIO_PORTC_CR_R, pin);
            dir == OUT ? set_bit(GPIO_PORTC_DIR_R, pin) : clr_bit(GPIO_PORTC_DIR_R, pin);
            set_bit(GPIO_PORTC_DEN_R, pin);
            break;

        case PORTD:
            GPIO_PORTD_LOCK_R = 0x4C4F434B;
            set_bit(GPIO_PORTD_CR_R, pin);
            dir == OUT ? set_bit(GPIO_PORTD_DIR_R, pin) : clr_bit(GPIO_PORTD_DIR_R, pin);
            set_bit(GPIO_PORTD_DEN_R, pin);
            break;

        case PORTE:
            GPIO_PORTE_LOCK_R = 0x4C4F434B;
            set_bit(GPIO_PORTE_CR_R, pin);
            dir == OUT ? set_bit(GPIO_PORTE_DIR_R, pin) : clr_bit(GPIO_PORTE_DIR_R, pin);
            set_bit(GPIO_PORTE_DEN_R, pin);
            break;

        case PORTF:
            GPIO_PORTF_LOCK_R = 0x4C4F434B;
            set_bit(GPIO_PORTF_CR_R, pin);
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
