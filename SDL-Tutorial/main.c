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
    
    if(!init()) {
        printf("Failed to initialize!\n");
    } else {
        // Load media
        if(!load_media()) {
            printf("Failed to load media!\n");
        } else {
            // Apply the image
            SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
            
            // Update the surface
            SDL_UpdateWindowSurface(gWindow);
            
            bool is_running = TRUE;
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
    
    // Free resources and close SDL
    close_sdl();
    
    return 0;
}


bool init() {
    
    // Initialization flag
    bool success = TRUE;
    
    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not be initialize! SDL_Error: %s\n", SDL_GetError());
        success = FALSE;
    } else {
        // Create window
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(gWindow == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = FALSE;
        } else {
            // Get window surface
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }
    
    return success;
}

bool load_media() {
    
    // Loading success flag
    bool success = TRUE;
    
    // Load splash image
    gHelloWorld = SDL_LoadBMP("hello_world.bmp");
    if(gHelloWorld == NULL) {
        printf("Unable to load image %s! SDL_Error: %s\n", "hello_world.bmp", SDL_GetError());
        success = FALSE;
    }
    
    return success;
}

void close_sdl() {
    
    // Deallocate surface
    SDL_FreeSurface(gHelloWorld);
    gHelloWorld = NULL;
    
    // Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    
    // Quit SDL subsystems
    SDL_Quit();
}
