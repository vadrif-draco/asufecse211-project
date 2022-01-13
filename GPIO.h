#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

typedef enum { PORTA, PORTB, PORTC, PORTD, PORTE, PORTF } GPIO_base;
typedef enum { PIN0, PIN1, PIN2, PIN3, PIN4, PIN5, PIN6, PIN7 } GPIO_pin;

typedef enum { IN, OUT } GPIO_dir;
typedef enum { LOW, HIGH } GPIO_val;
typedef enum { ANALOG, PULL_UP, PULL_DOWN, OPEN_DRAIN } GPIO_config;
typedef enum { FALLING_EDGE, RISING_EDGE, EITHER_EDGE, LOW_LEVEL, HIGH_LEVEL } GPIO_int_trigger;

// Initialization function for digital pins
// Initializations the provided pin and port(base) in the provided direction
//
void GPIO_init(GPIO_base, GPIO_pin, GPIO_dir);


// Configuration function for built-in pins
// Used to choose the launchpad configuration to our liking for the provided pin and port(base)
// Defaults to a strength of 2MA
//
void GPIO_launchpad_config(GPIO_base, GPIO_pin, GPIO_config);

// Interrupt Registration
// Registers an ISR handler to a provided port(base) on the triggering of the provided pin on it
//
void GPIO_register_interrupt(GPIO_base, GPIO_pin, GPIO_int_trigger, void (*handler)(void));

// Disables interrupts on pin+port(base) combination
// Does not unregister existing registered handler
// Implicitly clears any left-over IRQ flag
//
void GPIO_disable_interrupt(GPIO_base, GPIO_pin);

// Enables interrupts on pin+port(base) combination
// Implicitly clears any left-over IRQ flag
//
void GPIO_enable_interrupt(GPIO_base, GPIO_pin);

// Clears interrupt flag on pin+port(base) combination
//
void GPIO_clear_flag(GPIO_base, GPIO_pin);

// Returns the value of the provided pin+port(base) combination
// This value includes its position in a 32-bit retirn value
//
int32_t GPIO_read_pin(GPIO_base, GPIO_pin);

// Writes the value provided (HIGH or LOW) to the pin+port(base) combination
// The value does not need to be positioned in a 32-bit value
//
void GPIO_write_pin(GPIO_base, GPIO_pin, GPIO_val);

// Toggles the provided pin+port(base) combination
//
void GPIO_toggle_pin(GPIO_base, GPIO_pin);

#endif /* GPIO_H */
