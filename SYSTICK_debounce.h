#ifndef SYSTICK_DEBOUNCE_H
#define SYSTICK_DEBOUNCE_H

#include <stdint.h>
#include <stdbool.h>

#include "driverlib/systick.h"

// Function to setup SYSTICK for debounce purposes with provided duration in ms
//
void SYSTICK_debounce_ms_init(uint8_t);

// Blocking Function to start the debounce check
// Halts processing for the specified period of time in SYSTICK_debounce_ms_init
//
void SYSTICK_debounce_wait();

#endif /* SYSTICK_DEBOUNCE_H */
