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
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "CheckCollision.h"
#include "Constants.h"
#include "Dot.h"
#include "Texture.h"
#include "Timer.h"
#include "Button.h"




// Function prototypes

// Starts up SDL and creates window
boolean InitWindow(void);
// Loads media
boolean LoadMedia(void);
// Frees media and shuts down SDL
void CloseSDL(void);


// Global variables

// The window we'll be rendering to
SDL_Window *gWindow = NULL;
// The window renderer
SDL_Renderer *gRenderer = NULL;
// Dot texture
Texture *gDotTexture = NULL;
// Background texture
Texture *gBGTexture = NULL;


boolean InitWindow() {
    
    // Initialization flag
    boolean success = TRUE;
    
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
                    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                    success = FALSE;
                }
            }
        }
    }
    
    return success;
}


boolean LoadMedia() {
    
    // Loading success flag
    boolean success = TRUE;
    
    // Load the dot texture
    gDotTexture = Texture_New(gRenderer);
    if (!Texture_LoadFromFile(gDotTexture, "dot.bmp")) {
        printf("Unable to render dot texture!\n");
        success = FALSE;
    }
    
    // Load the BG texture
    gBGTexture = Texture_New(gRenderer);
    if (!Texture_LoadFromFile(gBGTexture, "bg.png")) {
        printf("Unable to render BG texture!\n");
        success = FALSE;
    }
    
    return success;
}


void CloseSDL() {
    
    // Free loaded images
    Texture_Destroy(gDotTexture);
    gDotTexture = NULL;
    
    // Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = NULL;
    gWindow = NULL;
    
    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}


int main(int argc, char* argv[]) {
    
    if (!InitWindow()) {
        printf("Failed to initialize!\n");
    } else {
        
        // Load media
        if (!LoadMedia()) {
            printf("Failed to load media!\n");
        } else {
            
            // Exit button closes window
            boolean quit = FALSE;
            
            // Event handler
            SDL_Event event;
            
            // The dot that will be moving around on the screen
            Dot dot;
            Dot_Init(&dot, DOT_WIDTH/2, DOT_HEIGHT/2);

            // The background scrolling offset
            int scrolling_offset = 0;
            
            // Application loop
            while (!quit) {
                
                // Handle event in queue
                while (SDL_PollEvent(&event) != 0) {
                    if (event.type == SDL_QUIT) {
                        // User requests quit
                        quit = TRUE;
                        
                    }
                    
                    // Handle input for the dot
                    Dot_HandleEvent(&dot, &event);
                }
                
                // Move the dot
                Dot_Move(&dot);
                
                // Scroll background
                --scrolling_offset;
                if (scrolling_offset < -Texture_GetWidth(gBGTexture)) {
                    scrolling_offset = 0;
                }
                
                
                // Clear the screen
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);
                
                // Render background
                Texture_Render(gBGTexture, scrolling_offset, 0, NULL, 0.0, NULL, SDL_FLIP_NONE);
                Texture_Render(gBGTexture, scrolling_offset + Texture_GetWidth(gBGTexture), 0, NULL, 0.0, NULL, SDL_FLIP_NONE);

                
                // Render dot
                Dot_Render(&dot, gDotTexture);
                
                // Update the surface
                SDL_RenderPresent(gRenderer);
            }
        }
    }
    
    
    
    // Free resources and close SDL
    CloseSDL();
    
    return 0;
}


