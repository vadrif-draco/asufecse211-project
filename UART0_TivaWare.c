#include "UART0.h"

#ifndef REGISTER_LEVEL_VERSION

void UART0_init(uint32_t baudrate) {

    // 1. Run Clock Gating to enable corresponding GPIO Port
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA));

    // 2. Configure pins A0 and A1 as the digital UART0 Rx and Tx pins
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    // 3. Run Clock Gating to enable UART Port
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_UART0));

    // 4. Disable before configuring
    UARTDisable(UART0_BASE);

    // 5. Configure UART0's communication settings
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), baudrate,

        UART_CONFIG_WLEN_8 // 8 data bits
        | UART_CONFIG_STOP_ONE // 1 stop bit
        | UART_CONFIG_PAR_NONE // no parity bits

    );

    // 6. Now we're ready
    UARTEnable(UART0_BASE);

}

uint8_t UART0_receive_char(void) {

    while (!UARTCharsAvail(UART0_BASE)); // Wait if there're no characters to receive
    return UARTCharGetNonBlocking(UART0_BASE);

}

void UART0_send_char(uint8_t c) {

    while (!UARTSpaceAvail(UART0_BASE)); // Wait if there's no more room for transmit
    UARTCharPutNonBlocking(UART0_BASE, c);

}

void UART0_send_string(uint8_t* str) { while (*str) UART0_send_char(*(str++)); }

#endif
