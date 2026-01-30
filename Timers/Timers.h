#ifndef TIMERS_H
#define TIMERS_H

#include <xc.h>
#include <stdint.h>

// --- Step 1: Enable only what you need (Memory Efficiency) ---
#define USE_TIMER1
#define USE_TIMER2
// #define USE_TIMER3 // Commented out = Timer3 is free for other modules

// --- Step 2: API (Resolution Flexibility) ---

#ifdef USE_TIMER1
extern volatile uint32_t t1_ticks;
void Timer1_Init(uint32_t freq_hz, uint8_t priority);
#endif

#ifdef USE_TIMER2
extern volatile uint32_t t2_ticks;
void Timer2_Init(uint32_t freq_hz, uint8_t priority);
#endif

uint32_t Timer_GetTicks(uint8_t timer_id);

#endif