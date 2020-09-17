#include <cmath>

#include <node_astar.hpp>
#include <../cell/cell.hpp>

node_astar::node_astar() {
  pos.row = -1;
  pos.col = -1;
  f = 0;
  g = 0;
  h = 0;
}

node_astar::node_astar(int r, int c) {
  pos = cell(r, c);
  f = 0;
  g = 0;
  h = 0;
}

double node_astar::euclidean_distance(node_astar& other) {
  if(other.pos.row<0 || other.pos.col<0)
    return 100000000;
  return sqrt(pow(other.pos.row-pos.row, 2) + pow(other.pos.col-pos.col, 2));
}