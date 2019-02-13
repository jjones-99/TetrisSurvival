#ifndef TBOARD_H
#define TBOARD_H

#include <vector>
#include <array>

#include "Cell.h"
#include "Util.h"

// Represents the Player class, defined elsewhere.
class Player;

// Some types we will use frequently.
typedef std::vector<Cell*> Row;
typedef std::vector<Row> Grid;
typedef std::vector<std::array<Cell*, 4>> PieceList;

// Represents the game board.
class Board {
 public:
  // Construct a default board.
  Board();
  
  // Construct a game board with given dimensions and difficulty.
  Board(int w, int h, float d);
  
  // Destruct the game board.
  ~Board();

  // Get the values of the members.
  const int* get_width() const ;
  const int* get_height() const ;
  const Grid* get_grid() const ;
  const Player* get_player() const ;
  const int* get_cur_id();

  // Moves the game state forwards in time.
  // - Makes the blocks fall.
  // - Updates the player's position based on their velocity.
  // - Returns true if the game is over.
  bool tick();
  
  // Moves the grid forwards in time. Makes all the blocks fall.
  // Returns true if a block crushes the player.
  bool tick_grid();
  
  // Generates a new tetronimo of the given shape starting at the given column.
  // Takes in a configuration, a 16-long c-string, representing a 4x4 grid,
  //   where characters that are '+' represent pieces of the block, and
  //   other characters represent empty space
  void create_tetromino(Shape s, int x, const char* config);
  
  // Generates a new tetronimo of the given shape
  void create_tetromino(Shape s);

  // Checks whether the tetromino with the given id can fall
  bool can_fall(int idcopy) const;

  // Moves the tetromino with the given id down by one row
  void fall(int idcopy);

  // Determines if the given position is occupied by a block or not.
  bool is_open(float x, float y) const;
  
  // Determines if a block has moved into the same cell as the player
  bool game_over();

  // Spawns a random block at the top of the screen.
  void spawn_block();
  
  // Spawns a random T block at the top of the screen.
  void spawn_T();
  
  // Spawns a random O block at the top of the screen.
  void spawn_O();
  
  // Spawns a random L block at the top of the screen.
  void spawn_L();
  
  // Spawns a random J block at the top of the screen.
  void spawn_J();
  
  // Spawns a random S block at the top of the screen.
  void spawn_S();
  
  // Spawns a random Z block at the top of the screen.
  void spawn_Z();
  
  // Spawns a random I block at the top of the screen.
  void spawn_I();
  
  // Controls the movement of the player.
  void player_jump() const;
  void player_move_left() const;
  void player_move_right() const;
  void player_halt_sideways() const;
  
  // Set a specific cell in the board.
  void set_cell(Shape s, int x, int y);
  void set_cell(Shape s, int x, int y, int id);
  
  // The test class is our friend.
  friend class BoardTestSuite;

 private:
  // The dimensions of the board.
  int width;
  int height;
  
  // The current tetronimo ID we are at in generation.
  int curID;
  
  // The difficulty of the game.
  float difficulty;
  
  // The grid of cells.
  Grid g;
  
  // The player.
  Player* p;
  
  // A list of every tetronimo we've spawned.
  PieceList tetrominos;
  
  // The rate at which blocks fall.
  int block_fall_rate;
  
  // The rate at which blocks spawn.
  int block_spawn_rate;
  
  // The rate at which ticks progress in the game.
  int tick_counter;
  
  // Generate a grid of cells with the given dimensions.
  Grid generate_board(const int & w, const int & h);
};



#endif
