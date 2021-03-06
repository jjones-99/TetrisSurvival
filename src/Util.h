#ifndef TUTIL_H
#define TUTIL_H

#include <iostream>
#include <cmath>
#include <vector>
#include <utility>

using namespace std;

const int TICK_RATE = 1;
const int BLOCK_FALL_RATE = 100 * TICK_RATE;
const int BLOCK_SPAWN_RATE = 7 * BLOCK_FALL_RATE;

const int MENU_WIDTH = 500;
const int MENU_HEIGHT = 500;

const int MAX_BOARD_WIDTH = 200;
const int MIN_BOARD_WIDTH = 5;
const int MAX_BOARD_HEIGHT = 200;
const int MIN_BOARD_HEIGHT = 5;
const int MAX_CELL_SIZE = 100;
const int MIN_CELL_SIZE = 5;
const int MAX_DIFFICULTY = 100;
const int MIN_DIFFICULTY = 0;

const float PLAYER_WIDTH = 0.5;
const float PLAYER_HEIGHT = 0.5;
const float PLAYER_JUMP_POWER = 0.2 / TICK_RATE;
const float PLAYER_HORIZONTAL_POWER = 0.1 / TICK_RATE;
const float PLAYER_GRAVITY = PLAYER_JUMP_POWER / 50.0;

#define TTROUBLESHOOT
#ifdef TTROUBLESHOOT
#define tsp(val) (cout << (val) << endl)
#define tspn(name, val) (cout << (name) << ": \t" << (val) << endl)
#else
#define tsp(val) ;
#define tspn(name, val) ;
#endif

struct Setup {
  int w, h, cs, d;
  
  Setup(): w(0), h(0), cs(0), d(0) {}
};

typedef std::pair<int, int> Posn;
typedef std::vector<Posn> Posns;

//enum representing possible Tetromino shapes
enum class Shape {
  EMPTY,
  BLOCK_T,
  BLOCK_O,
  BLOCK_L,
  BLOCK_J,
  BLOCK_S,
  BLOCK_Z,
  BLOCK_I,
  BLOCK_TOTAL
};

static float clip_range(float f, float min, float max) {
  if (f >= max) {
    return max;
  } else if (f <= min) {
    return min;
  } else {
    return f;
  }
}

static bool within(float fa, float fb, float delta) {
  return abs(fa - fb) <= delta;
}

static bool f_equals(float fa, float fb) {
  return within(fa, fb, 0.001);
}

static bool posns_contains(Posns ps, int x, int y) {
  for (Posn p : ps) {
    if (p.first == x && p.second == y) {
      return true;
    }
  }
  
  return false;
}

static bool print_posns(Posns ps) {
  for (Posn p : ps) {
    std::cout << "(" << p.first << " " << p.second << ") ";
  }
  std::cout << std::endl;
}

#endif
