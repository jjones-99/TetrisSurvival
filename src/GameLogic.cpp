#include "GameLogic.h"
#include <iostream>
using namespace std;

/* go method:
   -while loop based on quit flag
    -while loop to handle events
    call view.draw
   constructor that takes in model (board) and view (gameview)
*/

bool GameLogic::run_menu(Setup* game) {
    SDL_Event e;
    
    MenuView menu;
    
    bool quit = false;
    bool playing = true;
    
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                if(e.button.button == SDL_BUTTON_LEFT &&
                   menu.get_play_button()->
                   in_bounds(e.button.x, e.button.y)) {
                    menu.progress();
                } else if(e.button.button == SDL_BUTTON_LEFT &&
                   menu.get_quit_button()->
                          in_bounds(e.button.x, e.button.y)) {
                    quit = true;
                    playing = false;
                }
            } else if (e.type == SDL_KEYDOWN) {
                switch (*(menu.get_state())) {
                    case MenuState::WIDTH:
                    case MenuState::HEIGHT:
                    case MenuState::CELL_SIZE:
                    case MenuState::DIFFICULTY:
                        if (handle_menu_input(menu, &e.key)) {
                            quit = true;
                        }
                        break;
                    default:
                        break;
                }
            }
        }
        
        menu.draw();
    }
    
    if (!playing) {
        return false;
    } else {
        return menu.modify_setup(game);
    }
}

void GameLogic::run_game(Setup* game) {
    Board model(game->w, game->h, game->d);
    GameView view(model, game->cs);
    
    int curr_tick = 0;
    
    bool quit = false;

    SDL_Event e;
    while(!quit) {
        while(SDL_PollEvent(&e) != 0) {
            if(e.type == SDL_QUIT) {
                quit = true;
            }

            if (e.type == SDL_KEYDOWN) {
                quit = key_down_handler(model, &e.key);
            }

            if (e.type == SDL_KEYUP) {
                key_up_handler(model, &e.key);
            }
        }

        if (curr_tick % TICK_RATE == 0) {
            if (model.tick()) {
                quit = true;
            }
	    }

        view.draw();
        
        ++curr_tick;
    }
    
    if (*(model.get_player()->get_y()) >= *(model.get_height())) {
        std::cout << "You won!" << std::endl;
    } else {
        std::cout << "You lost!" << std::endl;
    }
}

bool GameLogic::key_down_handler(const Board & model, SDL_KeyboardEvent* e) {
	if (e->keysym.sym == SDLK_ESCAPE) {
		return true;
	} else if (e->keysym.sym == SDLK_RIGHT) {
	  model.player_move_right();
	} else if (e->keysym.sym == SDLK_LEFT) {
	  model.player_move_left();
	} else if (e->keysym.sym == SDLK_UP) {
	  model.player_jump();
	}
    
    return false;
}

void GameLogic::key_up_handler(const Board & model, SDL_KeyboardEvent* e) {
	if (e->keysym.sym == SDLK_RIGHT || e->keysym.sym == SDLK_LEFT) {
	  model.player_halt_sideways();
	}
}

bool GameLogic::handle_menu_input(MenuView & menu, SDL_KeyboardEvent* e) {
	int value = 0;
    switch (e->keysym.sym) {
        case SDLK_BACKSPACE:
            menu.cut_value();
            return false;
        case SDLK_RETURN:
            return menu.progress();
        case SDLK_0: break;
        case SDLK_1: value = 1; break;
        case SDLK_2: value = 2; break;
        case SDLK_3: value = 3; break;
        case SDLK_4: value = 4; break;
        case SDLK_5: value = 5; break;
        case SDLK_6: value = 6; break;
        case SDLK_7: value = 7; break;
        case SDLK_8: value = 8; break;
        case SDLK_9: value = 9; break;
        default:
            return false;
    }
    
    menu.append_value(value);
    return false;
}
