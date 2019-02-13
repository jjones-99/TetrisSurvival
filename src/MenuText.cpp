#ifndef TMENUTEXT_CPP
#define TMENUTEXT_CPP

#include "MenuText.h"

MenuText::MenuText(int y): MenuText(MENU_WIDTH * 9/16,
                          y,
                          MENU_WIDTH * 1/4,
                          MENU_HEIGHT * 1/16) {}
    
MenuText::MenuText(int x, int y, int w, int h) {
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    text = "0";
}

#endif