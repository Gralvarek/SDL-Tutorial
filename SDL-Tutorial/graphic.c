//
//  graphic.c
//  SDL-Tutorial
//
//  Created by Vero on 14.03.20.
//  Copyright © 2020 Asgard Inc. All rights reserved.
//

#include "graphic.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

extern SDL_Window* gWindow;
extern SDL_Surface* gScreenSurface;
extern SDL_Surface* gHelloWorld;


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
