#ifndef TVIEWUTIL_H
#define TVIEWUTIL_H

#include <SDL2/SDL.h>

// Basis from lazyfoo productions.
static
SDL_Surface* load_surface(std::string path) {  
  // Load image at specified path
  SDL_Surface* surface_from_bitmap = SDL_LoadBMP(path.c_str());
  if (surface_from_bitmap == NULL) {
    printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
  }

  // Return the new surface, which might be null.
  return surface_from_bitmap;
}

#endif