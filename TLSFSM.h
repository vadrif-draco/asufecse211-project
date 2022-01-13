#ifndef TLSFSM_H
#define TLSFSM_H

#include <stdint.h>

// Moore Finite State Machine (FSM) Struct representing the Traffic Light State (TLS)
//
// output: 16-bit value resembling the states of the system LEDs in terms of on/off/flashing
// delay_ms: The delay in ms after which this state naturally transitions to the next state
// next_state: The index of the next state in the states vector that is to be transitioned to
// action: The function to be executed when this state naturally transitions to its following one
//
typedef struct TrafficLightState {

    uint16_t output;
    uint16_t delay_ms;
    uint8_t next_state;
    void (*action)(void);

} TrafficLightState;

#endif /* TLSFSM_H */
