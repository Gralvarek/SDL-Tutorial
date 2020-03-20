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
#include <SDL_ttf.h>
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

// Globally used font
TTF_Font* gFont = NULL;

// Walking animation
Texture* gTextTexture = NULL;


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
                                    
            // Application loop
            while (!quit) {
                
                // Handle event in queue
                while (SDL_PollEvent(&event) != 0) {
                    if (event.type == SDL_QUIT) {
                        // User requests quit
                        quit = TRUE;
                        
                    }
                }
                
                // Clear the screen
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);
                
                // Render current frame
                Texture_Render(gTextTexture, (SCREEN_WIDTH - Texture_GetWidth(gTextTexture))/2, (SCREEN_HEIGHT - Texture_GetHeight(gTextTexture))/2, NULL, 0.0, NULL, SDL_FLIP_NONE);
                
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
                
                // Initialize SDL_ttf
                if (TTF_Init() == -1) {
                    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
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
    
    // Open the font
    gFont = TTF_OpenFont("lazy.ttf", 28);
    if (gFont == NULL) {
        printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
        success = FALSE;
    } else {
        
        // Render text
        SDL_Color text_color = {0, 0, 0};
        gTextTexture = Texture_New();
        if (!Texture_LoadFromRenderedText(gTextTexture, "The quick brown fox jumps over the lazy dog", text_color)) {
            printf("Failed to render text texture!\n");
            success = FALSE;
        }
    }
    return success;
}

void CloseSDL() {
    
    // Free loaded images
    Texture_Destroy(gTextTexture);
    gTextTexture = NULL;
    
    // Free global font
    TTF_CloseFont(gFont);
    gFont = NULL;
    
    // Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = NULL;
    gWindow = NULL;
    
    // Quit SDL subsystems
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}




