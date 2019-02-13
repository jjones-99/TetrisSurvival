#ifndef TPLAYER_H
#define TPLAYER_H

#include "Util.h"

class Board;

class Player {
 public:
  Player();
  ~Player();

  // Get the values of members
  const float* get_x() const ;
  const float* get_y() const ;
  const float* get_vx() const ;
  const float* get_vy() const ;
  const float* get_width() const ;
  const float* get_height() const ;

  // Get the cells that this player is currently occupying.
  Posns get_occupied();
	
	// Cause the player to tick forward one step in time.
	// Involves moving the player.
	bool tick(const Board* board);
  
  // Determines if there is a block to the right of the player.
  bool collides_right(const Board* board);
  
  // Determines if there is a block to the left of the player.
  bool collides_left(const Board* board);
  
  // Determines if there is a block to the top of the player.
  bool collides_above(const Board* board);
  
  // Determines if there is a block to the bottom of the player.
  bool collides_below(const Board* board);
  
  // Determines if the player can fall, based on the given board.
  bool can_fall(const Board* board);
	
	// Cause the player to jump. They can only jump if they have no vertical velocity.
	void jump();
	
	// Cause the player to move to the left. Adjusts the player's horizontal velocity.
	void move_left();
	
	// Cause the player to move to the right. Adjusts the player's horizontal velocity.
	void move_right();
	
	// Cause the player to halt all sideways motion.
	void halt_sideways();
  
  // Push the player down a cell, return false if that cell is occupied.
  bool push_down(const Board* board);
  
  friend class PlayerTestSuite;
  
 private:
  float x;
  float y;
  float vx;
  float vy;
  float width;
  float height;
  bool on_solid;
};

#endif
