#include <cell.hpp>
#include <cmath>

cell::cell() {
  row = -1;
  col = -1;
}

cell::cell(int r, int c) {
  row = r;
  col = c;
}

double cell::euclidean_distance(cell& other) {
  if(other.row<0 || other.col<0)
    return 100000000;
  return sqrt(pow(other.row-row, 2) + pow(other.col-col, 2));
}

bool cell::is_equal(cell& other) {
  return (row==other.row && col==other.col);
}