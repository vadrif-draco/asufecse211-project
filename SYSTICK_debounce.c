#include "SYSTICK_debounce.h"

// Variable that is to be polled on internally for delaying
//
static bool _waiting_for_debounce = true;

// Function to be called internally as the ISR handler for the timeout event
//
void _SYSTICK_debounce_isr();

void SYSTICK_debounce_ms_init(uint8_t ms) {

    // Disable-enable sandwich including setting wait period and ISR handler
    SysTickDisable();
    SysTickIntDisable();
    SysTickPeriodSet(16000 * ms - 1);
    SysTickIntRegister(_SYSTICK_debounce_isr);
    SysTickIntEnable();
    // SysTickEnable(); to be called when it's time to wait for debounce

}

void SYSTICK_debounce_wait() {

    SysTickEnable();
    _waiting_for_debounce = true;
    while (_waiting_for_debounce);

}

void _SYSTICK_debounce_isr() {

    SysTickDisable();
    _waiting_for_debounce = false;

}
