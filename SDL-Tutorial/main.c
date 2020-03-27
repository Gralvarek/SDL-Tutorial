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

typedef enum {FALSE = 0 , TRUE = 1} bool;

// Screen constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Button constants
const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;
const int TOTAL_BUTTONS = 4;

typedef enum _ButtonSprite {
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 2,
    BUTTON_SPRITE_MOUSE_UP = 3,
    BUTTON_SPRITE_TOTAL = 4
} ButtonSprite;







// Texture class

// Hide this when adapting to multi file program
typedef struct _Texture {
    SDL_Texture *texture; // The actual hardware texture
    int width; // Image width
    int height; // Image height
} Texture;

// Allocator
Texture *Texture_New(void);
// Initializes member variables (Constructor), allocates SDL_Texture
void Texture_Init(Texture *self);

// Deallocator
void Texture_Destroy(Texture *self);
// Deinitializes member variables (Destructor), deallocates SDL_Texture
void Texture_DeleteMembers(Texture *self);


// Loads image at specific path
bool Texture_LoadFromFile(Texture *self, const char* path);
//#if defined(_SDL_TTF_H) || defined(SDL_TTF_H)
// Creates image from font string
bool Texture_LoadFromRenderedText(Texture *self, const char* texture_text, SDL_Color text_color);
//#endif

// Set color modulation
void Texture_SetColor(Texture *self, Uint8 red, Uint8 green, Uint8 blue);
// Set blending
void Texture_SetBlendMode(Texture *self, SDL_BlendMode blending);
// Set alpha modulation
void Texture_SetAlpha(Texture *self, Uint8 alpha);


// Renders texture at given point
void Texture_Render(Texture *self, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip);

// Gets image dimensions
int Texture_GetWidth(Texture *self);
int Texture_GetHeight(Texture *self);






// Button class
/**
// Hide this when adapting to multi file program
typedef struct _Button {
    SDL_Point postion; // Top left position
    ButtonSprite current_sprite; // Currently used global sprite
} Button;

// Allocator
Button *Button_New(void);
// Initializes member variables (Constructor)
void Button_Init(Button *self);

// Deallocator
void Button_Destroy(Button *self);
// Deinitializes member variables (Destructor)
void Button_DeleteMembers(Button *self);

// Sets top left position
void Button_SetPosition(Button *self, int x, int y);

// Handles mouse event
void Button_HandleEvent(Button *self, SDL_Event* event);

// Show button sprite
void Button_Render(Button *self);
**/






// Timer class

typedef struct _Timer {
    Uint32 start_ticks; // The clock timer when the timer started
    Uint32 paused_ticks; // The ticks stored when the timer was paused
    bool paused; // The timer status
    bool started;
} Timer;


Timer *Timer_New(void);
void Timer_Init(Timer *self);

void Timer_Destroy(Timer *self);
void Timer_DeleteMembers(Timer *self);

void Timer_Start(Timer *self);
void Timer_Stop(Timer *self);
void Timer_Pause(Timer *self);
void Timer_Unpause(Timer *self);

Uint32 Timer_GetTicks(Timer *self);

bool Timer_IsStarted(Timer *self);
bool Timer_IsPaused(Timer *self);








// Dot class

typedef struct _Dot {
    int pos_x, pos_y;
    int vel_x, vel_y;
} Dot;

// The dimensions of the dot
static const int DOT_WIDTH = 20;
static const int DOT_HEIGHT = 20;

// Maximum axis velocity of the dot
static const int DOT_VEL = 10;


Dot *Dot_New(void);
void Dot_Init(Dot *self);

void Dot_Destroy(Dot *self);
void Dot_DeleteMembers(Dot *self);

void Dot_HandleEvent(Dot *self, SDL_Event *event);
void Dot_Move(Dot *self);
void Dot_Render(Dot *self);







// Function prototypes

// Starts up SDL and creates window
bool InitWindow(void);
// Loads media
bool LoadMedia(void);
// Frees media and shuts down SDL
void CloseSDL(void);

// Global variables

// The window we'll be rendering to
SDL_Window *gWindow = NULL;

// The window renderer
SDL_Renderer *gRenderer = NULL;

// Time text texture
Texture *gDotTexture = NULL;

