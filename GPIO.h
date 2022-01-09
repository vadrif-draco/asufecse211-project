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

void GPIO_init(GPIO_base, GPIO_pin, GPIO_dir);
void GPIO_launchpad_config(GPIO_base, GPIO_pin, GPIO_config);
void GPIO_register_interrupt(GPIO_base, GPIO_pin, GPIO_int_trigger, void (*handler)(void));
void GPIO_disable_interrupt(GPIO_base, GPIO_pin);
void GPIO_enable_interrupt(GPIO_base, GPIO_pin);
void GPIO_clear_flag(GPIO_base base, GPIO_pin pin);
int32_t GPIO_read_pin(GPIO_base, GPIO_pin);
void GPIO_write_pin(GPIO_base, GPIO_pin, GPIO_val);
void GPIO_toggle_pin(GPIO_base, GPIO_pin);

#endif /* GPIO_H */
