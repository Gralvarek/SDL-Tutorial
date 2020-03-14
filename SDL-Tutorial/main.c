//
//  main.c
//  fourier-drawing
//
//  Created by Vero on 14.03.20.
//  Copyright © 2020 Asgard Inc. All rights reserved.
//

#include <stdio.h>
#include <SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

typedef enum {FALSE = 0 , TRUE = 1} bool;

// Function prototypes

// Starts up SDL and creates window
bool init(void);

// Loads media
bool load_media(void);

// Frees media and shuts down SDL
void close_sdl(void);

// Global variables

// The window we'll be rendering to
SDL_Window* gWindow = NULL;

// The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

// The image we will load and show on the screen
SDL_Surface* gHelloWorld = NULL;



int main(int argc, char* argv[]) {
    
    // The window we'll be rendering to
    SDL_Window* window = NULL;
    
    // The surface contained by the window
    SDL_Surface* screen_surface = NULL;
    
    
    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not be initialize! SDL_Error: %s\n", SDL_GetError());
    } else {
        // Create window
        window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if(window == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        } else {
            // Get window surface
            screen_surface = SDL_GetWindowSurface(window);
            
            // Fill the surface white
            SDL_FillRect(screen_surface, NULL, SDL_MapRGB(screen_surface->format, 0xFF, 0xFF, 0xFF));
            
            // Update the surface
            SDL_UpdateWindowSurface(window);
            
            // Blocks window from closing
            int is_running = TRUE;
            SDL_Event event;
            while (is_running) {
                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) {
                        is_running = FALSE;
                    }
                }
                SDL_Delay(16);
            }

        }
    }
    
    // Destroy window
    SDL_DestroyWindow(window);
    
    // Quit SDL subsystems
    SDL_Quit();
    
    return 0;
}
