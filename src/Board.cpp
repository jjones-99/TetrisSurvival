#ifndef TBOARD_CPP
#define TBOARD_CPP

#include "Board.h"
#include "Player.h"

// Construct a default board.
Board::Board() {
  Board(10, 20, 1.0f);
}

// Construct a game board with given dimensions and difficulty.
Board::Board(int w, int h, float d) {
  width = w;
  height = h;
  curID = 0;
  difficulty = d;
  g = generate_board(w, h + 4);
  p = new Player();
  tick_counter = 0;
  block_fall_rate = BLOCK_FALL_RATE / difficulty ;
  block_spawn_rate = BLOCK_SPAWN_RATE / difficulty ;
}

// Destruct the game board.
Board::~Board() {
	delete p;
	
	for (Row r : g) {
		for (Cell* c : r) {
			delete c;
		}
	}
}

const int* Board::get_width() const {
  return &width;
}

const int* Board::get_height() const {
  return &height;
}

const int* Board::get_cur_id(){
  return &curID;
}

const Grid* Board::get_grid() const {
  return &g;
}

const Player* Board::get_player() const {
  return p;
}

bool Board::is_open(float x, float y) const {
  if (x < 0 || x >= width) {
    return false;
  }
  
  if (y < 0 || y >= height + 4) {
    return false;
  }
  
  return *g.at(y).at(x)->get_shape() == Shape::EMPTY;
}

bool Board::game_over() {
  Posns p_pos = p->get_occupied(); 
  for(int i = 0; i < height; i++) {
    for(int j = 0; j < width; j++) {
      for(int k = 0; k < p_pos.size(); k++){
	if(j == p_pos[k].first && i == p_pos[k].second && *g[i][j]->get_shape() != Shape::EMPTY){
	  return true;
       	}
      }
    }
  }
  return false;
}

Grid Board::generate_board(const int & w, const int & h) {
  Grid initialG;
  for (int i = 0; i < h; i++) {
    Row initialRow;
    for (int j = 0; j < w; j++) {
      Cell* newCell = new Cell(j, i);
      newCell->make_empty();
      initialRow.push_back(newCell);
    }
    initialG.push_back(initialRow);
  }
  
  return initialG;
}

void Board::set_cell(Shape s, int x, int y) {
  set_cell(s, x, y, curID);
  ++curID;
}

void Board::set_cell(Shape s, int x, int y, int id) {
  g[x][y]->set(s, id);
}

void Board::create_tetromino(Shape s, int x, const char* config) {
  int ii = 0;
  
  for (const char* curr = config;
       *curr != '\0' && ii < 16; 
       ++curr) {
    int row = ii / 4 + height;
    int col = ii % 4 + x;
    
    if (*curr == '+') {
      g[row][col]->set(s, curID);
    }
    ++ii;
  }
  
  ++curID;
}

void Board::create_tetromino(Shape s) {
  switch (s) {
  case Shape::BLOCK_T:
    g[height + 1][4]->set(s, curID);
    g[height][3]->set(s, curID);
    g[height][4]->set(s, curID);
    g[height][5]->set(s, curID);
    curID++;
    break;
  case Shape::BLOCK_O:
    g[height + 1][4]->set(s, curID);
    g[height+ 1][5]->set(s, curID);
    g[height][4]->set(s, curID);
    g[height][5]->set(s, curID);
    curID++;
    break;
  case Shape::BLOCK_L:
    g[height + 1][5]->set(s, curID);
    g[height][3]->set(s, curID);
    g[height][4]->set(s, curID);
    g[height][5]->set(s, curID);
    curID++;
    break;
  case Shape::BLOCK_J:
    g[height + 1][3]->set(s, curID);
    g[height][3]->set(s, curID);
    g[height][4]->set(s, curID);
    g[height][5]->set(s, curID);
    curID++;
    break;
  case Shape::BLOCK_S:
    g[height + 1][4]->set(s, curID);
    g[height][3]->set(s, curID);
    g[height][4]->set(s, curID);
    g[height + 1][5]->set(s, curID);
    curID++;
    break;
  case Shape::BLOCK_Z:
    g[height + 1][4]->set(s, curID);
    g[height + 1][3]->set(s, curID);
    g[height][4]->set(s, curID);
    g[height][5]->set(s, curID);
    curID++;
    break;
  case Shape::BLOCK_I:
    g[height][4]->set(s, curID);
    g[height + 1][4]->set(s, curID);
    g[height + 2][4]->set(s, curID);
    g[height + 3][4]->set(s, curID);
    curID++;
    break;
  default:
    break;
  }
}

