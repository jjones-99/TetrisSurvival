#ifndef TGAME_VIEW_H
#define TGAME_VIEW_H

#include <iostream>
#include <SDL2/SDL.h>

#include "Util.h"
#include "Board.h"
#include "Player.h"
#include "Cell.h"
#include "ViewUtil.h"

class GameView {
 public:
  GameView(const Board & b, const int & s);
  ~GameView();
  
  // Initializes SDL and makes the window.
  bool init();

  // Loads our media.
  bool load_media();

  // Frees media and shuts down SDL.
  void close();
  
  // Draws the current state of the board.
  void draw() const;

  // Draw the image that matches the given Cell.
  void draw_cell(const Cell & c) const;

  // Paint the player on the given surface.
  void draw_player() const;
  
  const int* get_cell_size() const;

  friend class GameViewTestSuite;

 private:
  // The board to be displayed.
  const Board* board;

  // The window we'll render.
  SDL_Window* view_window;

  // The surface in that window.
  SDL_Surface* view_surface;

  // The dimensions of the window.
  int window_width;
  int window_height;
  
  // The dimensions of the player. Saved once, used later.
  int player_width;
  int player_height;
  
  // The dimensions of each cell.
  int cell_size;
  
  // The images for cells
  SDL_Surface* red;
  SDL_Surface* orange;
  SDL_Surface* yellow;
  SDL_Surface* green;
  SDL_Surface* lightblue;
  SDL_Surface* darkblue;
  SDL_Surface* purple;
  SDL_Surface* white;
  SDL_Surface* gray;
};
 
#endif
