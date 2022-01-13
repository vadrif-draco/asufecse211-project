#include "GPIO.h"

// Private Mapping Functions
static uint32_t _map_port(GPIO_base);
static uint32_t _map_periph(GPIO_base);
static uint32_t _map_config(GPIO_config);
static uint32_t _map_int_flag(GPIO_pin);
static uint32_t _map_int_type(GPIO_int_trigger);
static uint8_t _map_pin(GPIO_pin);

void GPIO_init(GPIO_base base, GPIO_pin pin, GPIO_dir direction) {

    // 1. Run Clock Gating to enable GPIO Port
    SysCtlPeripheralEnable(_map_periph(base));
    while (!SysCtlPeripheralReady(_map_periph(base)));

    // 2. Unlock pin (not necessary for all pins)
    GPIOUnlockPin(_map_port(base), _map_pin(pin));

    // 3. Set direction (and implicitly digital enable)
    if (direction == OUT) GPIOPinTypeGPIOOutput(_map_port(base), _map_pin(pin));
    else GPIOPinTypeGPIOInput(_map_port(base), _map_pin(pin));

}

void GPIO_launchpad_config(GPIO_base base, GPIO_pin pin, GPIO_config config) {

    GPIOPadConfigSet(_map_port(base), _map_pin(pin), GPIO_STRENGTH_2MA, _map_config(config));

}

void GPIO_register_interrupt(GPIO_base base, GPIO_pin pin, GPIO_int_trigger trigger, void (*handler)(void)) {

    GPIOIntTypeSet(_map_port(base), _map_pin(pin), _map_int_type(trigger));
    GPIOIntRegister(_map_port(base), handler);
    // GPIOIntRegisterPin(_map_port(base), _map_pin(pin), handler);

}

void GPIO_disable_interrupt(GPIO_base base, GPIO_pin pin) {

    GPIOIntClear(_map_port(base), _map_int_flag(pin));
    GPIOIntDisable(_map_port(base), _map_int_flag(pin));

}

void GPIO_enable_interrupt(GPIO_base base, GPIO_pin pin) {

    GPIOIntClear(_map_port(base), _map_int_flag(pin));
    GPIOIntEnable(_map_port(base), _map_int_flag(pin));

}

void GPIO_clear_flag(GPIO_base base, GPIO_pin pin) {

    GPIOIntClear(_map_port(base), _map_int_flag(pin));

}

int32_t GPIO_read_pin(GPIO_base base, GPIO_pin pin) {

    return GPIOPinRead(_map_port(base), _map_pin(pin));

}

void GPIO_write_pin(GPIO_base base, GPIO_pin pin, GPIO_val value) {

    GPIOPinWrite(_map_port(base), _map_pin(pin), value == HIGH ? 0xFF : 0x00);

}

void GPIO_toggle_pin(GPIO_base base, GPIO_pin pin) {

    GPIO_write_pin(base, pin, GPIO_read_pin(base, pin) ? LOW : HIGH);

}

// The following mapping functions map our custom enums with TivaWare's

uint32_t _map_port(GPIO_base base) {

    switch (base) {

        case PORTA: return GPIO_PORTA_BASE;
        case PORTB: return GPIO_PORTB_BASE;
        case PORTC: return GPIO_PORTC_BASE;
        case PORTD: return GPIO_PORTD_BASE;
        case PORTE: return GPIO_PORTE_BASE;
        case PORTF: return GPIO_PORTF_BASE;
        default: return 0;

    }

}

uint32_t _map_periph(GPIO_base base) {

    switch (base) {

        case PORTA: return SYSCTL_PERIPH_GPIOA;
        case PORTB: return SYSCTL_PERIPH_GPIOB;
        case PORTC: return SYSCTL_PERIPH_GPIOC;
        case PORTD: return SYSCTL_PERIPH_GPIOD;
        case PORTE: return SYSCTL_PERIPH_GPIOE;
        case PORTF: return SYSCTL_PERIPH_GPIOF;
        default: return 0;

    }

}

uint32_t _map_config(GPIO_config config) {

    switch (config) {

        case ANALOG: return GPIO_PIN_TYPE_ANALOG;
        case PULL_UP: return GPIO_PIN_TYPE_STD_WPU;
        case PULL_DOWN: return GPIO_PIN_TYPE_STD_WPD;
        case OPEN_DRAIN: return GPIO_PIN_TYPE_OD;
        default: return 0;

    }

}

uint32_t _map_int_flag(GPIO_pin pin) {

    switch (pin) {

        case PIN0: return GPIO_INT_PIN_0;
        case PIN1: return GPIO_INT_PIN_1;
        case PIN2: return GPIO_INT_PIN_2;
        case PIN3: return GPIO_INT_PIN_3;
        case PIN4: return GPIO_INT_PIN_4;
        case PIN5: return GPIO_INT_PIN_5;
        case PIN6: return GPIO_INT_PIN_6;
        case PIN7: return GPIO_INT_PIN_7;
        default: return 0;

    }

}

uint32_t _map_int_type(GPIO_int_trigger trigger) {

    switch (trigger) {

        case FALLING_EDGE: return GPIO_FALLING_EDGE;
        case RISING_EDGE: return GPIO_RISING_EDGE;
        case EITHER_EDGE: return GPIO_BOTH_EDGES;
        case LOW_LEVEL: return GPIO_LOW_LEVEL;
        case HIGH_LEVEL: return GPIO_HIGH_LEVEL;
        default: return 0;

    }

}

uint8_t _map_pin(GPIO_pin pin) {

    switch (pin) {

        case PIN0: return GPIO_PIN_0;
        case PIN1: return GPIO_PIN_1;
        case PIN2: return GPIO_PIN_2;
        case PIN3: return GPIO_PIN_3;
        case PIN4: return GPIO_PIN_4;
        case PIN5: return GPIO_PIN_5;
        case PIN6: return GPIO_PIN_6;
        case PIN7: return GPIO_PIN_7;
        default: return 0;

    }

}