void Board::spawn_block() {
  int shape = rand() % 7;
  switch (shape) {
    case 0:
      spawn_T();
      break;
    case 1:
      spawn_O();
      break;
    case 2:
      spawn_L();
      break;
    case 3:
      spawn_J();
      break;
    case 4:
      spawn_S();
      break;
    case 5:
      spawn_Z();
      break;
    case 6:
      spawn_I();
      break;
  }
}

void Board::spawn_T() {
  // 0 : -|
  // 1 : T
  // 2 : |-
  // 3 : _|_
  int rotation = rand() % 4;
  
  // Odd rotation values have widths of three.
  // Even rotation values have widths of two.
  int horizontal_silhouette = 2 + rotation % 2;
  
  // Create the random position.
  int x_position = rand() % (width - horizontal_silhouette);
  
  Shape s = Shape::BLOCK_T;
  switch (rotation) {
    case 0:
      create_tetromino(s, x_position, 
                       "-----+--++---+--");
      break;
    case 1:
      create_tetromino(s, x_position, 
                       "--------+++--+--");
      break;
    case 2:
      create_tetromino(s, x_position, 
                       "----+---++--+---");
      break;
    case 3:
      create_tetromino(s, x_position, 
                       "---------+--+++-");
      break;
  }
}

void Board::spawn_O() {
  // 0 : O
  // int rotation = eh
  // There is only one rotation of the O piece.
  
  // Silhouette is always 2.
  int horizontal_silhouette = 2;
  
  // Create the random position.
  int x_position = rand() % (width - horizontal_silhouette);
  
  Shape s = Shape::BLOCK_O;
  create_tetromino(s, x_position, 
                   "--------++--++--");
}

void Board::spawn_L() {
  // 0 : L
  // 1 : |^^
  // 2 : ^|
  // 3 : __|
  int rotation = rand() % 4;
  
  // Odd rotation values have widths of three.
  // Even rotation values have widths of two.
  int horizontal_silhouette = 2 + rotation % 2;
  
  // Create the random position.
  int x_position = rand() % (width - horizontal_silhouette);
  
  Shape s = Shape::BLOCK_L;
  switch (rotation) {
    case 0:
      create_tetromino(s, x_position, 
                       "----+---+---++--");
      break;
    case 1:
      create_tetromino(s, x_position, 
                       "--------+++-+---");
      break;
    case 2:
      create_tetromino(s, x_position, 
                       "----++---+---+--");
      break;
    case 3:
      create_tetromino(s, x_position, 
                       "----------+-+++-");
      break;
  }
}

void Board::spawn_J() {
  // 0 : J
  // 1 : |__
  // 2 : |^
  // 3 : ^^|
  int rotation = rand() % 4;
  
  // Odd rotation values have widths of three.
  // Even rotation values have widths of two.
  int horizontal_silhouette = 2 + rotation % 2;
  
  // Create the random position.
  int x_position = rand() % (width - horizontal_silhouette);
  
  Shape s = Shape::BLOCK_J;
  switch (rotation) {
    case 0:
      create_tetromino(s, x_position, 
                       "-----+---+--++--");
      break;
    case 1:
      create_tetromino(s, x_position, 
                       "--------+---+++-");
      break;
    case 2:
      create_tetromino(s, x_position, 
                       "----++--+---+---");
      break;
    case 3:
      create_tetromino(s, x_position, 
                       "--------+++---+-");
      break;
  }
}

void Board::spawn_S() {
  // 0 : ^-_
  // 1 : _|^
  int rotation = rand() % 2;
  
  // Odd rotation values have widths of three.
  // Even rotation values have widths of two.
  int horizontal_silhouette = 2 + rotation % 2;
  
  // Create the random position.
  int x_position = rand() % (width - horizontal_silhouette);
  
  Shape s = Shape::BLOCK_S;
  switch (rotation) {
    case 0:
      create_tetromino(s, x_position, 
                       "----+---++---+--");
      break;
    case 1:
      create_tetromino(s, x_position, 
                       "---------++-++--");
      break;
  }
}

