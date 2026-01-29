/* 
 * File:   clock_app.h
 * Author: kiki
 *
 * Created on January 29, 2026, 11:41 AM
 */

#ifndef CLOCK_APP_H
#define	CLOCK_APP_H

typedef enum {
    CL_TIMEFORMAT_12H = 0,
    CL_TIMEFORMAT_24H
} CL_TimeFormat_t;

typedef enum {
    CL_DISPLAY_ANALOG = 0,
    CL_DISPLAY_DIGITAL
} CL_DisplayMode_t;

typedef struct {
    
};



void APP_Init();
void APP_Loop();

#endif	/* CLOCK_APP_H */

