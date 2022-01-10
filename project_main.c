#include "project_main.h"

bool ped_btns_cooling_down = false;
bool ped1_LED_flashing = false;
bool ped2_LED_flashing = false;

#define NUM_OF_STATES 10
#define STARTING_STATE 0

// When we've just started, there is no current state
// However, the next state is the one we start from
//
uint8_t current_state, next_state = STARTING_STATE;

TrafficLightState tls[NUM_OF_STATES] = {

    // Main Loop Sequence
    {0x044D, 1000, 1, state0_action}, // 0
    {0x0418, 5000, 2, state1_action}, // 1, can get pre-empted into 6
    {0x0428, 2000, 3, state2_action}, // 2
    {0x044E, 1000, 4, state3_action}, // 3
    {0x0144, 5000, 5, state4_action}, // 4, can get pre-empted into 8
    {0x0244, 2000, 0, state5_action}, // 5

    // The Two-Step Ped. Interrupt States
    // Reaching these states is not possible through normal flow
    // They are pre-empted into the flow through Ped. Btn. interrupts
    {0x044C, 1000, 7, ped_btn_action1}, // 6
    {0x044D, 1000, 2, ped_btn_action2}, // 7

    {0x044C, 1000, 9, ped_btn_action1}, // 8
    {0x044E, 1000, 5, ped_btn_action2}, // 9

};

void main() {

    // -------------------------------------------------------------------------
    // Initializations ---------------------------------------------------------
    // -------------------------------------------------------------------------

    // Enable interrupts to the processor
    IntMasterEnable();

    // First Traffic Light LEDs
    GPIO_init(PORTA, PIN7, OUT); // R1
    GPIO_init(PORTA, PIN6, OUT); // Y1
    GPIO_init(PORTA, PIN5, OUT); // G1

    // Second Traffic Light LEDs
    GPIO_init(PORTD, PIN3, OUT); // R2
    GPIO_init(PORTD, PIN2, OUT); // Y2
    GPIO_init(PORTD, PIN1, OUT); // G2

    // First Pedestrian LEDs
    GPIO_init(PORTA, PIN3, OUT); // R1
    GPIO_init(PORTA, PIN4, OUT); // G1

    // Second Pedestrian LEDs
    GPIO_init(PORTC, PIN5, OUT); // R2
    GPIO_init(PORTC, PIN4, OUT); // G2

    // Also the launchpad's built-in LEDs; for debugging purposes
    GPIO_init(PORTF, PIN1, OUT);
    GPIO_init(PORTF, PIN2, OUT);
    GPIO_init(PORTF, PIN3, OUT);

    // Pedestrian Buttons
    GPIO_init(PORTC, PIN7, IN); // BTN1
    GPIO_init(PORTD, PIN6, IN); // BTN2
    GPIO_register_interrupt(PORTC, PIN7, RISING_EDGE, ped1_btn_isr);
    GPIO_register_interrupt(PORTD, PIN6, RISING_EDGE, ped2_btn_isr);

    // UART Communication @baudrate:9600
    UART0_init(9600); // UART0 is the built-in UART port for USB comm

    // Adjusting Priorities
    IntPrioritySet(INT_GPIOA, 0x20);
    IntPrioritySet(INT_GPIOB, 0x20);
    IntPrioritySet(INT_GPIOC, 0x20);
    IntPrioritySet(INT_GPIOD, 0x20);
    IntPrioritySet(INT_GPIOE, 0x20);
    IntPrioritySet(INT_GPIOF, 0x20);
    // IntPrioritySet(INT_UART0, 0x20);
    IntPrioritySet(INT_TIMER0A, 0x20);
    IntPrioritySet(INT_TIMER1A, 0x20);
    IntPrioritySet(INT_TIMER2A, 0x20);

    // Will use SYSTICK to debounce the buttons, 30ms interval
    SYSTICK_debounce_ms_init(30);

    // Will use TIMER2 in the flashing part of the ped. LED
    TIMER32_ms_init(TIMER2, PERIODIC_DOWN, 100, flasher);
    TIMER32_start(TIMER2);

    // -------------------------------------------------------------------------
    // Main Program Loop -------------------------------------------------------
    // -------------------------------------------------------------------------

    proceed_to_next_tls();
    uint8_t prev_state = 255;
    while (true) {

        if (prev_state != current_state) {

            uint16_t t0 = TIMER32_get_remaining_ms(TIMER0) + 1, div = 10000;

            prev_state = current_state;

            if (current_state < 6) { // i.e., a normal flow state

                UART0_send_string("\n\n\rCurrently at state #");
                UART0_send_char('0' + current_state);
                UART0_send_string(", next state in ");
                do { UART0_send_char('0' + (t0 / div)); t0 %= div; } while (div /= 10);
                UART0_send_string("ms approximately.");

            } else { // otherwise, a flow interrupt state

                UART0_send_string("\n\n\rPre-empted to interrupt flow, now in state #");
                UART0_send_char('0' + current_state);

            }

        }

    }

}

void proceed_to_next_tls() {

    // Set new current state
    current_state = next_state;

    // Prepare new next state
    next_state = tls[current_state].next_state;

    // Propagate outputs as the state dictates
    propagate_outputs();

    // Call the state's action handler
    tls[current_state].action();

}

void state0_action() { restart_main_timer(); }
void state1_action() { restart_main_timer(); GPIO_enable_interrupt(PORTC, PIN7); }
void state2_action() { restart_main_timer(); GPIO_disable_interrupt(PORTC, PIN7); }
void state3_action() { restart_main_timer(); }
void state4_action() { restart_main_timer(); GPIO_enable_interrupt(PORTD, PIN6); }
void state5_action() { restart_main_timer(); GPIO_disable_interrupt(PORTD, PIN6); }

