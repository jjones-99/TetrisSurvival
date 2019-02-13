#ifndef TMENUTEXT_H
#define TMENUTEXT_H

#include <SDL2/SDL.h>

#include "Util.h"

class MenuText {
    public:
    MenuText(int y);
    
    MenuText(int x, int y, int w, int h);
    
    // The text to display.
    std::string text;

    // The dimensions of the text.
    SDL_Rect rect;
};

#endif