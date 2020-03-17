//
//  main.c
//  SDL-Tutorial
//
//  Created by Vero on 14.03.20.
//  Copyright © 2020 Asgard Inc. All rights reserved.
//

#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <string.h>

typedef enum {FALSE = 0 , TRUE = 1} bool;

// Function prototypes

// Starts up SDL and creates window
bool init_window(void);

// Loads media
bool load_media(void);

// Loads specific surface from path string
SDL_Surface* load_surface(char*);

// Frees media and shuts down SDL
void close_sdl(void);


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


// The window we'll be rendering to
SDL_Window* gWindow = NULL;

// The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

// Current displayed PNG image
SDL_Surface* gPNGSurface = NULL;


int main(int argc, char* argv[]) {
    
    if (!init_window()) {
        printf("Failed to initialize!\n");
    } else {
        
        // Load media
        if (!load_media()) {
            printf("Failed to load media!\n");
        } else {
            
            // Exit button closes window
            bool quit = FALSE;
            
            // Event handler
            SDL_Event event;
                                    
            // Application loop
            while (!quit) {
                
                // Handle event in queue
                while (SDL_PollEvent(&event)) {
                    
                    if (event.type == SDL_QUIT) {
                        // User requests quit
                        quit = TRUE;
                    }
                    
                }
                
                
                // Apply the image
                SDL_BlitSurface(gPNGSurface, NULL, gScreenSurface, NULL);
                
                // Update the surface
                SDL_UpdateWindowSurface(gWindow);
                
                // Sleeps the CPU
                SDL_Delay(10);
            }
        }
    }
    
    // Free resources and close SDL
    close_sdl();
    
    return 0;
}

bool init_window() {
    
    // Initialization flag
    bool success = TRUE;
    
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not be initialize! SDL_Error: %s\n", SDL_GetError());
        success = FALSE;
    } else {
        // Create window
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = FALSE;
        } else {
            // Initialize PNG Loading
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) & imgFlags)) {
                printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                success = FALSE;
            } else {
                // Get window surface
                gScreenSurface = SDL_GetWindowSurface(gWindow);
            }
        }
    }
    
    return success;
}

bool load_media() {
    
    // Loading success flag
    bool success = TRUE;
    
    // Load default image
    gPNGSurface = load_surface("loaded.png");
    if (gPNGSurface == NULL) {
        printf("Unable to load PNG image!\n");
        success = FALSE;
    }
    
    return success;
}

SDL_Surface* load_surface(char* path) {
    
    // optimized image to return
    SDL_Surface* optimized_surface = NULL;
        
    // Loads image from specific string
    SDL_Surface* loaded_surface = IMG_Load(path);
    if (loaded_surface == NULL) {
        printf("Unable to load image %s! SDL_Error: %s\n", path, IMG_GetError());
    } else {
        // Convert surface to screen format
        optimized_surface = SDL_ConvertSurface(loaded_surface, gScreenSurface->format, 0);
        if (optimized_surface == NULL) {
            printf("Unable to optimize image %s! SDL_Error: %s\n", path, SDL_GetError());
        }
        
        // Free old loaded surface
        SDL_FreeSurface(loaded_surface);
    }
    return optimized_surface;
}

void close_sdl() {
    
    // Free loaded image
    SDL_FreeSurface(gPNGSurface);
    gPNGSurface = NULL;
    
    // Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    
    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}


