#include "UART0.h"

#ifdef REGISTER_LEVEL_VERSION

void UART0_init(uint32_t baudrate);
void UART0_send_string(uint8_t*);
void UART0_send_char(uint8_t);
uint8_t UART0_receive_char();

void UART0_init(uint32_t baudrate) {

    // Calculating the baudrate divisor parts for IBRD and FBRD, avoiding use of floats
    // Said floats are avoided by amplifying the value to include three decimal places
    // These decimal places are then extracted and converted to the required FBRD value
    uint32_t amplified_data_rate = (UINT64_C(16000000) * 1000) / (baudrate * 16);
    uint32_t integer_part = amplified_data_rate / 1000;
    uint32_t float_part = ((amplified_data_rate - integer_part * 1000) * 64 + 500) / 1000;

    // Enabling and configuring GPIO necessities for the UART0 pins
    SYSCTL_RCGCGPIO_R |= 1; // Enable Clock Gating to GPIOA (UART0 uses pins A0 and A1)
    while (!(SYSCTL_PRGPIO_R & 1)); // Wait for clock gating to take effect
    GPIO_PORTA_DEN_R |= 0x03; // Enable digital usage of these pins
    GPIO_PORTA_AFSEL_R |= 0x03; // Set them to work as their alternate functions
    GPIO_PORTA_PCTL_R |= 0x11; // Choose UART for the alternate function

    // Enabling and configuring the UART0 module itself
    SYSCTL_RCGCUART_R |= 1; // Enable Clock Gating to UART0
    while (!(SYSCTL_PRUART_R & 1)); // Wait for clock gating to take effect
    UART0_CTL_R = 0; // Disable UART0 before configuring anything
    UART0_CC_R = 0; // Make the UART0 clock be derived from the CPU clock
    UART0_IBRD_R = integer_part; // Should be 104 if baudrate 9600
    UART0_FBRD_R = float_part; // Should be 11 if baudrate 9600
    UART0_LCRH_R = 0x60; // Configuration: 8 data bits, no parity bits, 1 stop bit, no FIFO
    UART0_CTL_R = 0x301; // Now we're ready, so enable UART0, its Tx, and its Rx

}

uint8_t UART0_receive_char(void) {

    while (get_bit(UART0_FR_R, 4) == 1); // Wait if empty (Polling RXFE)
    return UART0_DR_R;

}

void UART0_send_char(uint8_t c) {

    while (get_bit(UART0_FR_R, 5) == 1); // Wait if full (Polling TXFF)
    UART0_DR_R = c;

}

void UART0_send_string(uint8_t* str) { while (*str) UART0_send_char(*(str++)); }

#endif
