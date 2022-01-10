#include "UART0.h"

#ifdef REGISTER_LEVEL_VERSION

void UART0_init(uint32_t baudrate);
void UART0_send_string(uint8_t*);
void UART0_send_char(uint8_t);
uint8_t UART0_receive_char();

void UART0_init(uint32_t baudrate) {

    SYSCTL_RCGCUART_R |= 1; /* provide clock to UART0 */
    SYSCTL_RCGCGPIO_R |= 1; /* enable clock to PORTA */

    UART0_CTL_R = 0; /* disable UART0 */
    UART0_IBRD_R = 104; // 16000000 / (baudrate * 16); // HACK:
    UART0_FBRD_R = 11; // HACK:
    UART0_CC_R = 0; /* use system clock */
    UART0_LCRH_R = 0x60; /* 8-bit, no parity, 1-stop bit, no FIFO */
    UART0_CTL_R = 0x301; /* enable UART0, TXE, RXE */

    GPIO_PORTA_DEN_R |= 0x03; /* Make PA0 and PA1 as digital */
    GPIO_PORTA_AFSEL_R |= 0x03; /* Use PA0,PA1 alternate function */
    GPIO_PORTA_PCTL_R |= 0x11; /* configure PA0 and PA1 for UART */

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
