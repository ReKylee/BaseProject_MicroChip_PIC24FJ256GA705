#include "Timers.h"

#ifndef FCY
#define FCY 4000000UL // FCY is FOSC/2, and FOSC is 8MHz for this board.
#endif

/** * This Macro writes the actual function and ISR code. 
 * It calculates PRx based on the 'freq' passed in at runtime.
 */
#define BUILD_TIMER(ID, T_CON, T_PR, T_IE, T_IF, T_IP, T_ON, COUNTER) \
volatile uint32_t COUNTER = 0; \
void Timer##ID##_Init(uint32_t freq, uint8_t priority) { \
    T_CON = 0; \
    T_CON##bits.TCKPS = 0b11; /* 1:256 */ \
    T_PR = (uint16_t)((FCY / (256 * freq)) - 1); \
    T_IP = priority; \
    T_IF = 0; \
    T_IE = 1; \
    T_ON = 1; \
} \
void __attribute__((interrupt, no_auto_psv)) _T##ID##Interrupt(void) { \
    COUNTER++; \
    T_IF = 0; \
}

// --- Expand the code ONLY for enabled timers ---

#ifdef USE_TIMER1
BUILD_TIMER(1, T1CON, PR1, IEC0bits.T1IE, IFS0bits.T1IF, IPC0bits.T1IP, T1CONbits.TON, t1_ticks)
#endif

#ifdef USE_TIMER2
BUILD_TIMER(2, T2CON, PR2, IEC0bits.T2IE, IFS0bits.T2IF, IPC1bits.T2IP, T2CONbits.TON, t2_ticks)
#endif

#ifdef USE_TIMER3
BUILD_TIMER(3, T3CON, PR3, IEC0bits.T3IE, IFS0bits.T3IF, IPC0bits.T3IP, T3CONbits.TON, t3_ticks)
#endif

uint32_t Timer_GetTicks(uint8_t timer_id) {
    uint32_t val = 0;
    __builtin_disi(0x3FFF); // Disable interrupts for atomic read
    if (timer_id == 1) {
#ifdef USE_TIMER1
        val = t1_ticks;
#endif
    } else if (timer_id == 2) {
#ifdef USE_TIMER2
        val = t2_ticks;
#endif
    } else if (timer_id == 3) {
#ifdef USE_TIMER3
        val = t3_ticks;
#endif
    }
    __builtin_disi(0x0000);
    return val;
}