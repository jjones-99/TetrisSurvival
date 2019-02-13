#ifndef TMENUVIEW_CPP
#define TMENUVIEW_CPP

#include "MenuView.h"
#include "ViewUtil.h"
#include "Util.h"

// Constructs the menu view.
MenuView::MenuView(): 
  state(MenuState::MAIN),
  view_window(nullptr),
  view_surface(nullptr),
  background_surface(nullptr),
  play_button(MENU_HEIGHT * 1/2),
  quit_button(MENU_HEIGHT * 3/4),
  width_field(MENU_HEIGHT * 1/2),
  height_field(MENU_HEIGHT * 3/4),
  cell_size_field(MENU_HEIGHT * 1/2),
  difficulty_field(MENU_HEIGHT * 3/4),
  width_text(MENU_HEIGHT * 35/64),
  height_text(MENU_HEIGHT * 51/64),
  cell_size_text(MENU_HEIGHT * 35/64),
  difficulty_text(MENU_HEIGHT * 51/64),
  view_font(nullptr),
  width(0), height(0), cell_size(0), difficulty(0) {
    view_text_color = {0, 0, 0};
    init_sdl();
    load_media();
}

// Destructs the menu view.
MenuView::~MenuView() {
    close();
}

// Initializes SDL and makes the window.
bool MenuView::init_sdl() {
    // Returns true on success, false on failure.
  bool success = true;

  // Initialize SDL.
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "Error: SDL Initialization. SDL_Error: ";
    std::cout << SDL_GetError() << std::endl;
    success = false;
  } else {
    // SDL Initialized, construct the window.
    view_window = SDL_CreateWindow("Game",
				SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED,
				   MENU_WIDTH,
				   MENU_HEIGHT,
				SDL_WINDOW_SHOWN);

    if (view_window == nullptr) {
      // The window couldn't be constructed.
      std::cout << "Error: Window failed to construct. SDL_Error: ";
      std::cout << SDL_GetError() << std::endl;
      success = false;
    } else {
      // Get the surface of that window.
      view_surface = SDL_GetWindowSurface(view_window);
    }
  }
  
  if(TTF_Init() == -1) {
    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
    success = false;
  }
  
  return success;
}

// Loads our media.
bool MenuView::load_media() {
  // Load the images
  play_button.surface = load_surface("assets/MenuPlay.bmp");
  quit_button.surface = load_surface("assets/MenuQuit.bmp");
  background_surface = load_surface("assets/MenuBackground.bmp");
  width_field.surface = load_surface("assets/MenuWidth.bmp");
  height_field.surface = load_surface("assets/MenuHeight.bmp");
  cell_size_field.surface = load_surface("assets/MenuCellSize.bmp");
  difficulty_field.surface = load_surface("assets/MenuDifficulty.bmp");
  
  view_font = TTF_OpenFont("assets/lazy.ttf", 28);
  if( view_font == NULL )
  {
      printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
      return false;
  }
  
  // Returns true on success, false on failure.
  if (play_button.surface == nullptr ||
      quit_button.surface == nullptr ||
      background_surface == nullptr ||
      width_field.surface == nullptr ||
      height_field.surface == nullptr ||
      cell_size_field.surface == nullptr ||
      difficulty_field.surface == nullptr) {
    return false;
  }
  
  return true;
}

// Frees media and shuts down SDL.
void MenuView::close() {
  SDL_DestroyWindow(view_window);
  view_window = nullptr;
  view_surface = nullptr;
  SDL_FreeSurface(play_button.surface);
  SDL_FreeSurface(quit_button.surface);
  SDL_FreeSurface(background_surface);
  SDL_FreeSurface(width_field.surface);
  SDL_FreeSurface(height_field.surface);
  SDL_FreeSurface(cell_size_field.surface);
  SDL_FreeSurface(difficulty_field.surface);
  play_button.surface = nullptr;
  quit_button.surface = nullptr;
  background_surface = nullptr;
  width_field.surface = nullptr;
  height_field.surface = nullptr;
  cell_size_field.surface = nullptr;
  difficulty_field.surface = nullptr;
  
  TTF_CloseFont(view_font);
  view_font = nullptr;
    
  // Quit SDL.
  TTF_Quit();
  SDL_Quit();
}

