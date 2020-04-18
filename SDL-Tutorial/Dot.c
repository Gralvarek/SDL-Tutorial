//
//  Dot.c
//  SDL-Tutorial
//
//  Created by Vero on 27.03.20.
//  Copyright © 2020 Asgard Inc. All rights reserved.
//

#include "Dot.h"


// The dimensions of the dot
const int DOT_WIDTH = 20;
const int DOT_HEIGHT = 20;

// Maximum axis velocity of the dot
const int DOT_VEL = 10;


// Dot function definitions

Dot *Dot_New(int x, int y) {
    Dot *self = (Dot *)malloc(sizeof(Dot));
    Dot_Init(self, x, y);
    return self;
}

void Dot_Init(Dot *self, int x, int y) {
    
    // Initialize the offsets
    self->pos_x = x;
    self->pos_y = y;
    
    // Initialize the velocity
    self->vel_x = 0;
    self->vel_y = 0;
    
}

void Dot_Destroy(Dot *self) {
    if (self != NULL) {
        Dot_DeleteMembers(self);
        free(self);
    }
}

void Dot_DeleteMembers(Dot *self) {
    self->pos_x = 0;
    self->pos_y = 0;
    
    self->vel_x = 0;
    self->vel_y = 0;
}

void Dot_HandleEvent(Dot *self, SDL_Event *event) {
    
    // If a key is pressed
    if (event->type == SDL_KEYDOWN && event->key.repeat == 0) {
        
        // Adjust the velocity
        switch (event->key.keysym.sym) {
            case SDLK_UP:
                self->vel_y -= DOT_VEL;
                break;
            
            case SDLK_DOWN:
                self->vel_y += DOT_VEL;
                break;
                
            case SDLK_LEFT:
                self->vel_x -= DOT_VEL;
                break;
            
            case SDLK_RIGHT:
                self->vel_x += DOT_VEL;
                break;
        }
    } else if (event->type == SDL_KEYUP && event->key.repeat == 0) {
        
        // Adjust the velocity
        // I might be able to simply just set all these values to 0
        switch (event->key.keysym.sym) {
            case SDLK_UP:
                self->vel_y += DOT_VEL;
                break;
            
            case SDLK_DOWN:
                self->vel_y -= DOT_VEL;
                break;
                
            case SDLK_LEFT:
                self->vel_x += DOT_VEL;
                break;
            
            case SDLK_RIGHT:
                self->vel_x -= DOT_VEL;
                break;
        }
    }
}


void Dot_Move(Dot *self) {
    
    // Move the dot to the left or right
    self->pos_x += self->vel_x;
    
    // If the dot went too far to the left or the right
    if ((self->pos_x < 0) || (self->pos_x + DOT_WIDTH > SCREEN_WIDTH)) {
        // Move back
        self->pos_x -= self->vel_x;
    }
    
    
    // Move the dot up or down
    self->pos_y += self->vel_y;
    
    // If the dot went too far up or down
    if ((self->pos_y < 0) || (self->pos_y + DOT_HEIGHT > SCREEN_HEIGHT)) {
        // Move back
        self->pos_y -= self->vel_y;
    }
}

void Dot_Render(Dot *self, Texture * dot_texture/*, int camX, int camY*/) {
    // Show the dot
    Texture_Render(dot_texture, self->pos_x /*- camX*/, self->pos_y /*- camY*/, NULL, 0.0, NULL, SDL_FLIP_NONE);
}
