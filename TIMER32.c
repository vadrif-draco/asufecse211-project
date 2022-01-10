#include "TIMER32.h"

// Private Mapping Functions
static uint32_t _map_port(TIMER32_base);
static uint32_t _map_periph(TIMER32_base);
static uint32_t _map_config(TIMER32_config);


void TIMER32_ms_init(TIMER32_base base, TIMER32_config config, uint16_t ms, void (*timeout_handler)(void)) {

    // 1. Run Clock Gating to enable GPTM Timer, then wait until it is ready
    SysCtlPeripheralEnable(_map_periph(base));
    while (!SysCtlPeripheralReady(_map_periph(base)));

    // 2. Disable Timer
    TimerDisable(_map_port(base), TIMER_A);

    // 3. Configure 32-bit (full-width) Timer
    TimerConfigure(_map_port(base), _map_config(config));

    // 4. Set Timer Interval Load
    TimerControlStall(_map_port(base), TIMER_A, true); // Enable stall; to debug
    TimerLoadSet(_map_port(base), TIMER_A, (16000 * ms) - 1);

    // 5. Clear Interrupt Flag just in case it was up from any previous code
    TimerIntClear(_map_port(base), TIMER_TIMA_TIMEOUT);

    // 6. Enable Timer Interrupt
    TimerIntEnable(_map_port(base), TIMER_TIMA_TIMEOUT);

    // 7. Register Timeout Handler
    TimerIntRegister(_map_port(base), TIMER_A, timeout_handler);

}

void TIMER32_register_timeout_interrupt(TIMER32_base base, void (*timeout_handler)(void)) {

    TimerIntRegister(_map_port(base), TIMER_A, timeout_handler);

}

void TIMER32_clear_timeout_flag(TIMER32_base base) {

    TimerIntClear(_map_port(base), TIMER_TIMA_TIMEOUT);

}

uint16_t TIMER32_get_remaining_ms(TIMER32_base base) {

    return (uint16_t) ((TimerValueGet(_map_port(base), TIMER_A) + 1) / 16000);

}

void TIMER32_start(TIMER32_base base) { TimerEnable(_map_port(base), TIMER_A); }
void TIMER32_resume(TIMER32_base base) { TimerEnable(_map_port(base), TIMER_A); }
void TIMER32_pause(TIMER32_base base) { TimerDisable(_map_port(base), TIMER_A); }


uint32_t _map_port(TIMER32_base base) {

    switch (base) {

        case TIMER0: return TIMER0_BASE;
        case TIMER1: return TIMER1_BASE;
        case TIMER2: return TIMER2_BASE;
        case TIMER3: return TIMER3_BASE;
        case TIMER4: return TIMER4_BASE;
        case TIMER5: return TIMER5_BASE;
        case TIMER6: return TIMER6_BASE;
        case TIMER7: return TIMER7_BASE;
        default: return 0;

    }

}

uint32_t _map_periph(TIMER32_base base) {

    switch (base) {

        case TIMER0: return SYSCTL_PERIPH_TIMER0;
        case TIMER1: return SYSCTL_PERIPH_TIMER1;
        case TIMER2: return SYSCTL_PERIPH_TIMER2;
        case TIMER3: return SYSCTL_PERIPH_TIMER3;
        case TIMER4: return SYSCTL_PERIPH_TIMER4;
        case TIMER5: return SYSCTL_PERIPH_TIMER5;
        case TIMER6: return SYSCTL_PERIPH_TIMER6;
        case TIMER7: return SYSCTL_PERIPH_TIMER7;
        default: return 0;

    }

}

uint32_t _map_config(TIMER32_config config) {

    switch (config) {

        case ONE_SHOT_DOWN: return TIMER_CFG_ONE_SHOT;
        case ONE_SHOT_UP: return TIMER_CFG_ONE_SHOT_UP;
        case PERIODIC_DOWN: return TIMER_CFG_PERIODIC;
        case PERIODIC_UP: return TIMER_CFG_PERIODIC_UP;
        case RTC: return TIMER_CFG_RTC;
        default: return 0;

    }

}
