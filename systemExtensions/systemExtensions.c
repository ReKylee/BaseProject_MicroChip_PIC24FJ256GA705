#include <xc.h>
#include "systemExtensions.h"

static uint32_t system_millis = 0;

void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void)
{
    system_millis++;
    IFS0bits.T1IF = 0; // clear interrupt flag
}

uint32_t millis(void)
{
    return system_millis;
}

void Timer_initialize(void){
    T1CONbits.TON = 0;     // Stop timer during setup
    T1CONbits.TSIDL = 0;   // Continue in idle mode
    T1CONbits.TGATE = 0;   // Gated timer off
    T1CONbits.TCKPS = 0b11; // 1:256 prescaler
    T1CONbits.TCS = 0;     // Use internal clock
    PR1 = 31;              // For 1 ms tick: PR1 = (8e6 / 256) * 0.001 - 1 ? 31
    TMR1 = 0;              // Reset timer
    IPC0bits.T1IP = 1;     // Interrupt priority
    IFS0bits.T1IF = 0;     // Clear interrupt flag
    IEC0bits.T1IE = 1;     // Enable Timer1 interrupt
    __builtin_enable_interrupts(); // Global interrupts enable
    T1CONbits.TON = 1;     // Start timer
}

