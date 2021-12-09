#include "SYSTICK.h"

void SysTickDisable(void) {

    clr_bit(NVIC_ST_CTRL_R, 0);
    set_bit(NVIC_ST_CURRENT_R, 0);

}

void SysTickEnable(void) {

    set_bit(NVIC_ST_CTRL_R, 0);
    clr_bit(NVIC_ST_CTRL_R, 1);
    set_bit(NVIC_ST_CTRL_R, 2);

}

void SysTickPeriodSet(uint32 millis) {

    uint32 ticks = millis * 16000 - 1;
    NVIC_ST_RELOAD_R = ticks;

}

uint8 SysTickTimeout(void) {

    return get_bit(NVIC_ST_CTRL_R, 16);

}