// Draws the current state of the menu.
void MenuView::draw() const {
  SDL_Rect window_rect;
  window_rect.x = 0;
  window_rect.y = 0;
  window_rect.w = MENU_WIDTH;
  window_rect.h = MENU_HEIGHT;
  
  SDL_BlitScaled(background_surface, NULL, view_surface, &window_rect);
  
  switch (state) {
    case MenuState::MAIN:
      draw_piece(play_button);
      draw_piece(quit_button);
      break;
    case MenuState::WIDTH:
    case MenuState::HEIGHT:
      draw_piece(width_field);
      draw_piece(height_field);
      draw_text(width_text);
      draw_text(height_text);
      break;
    case MenuState::CELL_SIZE:
    case MenuState::DIFFICULTY:
      draw_piece(cell_size_field);
      draw_piece(difficulty_field);
      draw_text(cell_size_text);
      draw_text(difficulty_text);
      break;
    default:
      break;
  }
  
  SDL_UpdateWindowSurface(view_window);
}
      
// Draws the given piece in the window.
void MenuView::draw_piece(MenuPiece b) const {
    SDL_BlitScaled(b.surface, NULL, view_surface, &(b.rect));
}

void MenuView::draw_text(MenuText t) const {
  //Render text surface
  SDL_Surface* text_surface = TTF_RenderText_Solid(view_font, t.text.c_str(), {0, 0, 0});
  SDL_BlitSurface(text_surface, NULL, view_surface, &(t.rect));
}

// Returns the current state of the menu.
const MenuState* MenuView::get_state() const {
    return &state;
}

// Returns the player button.
const MenuPiece* MenuView::get_play_button() const {
    return &play_button;
}

// Returns the quit button.
const MenuPiece* MenuView::get_quit_button() const {
    return &quit_button;
}

// Appends the given digit to the currently-tracked value.
void MenuView::append_value(const int & d) {
  int* p;
  switch (state) {
    case MenuState::WIDTH:
      p = &width;
      break;
    case MenuState::HEIGHT:
      p = &height;
      break;
    case MenuState::CELL_SIZE:
      p = &cell_size;
      break;
    case MenuState::DIFFICULTY:
      p = &difficulty;
      break;
    default:
      return;
  }
  
  *p = *p * 10 + d;
  update_text();
}

// Cuts the last digit from the currently-tracked value.
void MenuView::cut_value() {
  int* p;
  switch (state) {
    case MenuState::WIDTH:
      p = &width;
      break;
    case MenuState::HEIGHT:
      p = &height;
      break;
    case MenuState::CELL_SIZE:
      p = &cell_size;
      break;
    case MenuState::DIFFICULTY:
      p = &difficulty;
      break;
    default:
      return;
  }
  
  *p = *p / 10;
  *p = max(0, *p);
  update_text();
}

void MenuView::reset() {
  state = MenuState::MAIN;
}

bool MenuView::progress() {
  switch (state) {
    case MenuState::MAIN:
      state = MenuState::WIDTH;
      break;
    case MenuState::WIDTH:
      state = MenuState::HEIGHT;
      break;
    case MenuState::HEIGHT:
      state = MenuState::CELL_SIZE;
      break;
    case MenuState::CELL_SIZE:
      state = MenuState::DIFFICULTY;
      break;
    case MenuState::DIFFICULTY:
      return true;
    default:
      break;
  }
  
  return false;
}

void MenuView::update_text() {
  width_text.text = std::to_string(width);
  height_text.text = std::to_string(height);
  cell_size_text.text = std::to_string(cell_size);
  difficulty_text.text = std::to_string(difficulty);
}

bool MenuView::modify_setup(Setup* game) {
  game->w = clip_range(width, MIN_BOARD_WIDTH, MAX_BOARD_WIDTH);
  game->h = clip_range(height, MIN_BOARD_HEIGHT, MAX_BOARD_HEIGHT);
  game->cs = clip_range(cell_size, MIN_CELL_SIZE, MAX_CELL_SIZE);
  game->d = clip_range(difficulty, MIN_DIFFICULTY, MAX_DIFFICULTY);
  
  return true;
}

#endif