void ped_btn_action1() {

    // 1. Pause main loop timer
    TIMER32_pause(TIMER0);

    // 2. Initialize and start interrupt timer
    TIMER32_ms_init(TIMER1, ONE_SHOT_DOWN, tls[current_state].delay_ms, proceed_to_next_tls);
    TIMER32_start(TIMER1);

}

void ped_btn_action2() {

    TIMER32_clear_timeout_flag(TIMER1);

    // 1. Re-initialize and start interrupt timer
    TIMER32_ms_init(TIMER1, ONE_SHOT_DOWN, tls[current_state].delay_ms, background_ped_btn_action1);
    TIMER32_start(TIMER1);

}

void background_ped_btn_action1() {

    TIMER32_clear_timeout_flag(TIMER1);

    // 1. Manually return to pre-empted state and resume main loop timer
    // In the states vector, the interrupt states have the same next_state as their pre-emptees
    // So, to get their parents' state number, we can move backwards from that next_state
    current_state = next_state - 1;
    propagate_outputs();
    TIMER32_resume(TIMER0);

    // 2. Re-initialize and start interrupt timer
    TIMER32_ms_init(TIMER1, ONE_SHOT_DOWN, 1000, background_ped_btn_action2);
    TIMER32_start(TIMER1);

}

void background_ped_btn_action2() {

    TIMER32_clear_timeout_flag(TIMER1);

    // 1. Unraise cooldown flag
    ped_btns_cooling_down = false;
    GPIO_write_pin(PORTF, PIN2, LOW);
    GPIO_write_pin(PORTF, PIN3, LOW);

    // 2. No need to "disable" TIMER1, it's in one-shot mode after all

}

void ped1_btn_isr() {

    GPIO_clear_flag(PORTC, PIN7);

    if (ped_btns_cooling_down) return;

    SYSTICK_debounce_wait();

    if (GPIO_read_pin(PORTC, PIN7)) {

        ped_btns_cooling_down = true;
        GPIO_write_pin(PORTF, PIN2, HIGH);
        // Pre-empt the normal state flow
        next_state = 6; proceed_to_next_tls();

    }

}

void ped2_btn_isr() {

    GPIO_clear_flag(PORTD, PIN6);

    if (ped_btns_cooling_down) return;

    SYSTICK_debounce_wait();

    if (GPIO_read_pin(PORTD, PIN6)) {

        ped_btns_cooling_down = true;
        GPIO_write_pin(PORTF, PIN3, HIGH);
         // Pre-empt the normal state flow
        next_state = 8; proceed_to_next_tls();

    }

}

void restart_main_timer() {

    TIMER32_ms_init(TIMER0, ONE_SHOT_DOWN, tls[current_state].delay_ms, proceed_to_next_tls);
    TIMER32_start(TIMER0);

}

void propagate_outputs() {

    //                           5432 1098 7654 3210
    // Output is in the form of: xxxx xRYG xRYG xxxx concerning the two traffic lights

    // First Traffic Light LEDs
    GPIO_write_pin(PORTA, PIN7, get_bit(tls[current_state].output, 10) ? HIGH : LOW); // R1
    GPIO_write_pin(PORTA, PIN6, get_bit(tls[current_state].output, 9) ? HIGH : LOW); // Y1
    GPIO_write_pin(PORTA, PIN5, get_bit(tls[current_state].output, 8) ? HIGH : LOW); // G1

    // Second Traffic Light LEDs
    GPIO_write_pin(PORTD, PIN3, get_bit(tls[current_state].output, 6) ? HIGH : LOW); // R2
    GPIO_write_pin(PORTD, PIN2, get_bit(tls[current_state].output, 5) ? HIGH : LOW); // Y2
    GPIO_write_pin(PORTD, PIN1, get_bit(tls[current_state].output, 4) ? HIGH : LOW); // G2

    //                           5432 1098 7654 3210
    // Output is in the form of: xxxx xxxx xxxx 21xx concerning the two ped. lights
    // If the bit is set, the light is green, otherwise red

    // First Pedestrian LEDs
    GPIO_write_pin(PORTA, PIN3, get_bit(tls[current_state].output, 3) ? LOW : HIGH); // R1
    GPIO_write_pin(PORTA, PIN4, get_bit(tls[current_state].output, 3) ? HIGH : LOW); // G1

    // Second Pedestrian LEDs
    GPIO_write_pin(PORTC, PIN5, get_bit(tls[current_state].output, 2) ? LOW : HIGH); // R2
    GPIO_write_pin(PORTC, PIN4, get_bit(tls[current_state].output, 2) ? HIGH : LOW); // G2

    //                           5432 1098 7654 3210
    // Output is in the form of: xxxx xxxx xxxx xx21 concerning flashing
    // If the bit is set, flash
    ped1_LED_flashing = (get_bit(tls[current_state].output, 1)) ? true : false; // G1
    ped2_LED_flashing = (get_bit(tls[current_state].output, 0)) ? true : false; // G2

}

void flasher() {

    TIMER32_clear_timeout_flag(TIMER2);
    GPIO_toggle_pin(PORTF, PIN1);
    if (ped1_LED_flashing) GPIO_toggle_pin(PORTA, PIN4); // G1
    if (ped2_LED_flashing) GPIO_toggle_pin(PORTC, PIN4); // G2

}
