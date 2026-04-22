#include "TM4C123GH6PM.h"
#include "uart.h"

void uart0_init(void) {
    // Enable clocks for UART0 and GPIOA
    SYSCTL->RCGCUART |= (1 << 0);
    SYSCTL->RCGCGPIO |= (1 << 0);

    // Wait for peripherals to be ready
    while (!(SYSCTL->PRUART & (1 << 0)));
    while (!(SYSCTL->PRGPIO & (1 << 0)));

    // Configure PA0 (RX) and PA1 (TX) as UART pins
    GPIOA->AFSEL |= (1 << 0) | (1 << 1);
    GPIOA->PCTL  |= (1 << 0) | (1 << 4);   // PMC0=1, PMC1=1 for UART
    GPIOA->DEN   |= (1 << 0) | (1 << 1);

    // Disable UART before configuring
    UART0->CTL &= ~(1 << 0);

    // Baud rate: 115200, system clock = 16MHz
    // BRD = 16,000,000 / (16 * 115200) = 8.680...
    // IBRD = 8, FBRD = int(0.680 * 64 + 0.5) = 44
    UART0->IBRD = 8;
    UART0->FBRD = 44;

    // 8-bit, no parity, 1 stop bit, FIFOs enabled
    UART0->LCRH = (0x3 << 5) | (1 << 4);

    // Enable UART, TX, RX
    UART0->CTL |= (1 << 0) | (1 << 8) | (1 << 9);
}

void uart0_print(const char *str) {
    while (*str) {
        // Wait until TX FIFO is not full
        while (UART0->FR & (1 << 5));
        UART0->DR = *str++;
    }
}
