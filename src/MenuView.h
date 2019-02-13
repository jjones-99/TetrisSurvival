#ifndef TMENUVIEW_H
#define TMENUVIEW_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL_ttf.h>

#include "Board.h"
#include "GameView.h"
#include "MenuPiece.h"
#include "MenuText.h"

enum class MenuState {
  MAIN, WIDTH, HEIGHT, CELL_SIZE, DIFFICULTY, TOTAL
};

class MenuView {
 public:
  MenuView();
  ~MenuView();
  
  // Initializes SDL and makes the window.
  bool init_sdl();

  // Loads our media.
  bool load_media();

  // Frees media and shuts down SDL.
  void close();
  
  // Draws the current state of the board.
  void draw() const;
    
  // Draws the given button in the window.
  void draw_piece(MenuPiece b) const;
  
  // Draws the given text in the window.
  void draw_text(MenuText t) const;
  void draw_text(MenuText t, SDL_Rect* r) const;
    
  // Returns the player button.
  const MenuPiece* get_play_button() const;

  // Returns the quit button.
  const MenuPiece* get_quit_button() const;
  
  // Returns the state of the menu.
  const MenuState* get_state() const;
  
  // Appends the given digit to the currently-tracked value.
  void append_value(const int & d);
  
  // Cuts the last digit from the currently-tracked value.
  void cut_value();
  
  // Creates a board and allocates it on the heap.
  Board* make_board() const;
  
  // Creates a game view and allocates it on the heap.
  GameView* make_view(Board* b) const;
  
  // Goes to the main state of the menu.
  void reset();
  
  // Progresses to the next state of the menu.
  bool progress();
  
  void update_text();
  
  bool modify_setup(Setup* game);

  friend class MenuViewTestSuite;

 private:
  
  // The current state of the menu.
  MenuState state;

  // The window we'll render.
  SDL_Window* view_window;

  // The surface in that window.
  SDL_Surface* view_surface;
  
  // The font to write in.
  TTF_Font* view_font;
  
  // The color to write in.
  SDL_Color view_text_color;

  // The dimensions of the window.
  int window_width;
  int window_height;
    
  // The MenuPiece in the window.
  MenuPiece play_button;
  MenuPiece quit_button;
  MenuPiece width_field;
  MenuPiece height_field;
  MenuPiece cell_size_field;
  MenuPiece difficulty_field;
  
  // The text in the window.
  MenuText width_text;
  MenuText height_text;
  MenuText cell_size_text;
  MenuText difficulty_text;
  
  // The fields to create the board.
  int width, height, cell_size, difficulty;
  
  // The background of the menu.
  SDL_Surface* background_surface;
};
 
#endif
