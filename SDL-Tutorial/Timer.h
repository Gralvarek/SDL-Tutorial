//
//  Timer.h
//  SDL-Tutorial
//
//  Created by Vero on 27.03.20.
//  Copyright © 2020 Asgard Inc. All rights reserved.
//

#ifndef Timer_h
#define Timer_h

#include <stdio.h>
#include <stdlib.h>
#include "Constants.h"
#include <SDL.h>



// Timer class


typedef struct _Timer {
    Uint32 start_ticks; // The clock timer when the timer started
    Uint32 paused_ticks; // The ticks stored when the timer was paused
    bool paused; // The timer status
    bool started;
} Timer;


Timer *Timer_New(void);
void Timer_Init(Timer *self);

void Timer_Destroy(Timer *self);
void Timer_DeleteMembers(Timer *self);

void Timer_Start(Timer *self);
void Timer_Stop(Timer *self);
void Timer_Pause(Timer *self);
void Timer_Unpause(Timer *self);

Uint32 Timer_GetTicks(Timer *self);

bool Timer_IsStarted(Timer *self);
bool Timer_IsPaused(Timer *self);





#endif /* Timer_h */
