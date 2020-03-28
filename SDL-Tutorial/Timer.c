//
//  Timer.c
//  SDL-Tutorial
//
//  Created by Vero on 27.03.20.
//  Copyright © 2020 Asgard Inc. All rights reserved.
//

#include "Timer.h"

// Timer function definitions


Timer *Timer_New() {
    Timer *self = (Timer *)malloc(sizeof(Timer));
    Timer_Init(self);
    return self;
}


void Timer_Init(Timer *self) {
    self->start_ticks = 0;
    self->paused_ticks = 0;
    self->started = FALSE;
    self->paused = FALSE;
}

void Timer_Destroy(Timer *self) {
    if (self != NULL) {
        Timer_DeleteMembers(self);
        free(self);
    }
}

void Timer_DeleteMembers(Timer *self) {
    self->start_ticks = 0;
    self->paused_ticks = 0;
    self->started = FALSE;
    self->paused = FALSE;
}


void Timer_Start(Timer *self) {
    // Start the timer
    self->started = TRUE;
    
    // Unpause the timer
    self->paused = FALSE;
    
    // Get the current clock time
    self->start_ticks = SDL_GetTicks();
    self->paused_ticks = 0;
}

void Timer_Stop(Timer *self) {
    // Stop the timer
    self->started = FALSE;
    
    // Unpause the timer
    self->paused = FALSE;
    
    // Clear the tick variables
    self->start_ticks = 0;
    self->paused_ticks = 0;
}

void Timer_Pause(Timer *self) {
    // If the timer is running and isn't paused
    if (self->started && !self->paused) {
        
        // Pause the timer
        self->paused = TRUE;
        
        // Calculated the paused ticks
        self->paused_ticks = SDL_GetTicks() - self->start_ticks;
        self->start_ticks = 0;
    }
    
}

void Timer_Unpause(Timer *self) {
    // If the timer is running and paused
    if (self->started && self->paused) {
        
        // Unpause the timer
        self->paused = FALSE;
        
        // Reset the starting ticks
        self->start_ticks = SDL_GetTicks() - self->paused_ticks;
        
        // Reset the paused ticks
        self->paused_ticks = 0;
    }
}

Uint32 Timer_GetTicks(Timer *self) {
    
    // The actual timer time
    Uint32 time = 0;
    
    // If the timer is running
    if (self->started) {
        // If the timer is paused
        if (self->paused) {
            // Return the number of ticks when the timer was paused
            time = self->paused_ticks;
        } else {
            // Return the current time minus the start time
            time = SDL_GetTicks() - self->start_ticks;
        }
    }
    
    return time;
}

bool Timer_IsStarted(Timer *self) {
    // Timer is running and paused or unpaused
    return self->started;
}

bool Timer_IsPaused(Timer *self) {
    // Timer is running and paused
    return self->paused && self->started;
}

