#ifndef TIMER32_H
#define TIMER32_H

#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_memmap.h"
#include "driverlib/timer.h"
#include "driverlib/sysctl.h"

typedef enum { TIMER0, TIMER1, TIMER2, TIMER3, TIMER4, TIMER5, TIMER6, TIMER7 } TIMER32_base;
typedef enum { ONE_SHOT_DOWN, ONE_SHOT_UP, PERIODIC_DOWN, PERIODIC_UP, RTC } TIMER32_config;

// Initialization Function
// Initializaties the provided timer(base) into 32-bit mode in the required configuration
// Configurations can be one of the values in the TIMER32_config enum in this header file
// In addition the waiting period and the timeout event ISR handler are configured here
//
void TIMER32_ms_init(TIMER32_base, TIMER32_config, uint16_t ms, void (*timeout_handler)(void));

// Interrupt Registration Function
// An independent function to register the timeout event ISR handler
//
void TIMER32_register_timeout_interrupt(TIMER32_base, void (*timeout_handler)(void));

// Clears interrupt flag on provided timer(base)
//
void TIMER32_clear_timeout_flag(TIMER32_base);

// Gets the remaining amount of time for the timeout of the provided timer(base) in ms
//
uint16_t TIMER32_get_remaining_ms(TIMER32_base);

// Starts timer if not running, does nothing otherwise
//
void TIMER32_start(TIMER32_base);

// Resumes timer if paused/not running, does nothing otherwise
// This function is just an alias to TIMER32_start for convenience
//
void TIMER32_resume(TIMER32_base);

// Pauses timer if running, does nothing otherwise
//
void TIMER32_pause(TIMER32_base);

#endif /* TIMER32_H */
