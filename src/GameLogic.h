#ifndef _GAME_LOGIC_H
#define _GAME_LOGIC_H

#include "Util.h"
#include "Board.h"
#include "GameView.h"
#include "MenuView.h"

class GameLogic {
 public:
  bool run_menu(Setup* game);
  void run_game(Setup* game);

 private:
  bool key_down_handler(const Board & model, SDL_KeyboardEvent* e);
  void key_up_handler(const Board & model, SDL_KeyboardEvent* e);
  bool handle_menu_input(MenuView & model, SDL_KeyboardEvent* e);
};

#endif
