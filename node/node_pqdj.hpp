#ifndef NODE_PQDJ
#define NODE_PQDJ

#include <../cell/cell.hpp>

class node_pqdj {
  public:
    cell pos;
    double dist;

    node_pqdj();
    node_pqdj(int r, int c, double d);
};

class node_compare {
  public:
    bool operator() (node_pqdj a, node_pqdj b) {
      return a.dist > b.dist;
    }
};

#endif