void Board::spawn_Z() {
  // 0 : _-^
  // 1 : ^|_
  int rotation = rand() % 2;
  
  // Odd rotation values have widths of three.
  // Even rotation values have widths of two.
  int horizontal_silhouette = 2 + rotation % 2;
  
  // Create the random position.
  int x_position = rand() % (width - horizontal_silhouette);
  
  Shape s = Shape::BLOCK_Z;
  switch (rotation) {
    case 0:
      create_tetromino(s, x_position, 
                       "-----+--++--+---");
      break;
    case 1:
      create_tetromino(s, x_position, 
                       "--------++---++-");
      break;
  }
}

void Board::spawn_I() {
  // 0 : |
  // 1 : __
  int rotation = rand() % 2;
  
  // Odd rotation values have widths of 4.
  // Even rotation values have widths of 1.
  int horizontal_silhouette = 2 + 3 * rotation % 2;
  
  // Create the random position.
  int x_position = rand() % (width - horizontal_silhouette);
  
  Shape s = Shape::BLOCK_I;
  switch (rotation) {
    case 0:
      create_tetromino(s, x_position, 
                       "+---+---+---+---");
      break;
    case 1:
      create_tetromino(s, x_position, 
                       "------------++++");
      break;
  }
}

void Board::player_jump() const {
  p->jump();
}

void Board::player_move_left() const {
  p->move_left();
}

void Board::player_move_right() const {
  p->move_right();
}

void Board::player_halt_sideways() const {
  p->halt_sideways();
}

bool Board::tick() {
  // Increment the counter.
  tick_counter += 1;
  
  // Tick the player.
  if (p->tick(this)) {
    return true;
  }
  
  // If enough ticks have passed, tick the grid.
  if (tick_counter % block_fall_rate  == 0) {
    if (tick_grid()) {
      return true;
    }
  }
  
  // If enough ticks have passed, spawn a new block.
  if (tick_counter % block_spawn_rate  == 0) {
    spawn_block();
  }
  
  return false;
}

bool Board::tick_grid() {
  // Get all the cells that a player is occupying.
  Posns player_occupied_cells = p->get_occupied();
  //print_posns(player_occupied_cells);
  
  // If there are no tetrominos yet, we don't need to do anything.
  if (curID == 0) {
    return false;
  }
  
  // Create an array to store whether or not each tetromino ID can fall.
  bool fall_map[curID];
  for (int ii = 0; ii < curID; ++ii) {
    fall_map[ii] = true;
  }
    
  // Iterate over each cell and determine which id's can't fall.
  for (int row = 0; row < height + 3; ++row) {
    for (int col = 0; col < width; ++col) {
      Cell* this_cell = g[row][col];
      int this_id = *this_cell->get_id();
      if (*this_cell->get_shape() != Shape::EMPTY) {
        if (row == 0) {
          // This cell is in the bottom row, it can't fall.
          fall_map[this_id] = false;
        } else {
          Cell* lower_cell = g[row - 1][col];
          if (*lower_cell->get_shape() != Shape::EMPTY && *lower_cell->get_id() != this_id) {
            // This cell is not in the bottom row, but there is a cell right beneath it that isn't empty.
            fall_map[this_id] = false;
          }
        }
      }
    }
  }
    
  // Iterate over each cell again and make the blocks that can fall drop.
  for (int row = 0; row < height + 4; ++row) {
    for (int col = 0; col < width; ++col) {
      Cell* this_cell = g[row][col];
      Shape this_shape = *this_cell->get_shape();
      if (this_shape != Shape::EMPTY) {
        int this_id = *this_cell->get_id();
        if (fall_map[this_id] == true) {
          // The cell can fall.
          // Will the cell fall onto the player?
          if (posns_contains(player_occupied_cells, col, row - 1)) {
            // Can the player move down?
            if (!p->push_down(this)) {
              return true;
            }
          }
          // The cell can move, the player won't be squished.
          // we know there is an empty lower cell.
          Cell* lower_cell = g[row - 1][col];
          lower_cell->set(this_shape, this_id);
          this_cell->make_empty();
        }
      }
    }
  }
  
  return false;
}

#endif