// Global font
TTF_Font* gFont = NULL;










// Texture function definitions


Texture *Texture_New() {
    Texture *self = (Texture *) malloc(sizeof(Texture));
    Texture_Init(self);
    return self;
}

void Texture_Init(Texture *self) {
    self->texture = NULL;
    self->width = 0;
    self->height = 0;
}

void Texture_Destroy(Texture *self) {
    if (self != NULL) {
        Texture_DeleteMembers(self);
        free(self);
    }
}

void Texture_DeleteMembers(Texture *self) {
    if (self->texture != NULL) {
        SDL_DestroyTexture(self->texture);
        self->texture = NULL;
        self->width = 0;
        self->height = 0;
    }
}
    
bool Texture_LoadFromFile(Texture *self, const char *path) {
    
    // Get rid of preexisting texture
    Texture_DeleteMembers(self);
    
    // The final texture
    SDL_Texture * new_texture = NULL;
    
    // Load image at specific path
    SDL_Surface * loaded_surface = IMG_Load(path);
    if (loaded_surface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
    } else {
        
        // Color key image
        SDL_SetColorKey(loaded_surface, SDL_TRUE, SDL_MapRGB(loaded_surface->format, 0x00, 0xFF, 0xFF));
        
        // Create new texture from surface pixels
        new_texture = SDL_CreateTextureFromSurface(gRenderer, loaded_surface);
        if (new_texture == NULL) {
            printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
        } else {
            
            // Get image dimensions
            self->width = loaded_surface->w;
            self->height = loaded_surface->h;
        }
        
        // Get rid of old loaded surface
        SDL_FreeSurface(loaded_surface);
    }
    
    // Return success
    self->texture = new_texture;
    return self->texture != NULL;
}

//#if defined(_SDL_TTF_H) || defined(SDL_TTF_H)
bool Texture_LoadFromRenderedText(Texture *self, const char *texture_text, SDL_Color text_color) {
    
    // Get rid of preexisting texture
    Texture_DeleteMembers(self);
    
    // Render text surface
    SDL_Surface * text_surface = TTF_RenderText_Solid(gFont, texture_text, text_color);
    if (text_surface == NULL) {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    } else {
        
        // Create texture from surface pixels
        self->texture = SDL_CreateTextureFromSurface(gRenderer, text_surface);
        if (self->texture == NULL) {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        } else {
            
            // Get image dimensions
            self->width = text_surface->w;
            self->height = text_surface->h;
        }
        
        // Get rid of old surface
        SDL_FreeSurface(text_surface);
    }
    
    return self->texture != NULL;
}
//#endif

void Texture_SetColor(Texture *self, Uint8 red, Uint8 green, Uint8 blue) {
    // Modulate texture
    SDL_SetTextureColorMod(self->texture, red, green, blue);
}

void Texture_SetBlendMode(Texture *self, SDL_BlendMode blending) {
    SDL_SetTextureBlendMode(self->texture, blending);
}

void Texture_SetAlpha(Texture *self, Uint8 alpha) {
    SDL_SetTextureAlphaMod(self->texture, alpha);
}

void Texture_Render(Texture *self, int x, int y, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip) {
    
    // Set rendering space and render to screen
    SDL_Rect render_quad = {x, y, self->width, self->height};
    
    // Set clip rendering dimensions
    if (clip != NULL) {
        render_quad.w = clip->w;
        render_quad.h = clip->h;
    }
    
    SDL_RenderCopyEx(gRenderer, self->texture, clip, &render_quad, angle, center, flip);
}

int Texture_GetWidth(Texture *self) {
    return self->width;
}

int Texture_GetHeight(Texture *self) {
    return self->height;
}
    



