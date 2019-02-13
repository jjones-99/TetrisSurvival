#ifndef TCELL_H
#define TCELL_H

#include "Util.h"

class Cell {
 public:
 Cell(int ix, int iy);
  ~Cell();

  // Get values of members.
  const Shape* get_shape() const ;
  const int* get_id() const ;
  const int* get_x() const ;
  const int* get_y() const ;
  
  void make_empty();
  void set(const Shape & ns, const int & id);
  
  friend class CellTestSuite;

 private:
  Shape shape;
  int shapeId;
  int x;
  int y;
};

#endif
