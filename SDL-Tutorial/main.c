//
//  main.c
//  SDL-Tutorial
//
//  Created by Vero on 14.03.20.
//  Copyright © 2020 Asgard Inc. All rights reserved.
//

#include <stdio.h>
#include <SDL.h>

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

enum KeyPressSurface{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


// The window we'll be rendering to
SDL_Window* gWindow = NULL;

// The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

// The images that correspond to key presses
SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

// Current displayed image
SDL_Surface* gCurrentSurface = NULL;


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
            
            // Sets default current surface
            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
            
            // Application loop
            while (!quit) {
                
                // Handle event in queue
                while (SDL_PollEvent(&event)) {
                    
                    if (event.type == SDL_QUIT) {
                        // User requests quit
                        quit = TRUE;
                    } else if (event.type == SDL_KEYDOWN) {
                        // User presses key
                        
                        switch (event.key.keysym.sym) {
                            case SDLK_UP:
                                gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
                                break;
                            case SDLK_DOWN:
                                gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
                                break;
                            case SDLK_LEFT:
                                gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
                                break;
                            case SDLK_RIGHT:
                                gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
                                break;
                            default:
                                gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
                                break;
                        }
                    }
                    
                }
                
                
                // Apply the image
                SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);
                
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
            // Get window surface
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }
    
    return success;
}

bool load_media() {
    
    // Loading success flag
    bool success = TRUE;
    
    // Load default image
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = load_surface("press.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
        printf("Unable to load default image!\n");
        success = FALSE;
    }
    
    // Load default image
    gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = load_surface("up.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL) {
        printf("Unable to load up image!\n");
        success = FALSE;
    }
    
    // Load default image
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = load_surface("down.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL) {
        printf("Unable to load down image!\n");
        success = FALSE;
    }
    
    // Load default image
    gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = load_surface("left.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL) {
        printf("Unable to load left image!\n");
        success = FALSE;
    }
    
    // Load default image
    gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = load_surface("right.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL) {
        printf("Unable to load right image!\n");
        success = FALSE;
    }
    
    return success;
}

SDL_Surface* load_surface(char* path) {
        
    // Loads image from specific string
    SDL_Surface* loaded_surface = SDL_LoadBMP(path);
    if (loaded_surface == NULL) {
        printf("Unable to load image %s! SDL_Error: %s\n", path, SDL_GetError());
    }
    return loaded_surface;
}

void close_sdl() {
    
    // Deallocate surface
    for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i) {
        SDL_FreeSurface(gKeyPressSurfaces[i]);
        gKeyPressSurfaces[i] = NULL;
    }
    // Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    
    // Quit SDL subsystems
    SDL_Quit();
}


