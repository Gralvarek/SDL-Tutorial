//
//  main.c
//  SDL-Tutorial
//
//  Created by Vero on 14.03.20.
//  Copyright © 2020 Asgard Inc. All rights reserved.
//

#include <stdio.h>
#include <SDL.h>
#include "graphic.h"



// Global variables

// The window we'll be rendering to
SDL_Window* gWindow = NULL;

// The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

// The image we will load and show on the screen
SDL_Surface* gXOut = NULL;



int main(int argc, char* argv[]) {
    
  
    if(!init()) {
        printf("Failed to initialize!\n");
    } else {
        // Load media
        if(!load_media()) {
            printf("Failed to load media!\n");
        } else {
            // Exit button closes window
            bool quit = FALSE;
            SDL_Event event;
            while (!quit) {
                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) {
                        quit = TRUE;
                    }
                }
                
                
                // Apply the image
                SDL_BlitSurface(gXOut, NULL, gScreenSurface, NULL);
                
                // Update the surface
                SDL_UpdateWindowSurface(gWindow);
                
                // Sleeps the CPU
                SDL_Delay(16);
            }
        }
    }
    
    // Free resources and close SDL
    close_sdl();
    
    return 0;
}



