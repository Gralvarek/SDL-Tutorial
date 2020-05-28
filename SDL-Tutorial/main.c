//
//  main.c
//  SDL-Tutorial
//
//  Created by Vero on 14.03.20.
//  Copyright © 2020 Asgard Inc. All rights reserved.
//

#include <stdio.h>
#include <string.h>
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
// Global font
TTF_Font *gFont = NULL;
// Input Text Texture
Texture *gInputTextTexture = NULL;
// Prompt Text Texture
Texture *gPromptTextTexture = NULL;





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
    //Loading success flag
    
    //Open the font
    gFont = TTF_OpenFont( "lazy.ttf", 28 );
    if( gFont == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = FALSE;
    }
    else
    {
        //Render the prompt
        SDL_Color textColor = { 0, 0, 0, 0xFF };
        gPromptTextTexture = Texture_New(gRenderer);
        if( !Texture_LoadFromRenderedText(gPromptTextTexture, gFont, "Enter Text:", textColor)) {
            printf( "Failed to render prompt text!\n" );
            success = FALSE;
        }
    }
    

    
    return success;
}


void CloseSDL() {
    
    // Destroy Renderer
    Texture_Destroy(gPromptTextTexture);
    Texture_Destroy(gInputTextTexture);
    gPromptTextTexture = NULL;
    gInputTextTexture = NULL;

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
            
            // Text color
            SDL_Color text_color = {0, 0, 0, 0xFF};
            
            // The current input string
            size_t buffer_size = 64;
            char input_text[buffer_size];
            strcpy(input_text, "Some Text");


            gInputTextTexture = Texture_New(gRenderer);
            Texture_LoadFromRenderedText(gInputTextTexture, gFont, input_text, text_color);
            
            // Enable text input
            SDL_StartTextInput();
            
            // Application loop
            while (!quit) {
                
                boolean render_text = FALSE;
                
                // Handle event in queue
                while (SDL_PollEvent(&event) != 0) {
                    if (event.type == SDL_QUIT) {
                        // User requests quit
                        quit = TRUE;
                        
                    } else if (event.type == SDL_KEYDOWN) {
                        if (event.key.keysym.sym == SDLK_BACKSPACE && strlen(input_text) > 0) {
                            // Handle backspace
                            input_text[strlen(input_text) - 1] = '\0';
                            render_text = TRUE;
                        } else if (event.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL) {
                            // Handle Copy
                            SDL_SetClipboardText(input_text);
                        } else if (event.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL) {
                            // Handle Paste
                            strcpy(input_text, SDL_GetClipboardText());
                            render_text = TRUE;
                        }
                        
                    } else if (event.type == SDL_TEXTINPUT) {
                        // Not copying or pasting
                        if (!(SDL_GetModState() & KMOD_CTRL && (event.text.text[0] == 'c' || event.text.text[0] == 'C' || event.text.text[0] == 'v' || event.text.text[0] == 'V'))) {
                            if (strlen(input_text) < buffer_size) {
                                // Append Character
                                strcat(input_text, event.text.text);
                                render_text = TRUE;
                            } else {
                                printf("Text Buffer is full!\n");
                            }
                        }
                    }
                 
                    //printf("%s", strcmp(input_text, "") ? "true" : "false");
                    // Rerender text if needed
                    if (render_text) {
                    
                        // Text is not empty
                        if (strcmp(input_text, "")) {
                            // Render new text
                            if( !Texture_LoadFromRenderedText(gInputTextTexture, gFont, input_text, text_color)) {
                                printf( "Failed to render input text!\n" );
                            }
                        } else {
                            // Render space texture
                            if( !Texture_LoadFromRenderedText(gInputTextTexture, gFont, " ", text_color)) {
                                printf( "Failed to render empty text!\n" );
                            }
                        }
                    }
                    
                }
                
        
                
                // Clear the screen
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);
                
                // Render text textures
                Texture_Render(gPromptTextTexture, (SCREEN_WIDTH - Texture_GetWidth(gPromptTextTexture)) / 2, 0, NULL, 0.0, NULL, SDL_FLIP_NONE);
                Texture_Render(gInputTextTexture, (SCREEN_WIDTH - Texture_GetWidth(gInputTextTexture)) / 2, Texture_GetHeight(gPromptTextTexture), NULL, 0.0, NULL, SDL_FLIP_NONE);
                
                // Update the surface
                SDL_RenderPresent(gRenderer);
                
            }
            
            // Disable Text Input
            SDL_StopTextInput();
        }
    }
    
    
    
    // Free resources and close SDL
    CloseSDL();
    
    return 0;
}


