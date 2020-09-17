#ifndef NODE_ASTAR
#define NODE_ASTAR

#include <../cell/cell.hpp>

class node_astar {
  public:
    cell pos;
    double f, g, h;

    node_astar();
    node_astar(int r, int c);
    double euclidean_distance(node_astar& other);
};

class node_compare_on_f {
  public:
    bool operator() (node_astar a, node_astar b) {
      return a.f > b.f;
    }
};

#endif