//
//  CheckCollision.c
//  SDL-Tutorial
//
//  Created by Vero on 27.03.20.
//  Copyright © 2020 Asgard Inc. All rights reserved.
//

#include "CheckCollision.h"



boolean CheckCollision_CircleAndCircle(Circle *a, Circle *b) {
    
    // Calculate total radius squared
    int total_radius_squared = a->r + b->r;
    total_radius_squared = total_radius_squared * total_radius_squared;
    
    // If the distance between the centers of the circles is less than the sum of their radii
    if (DistanceSquared(a->x, a->y, b->x, b->y) < total_radius_squared) {
        // The circles have collided
        return TRUE;
    }
    
    // If not
    return FALSE;
}


boolean CheckCollision_CircleAndRect(Circle *a, SDL_Rect *b) {
    
    // Closest point on collision box
    int cX, cY;
    

    // Find closest x offset
    if (a->x < b->x) {
        cX = b->x;
    } else if (a->x > b->x + b->w) {
        cX = b->x + b->w;
    } else {
        cX = a->x;
    }
    
    
    // Find closest x offset
    if (a->y < b->y) {
        cY = b->y;
    } else if (a->y > b->y + b->h) {
        cY = b->y + b->h;
    } else {
        cY = a->y;
    }
    
    // If the closest point is inside the circle
    if (DistanceSquared(a->x, a->y, cX, cY) < a->r * a->r) {
        // This circle and box have collided
        return TRUE;
    }
    
    // The shapes have not collided
    return FALSE;
}

boolean CheckCollision_RectAndRect(SDL_Rect *a, SDL_Rect *b) {
    
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a->x;
    rightA = a->x + a->w;
    topA = a->y;
    bottomA = a->y + a->h;

    //Calculate the sides of rect B
    leftB = b->x;
    rightB = b->x + b->w;
    topB = b->y;
    bottomB = b->y + b->h;
    
    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return FALSE;
    }

    if( topA >= bottomB )
    {
        return FALSE;
    }

    if( rightA <= leftB )
    {
        return FALSE;
    }

    if( leftA >= rightB )
    {
        return FALSE;
    }

    //If none of the sides from A are outside B
    return TRUE;
}






double DistanceSquared(int x1, int y1, int x2, int y2) {
    int delta_x = x2 - x1;
    int delta_y = y2 - y1;
    return delta_x*delta_x + delta_y*delta_y;
}
