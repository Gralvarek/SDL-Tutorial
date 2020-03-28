//
//  Button.c
//  SDL-Tutorial
//
//  Created by Vero on 27.03.20.
//  Copyright © 2020 Asgard Inc. All rights reserved.
//

#include "Button.h"



// Button function definitions


Button *Button_New() {
    Button *self = (Button*) malloc(sizeof(Button));
    Button_Init(self);
    return self;
}

void Button_Init(Button *self) {
    self->postion.x = 0;
    self->postion.y = 0;
    self->current_sprite = BUTTON_SPRITE_MOUSE_OUT;
}

void Button_Destroy(Button *self) {
    if (self != NULL) {
        Button_DeleteMembers(self);
        free(self);
    }
}

void Button_DeleteMembers(Button *self) {
    self->postion.x = 0;
    self->postion.y = 0;
    self->current_sprite = BUTTON_SPRITE_MOUSE_OUT;
}

void Button_SetPostion(Button *self, int x, int y) {
    self->postion.x = x;
    self->postion.y = y;
}

void Button_HandleEvent(Button *self, SDL_Event *event) {
    
    // If mouse event happened
    if (event->type == SDL_MOUSEMOTION || event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP) {
        
        // Get mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);
        
        // Check if mouse is inside button
        bool inside = TRUE;
        if (x < self->postion.x) {
            // Mouse is left of the button
            inside = FALSE;
            
        } else if (x > self->postion.x + BUTTON_WIDTH) {
            // Mouse is right of the button
            inside = FALSE;
            
        } else if (y < self->postion.y) {
            // Mouse is above the button
            inside = FALSE;
            
        } else if (y > self->postion.y + BUTTON_HEIGHT) {
            // Mouse is below the button
            inside = FALSE;
            
        }
        
        if (!inside) {
            self->current_sprite = BUTTON_SPRITE_MOUSE_OUT;
        } else {
            // Mouse is inside button
            
            // Set mouse over sprite
            switch (event->type) {
                case SDL_MOUSEMOTION:
                    self->current_sprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                    break;
                
                case SDL_MOUSEBUTTONDOWN:
                    self->current_sprite = BUTTON_SPRITE_MOUSE_DOWN;
                    break;
                
                case SDL_MOUSEBUTTONUP:
                    self->current_sprite = BUTTON_SPRITE_MOUSE_UP;
                    break;
            }
        }
    }
}
/**
void Button_Render(Button *self, Texture *button_texture) {
    // Show current button sprite
    Texture_Render(button_texture, self->postion.x, self->postion.y, &gSpriteClips[self->current_sprite], 0.0, NULL, SDL_FLIP_NONE);
}
**/


