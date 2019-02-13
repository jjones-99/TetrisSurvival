#ifndef TCELL_CPP
#define TCELL_CPP

#include "Cell.h"
#include <iostream>
using namespace std;

Cell::Cell(int ix, int iy) {
  x = ix;
  y = iy;
  
  make_empty();
}

Cell::~Cell() {

}

const Shape* Cell::get_shape() const {
  return &shape;
}

const int* Cell::get_id() const {
  return &shapeId;
}

const int* Cell::get_x() const {
  return &x;
}

const int* Cell::get_y() const {
  return &y;
}

void Cell::make_empty(){
  set(Shape::EMPTY, -1);
}

void Cell::set(const Shape & ns, const int & id){
  shape = ns;
  shapeId = id;
}

#endif
