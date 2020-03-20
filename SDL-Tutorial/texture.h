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
#include <SDL_ttf.h>
#include "bool.h"


typedef struct _Texture {
    SDL_Texture* texture; // The actual hardware texture
    int width; // Image width
    int height; // Image height
} Texture;

// Allocator
Texture* Texture_New(void);
// Initializes member variables (Constructor)
void Texture_Init(Texture* self);

// Deallocator
void Texture_Destroy(Texture* self);
// Deinitializes member variables (Destructor), also deallocates SDL_Texture
void Texture_DeleteMembers(Texture* self);


// Loads image at specific path
bool Texture_LoadFromFile(Texture* self, const char* path);
// Creates image from font string
bool Texture_LoadFromRenderedText(Texture* self, const char* texture_text, SDL_Color text_color);


// Set color modulation
void Texture_SetColor(Texture* self, Uint8 red, Uint8 green, Uint8 blue);
// Set blending
void Texture_SetBlendMode(Texture* self, SDL_BlendMode blending);
// Set alpha modulation
void Texture_SetAlpha(Texture* self, Uint8 alpha);


// Renders texture at given point
void Texture_Render(Texture* self, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip);

// Gets image dimensions
int Texture_GetWidth(Texture* self);
int Texture_GetHeight(Texture* self);

#endif /* TEXTURE_H */
