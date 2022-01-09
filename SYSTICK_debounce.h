#ifndef SYSTICK_DEBOUNCE_H
#define SYSTICK_DEBOUNCE_H

#include <stdint.h>
#include <stdbool.h>

#include "driverlib/systick.h"

static bool waiting_for_debounce = true;

void SYSTICK_debounce_ms_init(uint8_t);
void SYSTICK_debounce_wait();
void SYSTICK_debounce_isr();

#endif /* SYSTICK_DEBOUNCE_H */
