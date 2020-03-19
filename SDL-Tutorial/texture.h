//
//  texture.h
//  SDL-Tutorial
//
//  Created by Vero on 18.03.20.
//  Copyright © 2020 Asgard Inc. All rights reserved.
//

#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include "bool.h"


typedef struct _Texture {
    SDL_Texture* texture;
    int width;
    int height;
} Texture;

// Allocator + Constructor
Texture* Texture_New(void);
// Allocates and Initializes member variables
void Texture_Init(Texture* self);

// Deallocator + destructor
void Texture_Destroy(Texture* self);
// Deallocates memory of member variables
void Texture_FreeMembers(Texture* self);

// Loads image at specific path
bool Texture_LoadFromFile(Texture* self, const char* path);

// Set color modulation
void Texture_SetColor(Texture* self, Uint8 red, Uint8 green, Uint8 blue);

// Renders texture at given point
void Texture_Render(Texture* self, int x, int y, SDL_Rect* clip);

// Gets image dimensions
int Texture_GetWidth(Texture* self);
int Texture_GetHeight(Texture* self);

#endif /* TEXTURE_H */
