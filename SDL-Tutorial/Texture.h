//
//  Texture.h
//  SDL-Tutorial
//
//  Created by Vero on 27.03.20.
//  Copyright © 2020 Asgard Inc. All rights reserved.
//

#ifndef Texture_h
#define Texture_h

#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "Constants.h"


// Texture class
/**
typedef struct _Texture {
    SDL_Texture *texture; // The actual hardware texture
    int width; // Image width
    int height; // Image height
    SDL_Renderer *renderer; // Renderer
} Texture;
**/
typedef struct _Texture Texture;

// Allocator
Texture *Texture_New(SDL_Renderer *);
// Initializes member variables (Constructor), allocates SDL_Texture
void Texture_Init(Texture *self, SDL_Renderer *);

// Deallocator
void Texture_Destroy(Texture *self);
// Deinitializes member variables (Destructor), deallocates SDL_Texture
void Texture_DeleteMembers(Texture *self);


// Loads image at specific path
boolean Texture_LoadFromFile(Texture *self, const char* path);
//#if defined(_SDL_TTF_H) || defined(SDL_TTF_H)
// Creates image from font string
boolean Texture_LoadFromRenderedText(Texture *self, TTF_Font *font, const char* texture_text, SDL_Color text_color);
//#endif

// Set color modulation
void Texture_SetColor(Texture *self, Uint8 red, Uint8 green, Uint8 blue);
// Set blending
void Texture_SetBlendMode(Texture *self, SDL_BlendMode blending);
// Set alpha modulation
void Texture_SetAlpha(Texture *self, Uint8 alpha);


// Renders texture at given point
void Texture_Render(Texture *self, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip);

// Gets image dimensions
int Texture_GetWidth(Texture *self);
int Texture_GetHeight(Texture *self);


#endif /* Texture_h */
