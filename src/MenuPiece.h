#ifndef TBUTTON_H
#define TBUTTON_H

#include <SDL2/SDL.h>

#include "Util.h"

class MenuView;

class MenuPiece {
    public:
    // Builds a MenuPiece with the given dimensions.
    MenuPiece(const int & x, const int & y, const int & w, const int & h);
    
    // Every MenuPiece in this game has the same x, w, and h.
    MenuPiece(const int & y);   
    
    // Determines if the given coordinates are in the MenuPiece's bounds.
    bool in_bounds(const int & x, const int & y) const;
    
    // The surface to display on the MenuPiece.
    SDL_Surface* surface;
    
    // The dimensions of the MenuPiece.
    SDL_Rect rect;
};

#endif