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

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Function prototypes

// Starts up SDL and creates window
bool init_window(void);

// Loads media
bool load_media(void);

// Loads specific surface from path string
SDL_Surface* load_surface(char*);

// Loads specific texture from path string
SDL_Texture* load_texture(char*);

// Frees media and shuts down SDL
void close_sdl(void);

// Global variables

// The window we'll be rendering to
SDL_Window* gWindow = NULL;

// The window renderer
SDL_Renderer* gRenderer = NULL;

// Current displayed texture
SDL_Texture* gTexture = NULL;


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
                
                // Clear the screen
                SDL_RenderClear(gRenderer);
                
                // Top left corner viewport
                SDL_Rect top_left_viewport;
                top_left_viewport.x = 0;
                top_left_viewport.y = 0;
                top_left_viewport.w = SCREEN_WIDTH/2;
                top_left_viewport.h = SCREEN_HEIGHT/2;
                SDL_RenderSetViewport(gRenderer, &top_left_viewport);
                
                // Render texture to screen
                SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
                
                // Top right corner viewport
                SDL_Rect top_right_viewport;
                top_right_viewport.x = SCREEN_WIDTH/2;
                top_right_viewport.y = 0;
                top_right_viewport.w = SCREEN_WIDTH/2;
                top_right_viewport.h = SCREEN_HEIGHT/2;
                SDL_RenderSetViewport(gRenderer, &top_right_viewport);
                
                // Render texture to screen
                SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
                
                // Bottom viewport
                SDL_Rect bottom_viewport;
                bottom_viewport.x = 0;
                bottom_viewport.y = SCREEN_HEIGHT/2;
                bottom_viewport.w = SCREEN_WIDTH;
                bottom_viewport.h = SCREEN_HEIGHT/2;
                SDL_RenderSetViewport(gRenderer, &bottom_viewport);
                
                // Render texture to screen
                SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
                
                // Update the surface
                SDL_RenderPresent(gRenderer);
                
                // Sleeps the window
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
            // Create renderer for window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
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

bool load_media() {
    
    // Loading success flag
    bool success = TRUE;
    
    // Load PNG texture
    
    gTexture = load_texture("viewport.png");
    if (gTexture == NULL) {
        printf("Unable to load PNG image!\n");
        success = FALSE;
    }
    
    return success;
}

SDL_Texture* load_texture(char* path) {
    
    // The final texture
    SDL_Texture* new_texture = NULL;
        
    // Loads image from specific string
    SDL_Surface* loaded_surface = IMG_Load(path);
    if (loaded_surface == NULL) {
        printf("Unable to load image %s! SDL_Error: %s\n", path, IMG_GetError());
    } else {
        // Convert texture from surface pixels
        new_texture = SDL_CreateTextureFromSurface(gRenderer, loaded_surface);
        if (new_texture == NULL) {
            printf("Unable to create texture from %s! SDL_Error: %s\n", path, SDL_GetError());
        }
        
        // Free old loaded surface
        SDL_FreeSurface(loaded_surface);
    }
    return new_texture;
}

/*SDL_Surface* load_surface(char* path) {
    
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
}*/

void close_sdl() {
    
    // Free loaded image
    //SDL_DestroyTexture(gTexture);
    //gTexture = NULL;
    
    // Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = NULL;
    gWindow = NULL;
    
    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}