// Button function definitions
/**

Button *Button_New() {
    Button *self = (Button*) malloc(sizeof(Button));
    Button_Init(self);
    return self;
}

void Button_Init(Button *self) {
    self->postion.x = 0;
    self->postion.y = 0;
    self->current_sprite = BUTTON_SPRITE_MOUSE_OUT;
}

void Button_Destroy(Button *self) {
    if (self != NULL) {
        Button_DeleteMembers(self);
        free(self);
    }
}

void Button_DeleteMembers(Button *self) {
    self->postion.x = 0;
    self->postion.y = 0;
    self->current_sprite = BUTTON_SPRITE_MOUSE_OUT;
}

void Button_SetPostion(Button *self, int x, int y) {
    self->postion.x = x;
    self->postion.y = y;
}

void Button_HandleEvent(Button *self, SDL_Event *event) {
    
    // If mouse event happened
    if (event->type == SDL_MOUSEMOTION || event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP) {
        
        // Get mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);
        
        // Check if mouse is inside button
        bool inside = TRUE;
        if (x < self->postion.x) {
            // Mouse is left of the button
            inside = FALSE;
            
        } else if (x > self->postion.x + BUTTON_WIDTH) {
            // Mouse is right of the button
            inside = FALSE;
            
        } else if (y < self->postion.y) {
            // Mouse is above the button
            inside = FALSE;
            
        } else if (y > self->postion.y + BUTTON_HEIGHT) {
            // Mouse is below the button
            inside = FALSE;
            
        }
        
        if (!inside) {
            self->current_sprite = BUTTON_SPRITE_MOUSE_OUT;
        } else {
            // Mouse is inside button
            
            // Set mouse over sprite
            switch (event->type) {
                case SDL_MOUSEMOTION:
                    self->current_sprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                    break;
                
                case SDL_MOUSEBUTTONDOWN:
                    self->current_sprite = BUTTON_SPRITE_MOUSE_DOWN;
                    break;
                
                case SDL_MOUSEBUTTONUP:
                    self->current_sprite = BUTTON_SPRITE_MOUSE_UP;
                    break;
            }
        }
    }
}

void Button_Render(Button *self) {
    // Show current button sprite
    Texture_Render(gButtonSpriteSheetTexture, self->postion.x, self->postion.y, &gSpriteClips[self->current_sprite], 0.0, NULL, SDL_FLIP_NONE);
}


**/

// Timer function definitions


Timer *Timer_New() {
    Timer *self = (Timer *)malloc(sizeof(Timer));
    Timer_Init(self);
    return self;
}


void Timer_Init(Timer *self) {
    self->start_ticks = 0;
    self->paused_ticks = 0;
    self->started = FALSE;
    self->paused = FALSE;
}

void Timer_Destroy(Timer *self) {
    if (self != NULL) {
        Timer_DeleteMembers(self);
        free(self);
    }
}

void Timer_DeleteMembers(Timer *self) {
    self->start_ticks = 0;
    self->paused_ticks = 0;
    self->started = FALSE;
    self->paused = FALSE;
}


void Timer_Start(Timer *self) {
    // Start the timer
    self->started = TRUE;
    
    // Unpause the timer
    self->paused = FALSE;
    
    // Get the current clock time
    self->start_ticks = SDL_GetTicks();
    self->paused_ticks = 0;
}

void Timer_Stop(Timer *self) {
    // Stop the timer
    self->started = FALSE;
    
    // Unpause the timer
    self->paused = FALSE;
    
    // Clear the tick variables
    self->start_ticks = 0;
    self->paused_ticks = 0;
}

void Timer_Pause(Timer *self) {
    // If the timer is running and isn't paused
    if (self->started && !self->paused) {
        
        // Pause the timer
        self->paused = TRUE;
        
        // Calculated the paused ticks
        self->paused_ticks = SDL_GetTicks() - self->start_ticks;
        self->start_ticks = 0;
    }
    
}

void Timer_Unpause(Timer *self) {
    // If the timer is running and paused
    if (self->started && self->paused) {
        
        // Unpause the timer
        self->paused = FALSE;
        
        // Reset the starting ticks
        self->start_ticks = SDL_GetTicks() - self->paused_ticks;
        
        // Reset the paused ticks
        self->paused_ticks = 0;
    }
}

Uint32 Timer_GetTicks(Timer *self) {
    
    // The actual timer time
    Uint32 time = 0;
    
    // If the timer is running
    if (self->started) {
        // If the timer is paused
        if (self->paused) {
            // Return the number of ticks when the timer was paused
            time = self->paused_ticks;
        } else {
            // Return the current time minus the start time
            time = SDL_GetTicks() - self->start_ticks;
        }
    }
    
    return time;
}

