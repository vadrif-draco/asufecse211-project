#ifndef TIMER32_H
#define TIMER32_H

#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_memmap.h"
#include "driverlib/timer.h"
#include "driverlib/sysctl.h"

typedef enum { TIMER0, TIMER1, TIMER2, TIMER3, TIMER4, TIMER5, TIMER6, TIMER7 } TIMER32_base;
typedef enum { ONE_SHOT_DOWN, ONE_SHOT_UP, PERIODIC_DOWN, PERIODIC_UP, RTC } TIMER32_config;

void TIMER32_ms_init(TIMER32_base, TIMER32_config, uint16_t ms, void (*timeout_handler)(void));
void TIMER32_register_timeout_interrupt(TIMER32_base, void (*timeout_handler)(void));
void TIMER32_clear_timeout_flag(TIMER32_base);
void TIMER32_start(TIMER32_base);
void TIMER32_resume(TIMER32_base);
void TIMER32_pause(TIMER32_base);

#endif /* TIMER32_H */
