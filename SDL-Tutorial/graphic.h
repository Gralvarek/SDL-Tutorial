//
//  graphic.h
//  fourier-drawing
//
//  Created by Vero on 14.03.20.
//  Copyright © 2020 Asgard Inc. All rights reserved.
//

#ifndef graphic_h
#define graphic_h

#include <stdio.h>
#include <SDL.h>

typedef enum {FALSE = 0 , TRUE = 1} bool;



// Function prototypes

// Starts up SDL and creates window
bool init(void);

// Loads media
bool load_media(void);

// Frees media and shuts down SDL
void close_sdl(void);

#endif /* graphic_h */