bool Timer_IsStarted(Timer *self) {
    // Timer is running and paused or unpaused
    return self->started;
}

bool Timer_IsPaused(Timer *self) {
    // Timer is running and paused
    return self->paused && self->started;
}






// Dot function definitions

Dot *Dot_New() {
    Dot *self = (Dot *)malloc(sizeof(Dot));
    Dot_Init(self);
    return self;
}

void Dot_Init(Dot *self) {
    
    // Initialize the offsets
    self->pos_x = 0;
    self->pos_y = 0;
    
    // Initialize the velocity
    self->vel_x = 0;
    self->vel_y = 0;
}

void Dot_Destroy(Dot *self) {
    if (self != NULL) {
        Dot_DeleteMembers(self);
        free(self);
    }
}

void Dot_DeleteMembers(Dot *self) {
    self->pos_x = 0;
    self->pos_y = 0;
    
    self->vel_x = 0;
    self->vel_y = 0;
}

void Dot_HandleEvent(Dot *self, SDL_Event *event) {
    
    // If a key is pressed
    if (event->type == SDL_KEYDOWN && event->key.repeat == 0) {
        
        // Adjust the velocity
        switch (event->key.keysym.sym) {
            case SDLK_UP:
                self->vel_y -= DOT_VEL;
                break;
            
            case SDLK_DOWN:
                self->vel_y += DOT_VEL;
                break;
                
            case SDLK_LEFT:
                self->vel_x -= DOT_VEL;
                break;
            
            case SDLK_RIGHT:
                self->vel_x += DOT_VEL;
                break;
        }
    } else if (event->type == SDL_KEYUP && event->key.repeat == 0) {
        
        // Adjust the velocity
        // I might be able to simply just set all these values to 0
        switch (event->key.keysym.sym) {
            case SDLK_UP:
                self->vel_y += DOT_VEL;
                break;
            
            case SDLK_DOWN:
                self->vel_y -= DOT_VEL;
                break;
                
            case SDLK_LEFT:
                self->vel_x += DOT_VEL;
                break;
            
            case SDLK_RIGHT:
                self->vel_x -= DOT_VEL;
                break;
        }
    }
}


void Dot_Move(Dot *self) {
    
    // Move the dot to the left or right
    self->pos_x += self->vel_x;
    
    // If the dot went too far to the left or the right
    if ((self->pos_x < 0) || (self->pos_x + DOT_WIDTH > SCREEN_WIDTH)) {
        // Move back
        self->pos_x -= self->vel_x;
    }
    
    // Move the dot up or down
    self->pos_y += self->vel_y;
    
    // If the dot went too far up or down
    if ((self->pos_y < 0) || (self->pos_y + DOT_HEIGHT > SCREEN_HEIGHT)) {
        // Move back
        self->pos_y -= self->vel_y;
    }
}

void Dot_Render(Dot *self) {
    // Show the dot
    Texture_Render(gDotTexture, self->pos_x, self->pos_y, NULL, 0.0, NULL, SDL_FLIP_NONE);
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
                    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
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
    
    // Load the dot texture
    gDotTexture = Texture_New();
    if (!Texture_LoadFromFile(gDotTexture, "dot.bmp")) {
        printf("Unable to render dot texture!\n");
        success = FALSE;
    }
    
    return success;
}

void CloseSDL() {
    
    // Free loaded images
    Texture_Destroy(gDotTexture);
    gDotTexture = NULL;
    
    TTF_CloseFont(gFont);
    gFont = NULL;
    
    /**
    // Deallocate buttons
    for (int i = 0; i < TOTAL_BUTTONS; ++i) {
        Button_Destroy(gButtons[i]);
        gButtons[i] = NULL;
    }
    **/
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
            bool quit = FALSE;
            
            // Event handler
            SDL_Event event;
            
            // The dot that will be moving around on the screen
            Dot dot;
            Dot_Init(&dot);
            
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
                
                // Clear the screen
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);
                
                // Render dot
                Dot_Render(&dot);
                
                // Update the surface
                SDL_RenderPresent(gRenderer);
            }
        }
    }
    
    
    
    // Free resources and close SDL
    CloseSDL();
    
    return 0;
}


