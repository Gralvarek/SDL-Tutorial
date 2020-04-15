//
//  CheckCollision.h
//  SDL-Tutorial
//
//  Created by Vero on 27.03.20.
//  Copyright © 2020 Asgard Inc. All rights reserved.
//

#ifndef CheckCollision_h
#define CheckCollision_h

#include <stdio.h>
#include "Constants.h"
#include "Circle.h"
#include <SDL.h>

// Collision detection between circle and circle
boolean CheckCollision_CircleAndCircle(Circle *, Circle *);
// Collision detection between circle and rect
boolean CheckCollision_CircleAndRect(Circle *, SDL_Rect *);
// Collision detection between rect and rect
boolean CheckCollision_RectAndRect(SDL_Rect *, SDL_Rect *);
// Calculates distance squared between two points
double DistanceSquared(int, int, int, int);


#endif /* CheckCollision_h */
