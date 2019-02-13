#include "GameView.h"
#include "ViewUtil.h"

// Construct a GameView.
GameView::GameView(const Board & b, const int & s):
  board(&b), cell_size(s) {
  window_width = *b.get_width() * cell_size;
  window_height = *b.get_height() * cell_size;
  view_window = nullptr;
  view_surface = nullptr;
    red = nullptr;
    orange = nullptr;
    yellow = nullptr;
    green = nullptr;
    lightblue = nullptr;
    darkblue = nullptr;
    purple = nullptr;
    white = nullptr;
    gray = nullptr;
  player_width = *(b.get_player()->get_width()) * cell_size;
  player_height = *(b.get_player()->get_height()) * cell_size;
  
  init();
  load_media();
}

// Destruct a GameView.
GameView::~GameView() {
  close();
}

// Initializes SDL and makes the window.
bool GameView::init() {
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
				   window_width,
				   window_height,
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
  
  return success;
}

// Loads our media.
bool GameView::load_media() {
  // Load the images
  lightblue = load_surface("assets/LightBlue.bmp");
  darkblue = load_surface("assets/DarkBlue.bmp");
  red = load_surface("assets/Red.bmp");
  purple = load_surface("assets/Purple.bmp");
  green = load_surface("assets/Green.bmp");
  orange = load_surface("assets/Orange.bmp");
  yellow = load_surface("assets/Yellow.bmp");
  white = load_surface("assets/White.bmp");
  gray = load_surface("assets/Gray.bmp");
  
  // Returns true on success, false on failure.
  if (lightblue == nullptr ||
      darkblue == nullptr ||
      red == nullptr ||
      purple == nullptr ||
      green == nullptr ||
      orange == nullptr ||
      yellow == nullptr ||
      white == nullptr ||
      gray == nullptr) {
    return false;
  }
  
  return true;
}

// Frees media and shuts down SDL.
void GameView::close() {
  // SDL_DestroyRenderer(view_renderer);
  // The renderer is part of the window, so it gets free'd when we
  // destory that window.
  
  // SDL_FreeSurface(view_surface); 
  // The surface is part of the window, so it gets free'd when we 
  // destroy that window.
  
  
  // Destroy the window.
  SDL_DestroyWindow(view_window);
  view_window = nullptr;
  view_surface = nullptr;
  SDL_FreeSurface(red);
  SDL_FreeSurface(orange);
  SDL_FreeSurface(yellow);
  SDL_FreeSurface(green);
  SDL_FreeSurface(lightblue);
  SDL_FreeSurface(darkblue);
  SDL_FreeSurface(purple);
  SDL_FreeSurface(white);
  SDL_FreeSurface(gray);

  // Quit SDL.
  SDL_Quit();
}

void GameView::draw() const {
  // Draw every cell.
  for (Row r : *board->get_grid()) {
    for (Cell* c : r) {
      draw_cell(*c);
    }
  }

  draw_player();

  SDL_UpdateWindowSurface(view_window);
}

// Construct the SDL_Rect that matches the given Cell.
void GameView::draw_cell(const Cell & c) const {
  int x_position = cell_size * *c.get_x();
  int y_position = cell_size * 
    (((-1 * *c.get_y()) - 1) + *board->get_height());
  
  SDL_Rect* rect = new SDL_Rect();
  rect->x = x_position;
  rect->y = y_position;
  rect->w = cell_size;
  rect->h = cell_size;

  // const Shape *s = c.get_shape();
  // Tommy's edits to draw the premade image with the rect specifications
  switch (*(c.get_shape())) {
    case Shape::EMPTY:
      SDL_BlitScaled(gray, NULL, view_surface, rect);
      break;
    case Shape::BLOCK_T:
      SDL_BlitScaled(purple, NULL, view_surface, rect);
      break;
    case Shape::BLOCK_O:
      SDL_BlitScaled(yellow, NULL, view_surface, rect);
      break;
    case Shape::BLOCK_L:
      SDL_BlitScaled(orange, NULL, view_surface, rect);
      break;
    case Shape::BLOCK_J:
      SDL_BlitScaled(darkblue, NULL, view_surface, rect);
      break;
    case Shape::BLOCK_S:
      SDL_BlitScaled(green, NULL, view_surface, rect);
      break;
    case Shape::BLOCK_Z:
      SDL_BlitScaled(red, NULL, view_surface, rect);
      break;
    case Shape::BLOCK_I:
      SDL_BlitScaled(lightblue, NULL, view_surface, rect);
      break;
    default:
      SDL_BlitScaled(white, NULL, view_surface, rect);
  }
}

// Paint the given player on the given surface.
void GameView::draw_player() const {
  const Player* p = board->get_player();
  float x_position = *p->get_x() * cell_size;
  float y_position = (cell_size * *board->get_height()) - 
    (cell_size * *p->get_y()) - cell_size + (*p->get_height() * cell_size);
  int width = *p->get_width() * cell_size;
  int height = *p->get_height() * cell_size;
  SDL_Rect* rect = new SDL_Rect();
  rect->x = x_position;
  rect->y = y_position;
  rect->w = width;
  rect->h = height;
  SDL_BlitScaled(white, NULL, view_surface, rect);
}
