#include "MenuPiece.h"

MenuPiece::MenuPiece(const int & x, const int & y, const int & w, const int & h) {
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    surface = nullptr;
}

MenuPiece::MenuPiece(const int & y) {
    rect.x = MENU_WIDTH * 1/4;
    rect.y = y;
    rect.w = MENU_WIDTH * 1/2;
    rect.h = MENU_HEIGHT * 1/8;
    surface = nullptr;
}

// Determines if the given coordinates are within the MenuPiece's bounds.
bool MenuPiece::in_bounds(const int & x, const int & y) const {
    return x >= rect.x
        && x <= (rect.x + rect.w)
        && y >= rect.y
        && y <= (rect.y + rect.h);
}