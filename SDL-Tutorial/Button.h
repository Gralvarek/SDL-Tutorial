//
//  Button.h
//  SDL-Tutorial
//
//  Created by Vero on 27.03.20.
//  Copyright © 2020 Asgard Inc. All rights reserved.
//

#ifndef Button_h
#define Button_h

#include <stdio.h>
#include <SDL.h>
#include "Constants.h"
#include "Texture.h"




// Button sprites enum
typedef enum _ButtonSprite {
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 2,
    BUTTON_SPRITE_MOUSE_UP = 3,
    BUTTON_SPRITE_TOTAL = 4
} ButtonSprite;


// Button class


typedef struct _Button {
    SDL_Point postion; // Top left position
    ButtonSprite current_sprite; // Currently used global sprite
} Button;


// Allocator
Button *Button_New(void);
// Initializes member variables (Constructor)
void Button_Init(Button *self);

// Deallocator
void Button_Destroy(Button *self);
// Deinitializes member variables (Destructor)
void Button_DeleteMembers(Button *self);

// Sets top left position
void Button_SetPosition(Button *self, int x, int y);

// Handles mouse event
void Button_HandleEvent(Button *self, SDL_Event* event);

// Show button sprite
void Button_Render(Button *self);




#endif /* Button_h */
