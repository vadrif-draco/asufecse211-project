#include "SYSTICK_debounce.h"

void SYSTICK_debounce_ms_init(uint8_t ms) {

    SysTickDisable();
    SysTickIntDisable();
    SysTickPeriodSet(16000 * ms - 1);
    SysTickIntRegister(SYSTICK_debounce_isr);
    SysTickIntEnable();
    // SysTickEnable(); to be called when it's time to wait for debounce

}

void SYSTICK_debounce_wait() {

    SysTickEnable();
    waiting_for_debounce = true;
    while (waiting_for_debounce);

}

void SYSTICK_debounce_isr() {

    SysTickDisable();
    waiting_for_debounce = false;

}
