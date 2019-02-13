#include <time.h>

#include "Board.h"
#include "GameView.h"
#include "GameLogic.h"

#include "Util.h"

int main() {
  srand(time(nullptr));
  
  GameLogic controller;
  
  Setup game;
  while (controller.run_menu(&game)) {
    controller.run_game(&game);
  }
  
  tsp("Finished main()");
}
