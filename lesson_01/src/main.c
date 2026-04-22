#include "TM4C123GH6PM.h"

// Simple delay function
void delay(unsigned long count) {
    while(count--);
}

int main(void) {
    // Enable clock for Port F
    SYSCTL->RCGCGPIO |= (1U << 5);  // Enable clock to GPIOF
    
    // Small delay to allow clock to stabilize
    delay(1);
    
    // Configure PF1, PF2, PF3 as outputs (RGB LEDs)
    GPIOF->DIR |= 0x0E;     // Set PF1, PF2, PF3 as outputs (0000 1110)
    GPIOF->DEN |= 0x0E;     // Digital enable PF1, PF2, PF3
    
    while(1) {
        // Turn on Red LED (PF1)
        GPIOF->DATA = 0x02;
        delay(1000000);
        
        // Turn on Blue LED (PF2)
        GPIOF->DATA = 0x04;
        delay(1000000);
        
        // Turn on Green LED (PF3)
        GPIOF->DATA = 0x08;
        delay(1000000);
        
        // Turn off all LEDs
        GPIOF->DATA = 0x00;
        delay(1000000);
    }
}
