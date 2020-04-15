//
//  Dot.h
//  SDL-Tutorial
//
//  Created by Vero on 27.03.20.
//  Copyright © 2020 Asgard Inc. All rights reserved.
//

#ifndef Dot_h
#define Dot_h

#include <stdio.h>
#include "Circle.h"
#include <SDL.h>
#include "CheckCollision.h"
#include "Constants.h"
#include "Texture.h"


// Dot class


typedef struct _Dot {
    int pos_x, pos_y;
    int vel_x, vel_y;
} Dot;


// Allocator
Dot *Dot_New(int, int);
// Initializes member variables (Constructor)
void Dot_Init(Dot *self, int, int);

// Deallocator
void Dot_Destroy(Dot *self);
// Deinitializes member variables (Destructor)
void Dot_DeleteMembers(Dot *self);

void Dot_HandleEvent(Dot *self, SDL_Event *event);
void Dot_Move(Dot *self);
void Dot_Render(Dot *self, Texture *, int camX, int camY);


// The dimensions of the dot
extern const int DOT_WIDTH;
extern const int DOT_HEIGHT;

// Maximum axis velocity of the dot
extern const int DOT_VEL;


#endif /* Dot_h */
