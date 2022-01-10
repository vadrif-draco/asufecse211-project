#include "UART0.h"

#ifndef REGISTER_LEVEL_VERSION

void HELPMEPLEAAAAAASE() {

    UARTIntClear(UART0_BASE, UART_INT_TX | UART_INT_RX);
    __asm("NOP");

}

void UART0_init(uint32_t baudrate) {

    // 1. Run Clock Gating to enable UART Port
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_UART0));

    // 2. Run Clock Gating to enable corresponding GPIO Port
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA));

    // 3. Disable before configuring
    UARTDisable(UART0_BASE);

    // 4. Configure UART0's communication settings
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), baudrate,

        UART_CONFIG_WLEN_8 // 8 data bits
        | UART_CONFIG_STOP_ONE // 1 stop bit
        | UART_CONFIG_PAR_NONE // no parity bits

    );

    // 5. Start
    UARTEnable(UART0_BASE);

}

void UART0_send_string(uint8_t* str) { while (*str) UART0_send_char(*(str++)); }
void UART0_send_char(uint8_t chr) { UARTCharPut(UART0_BASE, chr); }
uint8_t UART0_receive_char() { return UARTCharGet(UART0_BASE); }

#endif
