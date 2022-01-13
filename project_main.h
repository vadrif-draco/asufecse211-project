#ifndef PROJECT_MAIN_H
#define PROJECT_MAIN_H

#ifndef PART_TM4C123GH6PM
#define PART_TM4C123GH6PM
#endif

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "driverlib/interrupt.h"

#include "macros.h"
#include "TLSFSM.h"

#include "GPIO.h"
#include "UART0.h"
#include "TIMER32.h"
#include "SYSTICK_debounce.h"

// State Enforcer:
// 1. Cycles states
// 2. Propagtes current state's outputs
// 3. Calls current state's transition action
//
void proceed_to_next_tls();

// State Actions and ISRs

void state0_action();
void state1_action();
void state2_action();
void state3_action();
void state4_action();
void state5_action();
void ped_btn_action1();
void ped_btn_action2();
void background_ped_btn_action1();
void background_ped_btn_action2();
void ped1_btn_isr();
void ped2_btn_isr();

// Re-configure timer as per current state's delay_ms value, interrupt flag is cleared implicitly
//
void restart_main_timer();

// Propagates current state's outputs to GPIO pins of concern (either on/off or in flashing mode)
//
void propagate_outputs();

// Responsible for flashing GPIO pins when defined by state to be in flashing mode
//
void flasher();

#endif /* PROJECT_MAIN_H */
