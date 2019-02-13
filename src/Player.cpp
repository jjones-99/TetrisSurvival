#ifndef TPLAYER_CPP
#define TPLAYER_CPP

#include <cmath>

#include "Player.h"
#include "Board.h"
#include "Util.h"

Player::Player(): x(0.0), y(0.0),
		  vx(0.0), vy(0.0),
		  width(PLAYER_WIDTH),
		  height(PLAYER_HEIGHT),
      on_solid(true) {}

Player::~Player() {
  
}

// Get the values of members
const float* Player::get_x() const {
  return &x;
}

const float* Player::get_y() const {
  return &y;
}

const float* Player::get_vx() const {
  return &vx;
}

const float* Player::get_vy() const {
  return &vy;
}

const float* Player::get_width() const {
  return &width;
}

const float* Player::get_height() const {
  return &height;
}

// Get the cells that this player is currently occupying.
Posns Player::get_occupied() {
  Posns ps;

  float left_x = x - (width / 2);
  float right_x = x + (width / 2);
  float top_y = y + (height / 2);
  float bottom_y = y - (height / 2);

  Posn top_left = {left_x, top_y};
  Posn top_right = {right_x, top_y};
  Posn bottom_left = {left_x, bottom_y};
  Posn bottom_right = {right_x, bottom_y};
    
  if ((top_y != floor(top_y))) {
    ps.push_back(top_left);
  }

  if ((right_x != floor(right_x))
      && (top_y != floor(top_y))
      && (top_right != top_left)) {
    ps.push_back(top_right);
  }

  if ((bottom_left != top_left)
      && (bottom_left != top_right)) {
    ps.push_back(bottom_left);
  }

  if ((right_x != floor(right_x))
      && (bottom_right != top_left)
      && (bottom_right != top_right)
      && (bottom_right != bottom_left)) {
    ps.push_back(bottom_right);
  }

  return ps;
}

bool Player::tick(const Board* board) {
    vy = vy - PLAYER_GRAVITY;
    if (vy < 0) {
        float new_bottom = y + vy;
        bool left_open = board->is_open(x, new_bottom) 
            || x == floor(x);
        bool right_open = board->is_open(x + width, new_bottom) 
            || (x + width) == floor(x + width);
        
        if (left_open && right_open) {
            y = new_bottom;
        } else {
            y = ceil(new_bottom);
            vy = 0;
            on_solid = true;
        }
    } else if (vy > 0) {
        float new_top = y + height + vy;
        bool left_open = board->is_open(x, new_top)
            || x == floor(x);
        bool right_open = board->is_open(x + width, new_top)
            || (x + width) == floor(x + width);
        
        if (left_open && right_open) {
            y = new_top - height;
        } else {
            y = floor(new_top) - height;
            vy = 0;
        }
    }
    
    if (vx < 0) {
        float new_left = x + vx;
        bool up_open = board->is_open(new_left, y + height)
            || (y + height) == floor(y + height);
        bool down_open = board->is_open(new_left, y)
            || y == floor(y);
        
        if (up_open && down_open) {
            x = new_left;
        } else {
            x = ceil(new_left);
            vx = 0;
        }
    } else if (vx > 0) {
        float new_right = x + width + vx;
        bool up_open = board->is_open(new_right, y + height)
            || (y + height) == floor(y + height);
        bool down_open = board->is_open(new_right, y)
            || y == floor(y);
        
        if (up_open && down_open) {
            x = new_right - width;
        } else {
            x = floor(new_right) - width;
            vx = 0;
        }
    }
    
    if (y > *(board->get_height())) {
        return true;
    }
    
    x = clip_range(x, 0, *(board->get_width()));
    y = clip_range(y, 0, *(board->get_height()));
    
    return false;
}
	
void Player::jump() {
	// The player can only jump if they are on the ground.
	// (i.e. not falling or jumping, they have a vy of zero.)
	if (on_solid) {
        on_solid = false;
		vy = PLAYER_JUMP_POWER;
	}
}

void Player::move_left() {
	vx = -PLAYER_HORIZONTAL_POWER;
}

void Player::move_right() {
	vx = PLAYER_HORIZONTAL_POWER;
}
	
void Player::halt_sideways() {
	vx = 0;
}

bool Player::push_down(const Board* board) {
    int curr_x = floor(x);
    int curr_y = floor(y);
    
    if (!board->is_open(x, y - 1)) {
        return false;
    }
    
    y = curr_y - height;
    return true;
}
	
#endif