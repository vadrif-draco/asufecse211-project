#ifndef TLSFSM_H
#define TLSFSM_H

#include <stdint.h>

// Moore FSM Structure for Traffic Light State (TLS)

// output: the LEDs to turn on
// delay_ms: self-explanatory...
// next_state: the index of the next state in the states vector
// action: the function to be executed when this state is over, if any (could be none)

typedef struct {

    uint16_t output;
    uint16_t delay_ms;
    uint8_t next_state;
    void (*action)(void);

} TrafficLightState;

#endif /* TLSFSM_H */
