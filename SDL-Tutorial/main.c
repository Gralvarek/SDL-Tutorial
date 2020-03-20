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
#include "bool.h"
#include "texture.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Function prototypes

// Starts up SDL and creates window
bool InitWindow(void);

// Loads media
bool LoadMedia(void);

// Loads specific surface from path string
SDL_Surface* LoadSurface(char*);

// Loads specific texture from path string
SDL_Texture* LoadTexture(char*);

// Frees media and shuts down SDL
void CloseSDL(void);

// Global variables

// The window we'll be rendering to
SDL_Window* gWindow = NULL;

// The window renderer
SDL_Renderer* gRenderer = NULL;

// Walking animation
Texture* gArrowTexture;


int main(int argc, char* argv[]) {
    
    if (!InitWindow()) {
        printf("Failed to initialize!\n");
    } else {
        
        // Load media
        if (!LoadMedia()) {
            printf("Failed to load media!\n");
        } else {
            
            // Exit button closes window
            bool quit = FALSE;
            
            // Event handler
            SDL_Event event;
            
            // Angle of rotation
            double degrees = 0;
            
            // Flip type
            SDL_RendererFlip flip_type = SDL_FLIP_NONE;
                                    
            // Application loop
            while (!quit) {
                
                // Handle event in queue
                while (SDL_PollEvent(&event) != 0) {
                    if (event.type == SDL_QUIT) {
                        // User requests quit
                        quit = TRUE;
                        
                    } else if (event.type == SDL_KEYDOWN) {
                        switch (event.key.keysym.sym) {
                            case SDLK_a:
                                degrees -= 60;
                                break;
                            
                            case SDLK_o:
                                degrees += 60;
                                break;
                                
                            case SDLK_h:
                                flip_type = SDL_FLIP_HORIZONTAL;
                                break;
                                
                            case SDLK_t:
                                flip_type = SDL_FLIP_NONE;
                                break;
                                
                            case SDLK_n:
                                flip_type = SDL_FLIP_VERTICAL;
                                break;
                        }
                    }
                }
                
                // Clear the screen
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);
                
                // Render current frame
                Texture_Render(gArrowTexture, (SCREEN_WIDTH - Texture_GetWidth(gArrowTexture))/2, (SCREEN_HEIGHT - Texture_GetHeight(gArrowTexture))/2, NULL, degrees, NULL, flip_type);
                
                // Update the surface
                SDL_RenderPresent(gRenderer);
                
                // Sleeps the window
                SDL_Delay(10);
            }
        }
    }
    
    // Free resources and close SDL
    CloseSDL();
    
    return 0;
}

bool InitWindow() {
    
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
            // Create renderer for window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (gRenderer == NULL) {
                printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
                success = FALSE;
            } else {
                // Initialize renderer color
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                
                // Initialize PNG Loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags)) {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = FALSE;
                }
            }
        }
    }
    
    return success;
}

bool LoadMedia() {
    
    // Loading success flag
    bool success = TRUE;
    
    // Load front alpha texture
    gArrowTexture = Texture_New();
    if (Texture_LoadFromFile(gArrowTexture, "arrow.png") == FALSE) {
        printf("Failed to load arrow texture!\n");
        success = FALSE;
    }
    
    return success;
}

void CloseSDL() {
    
    // Free loaded images
    Texture_Destroy(gArrowTexture);
    gArrowTexture = NULL;
    
    // Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = NULL;
    gWindow = NULL;
    
    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}




