#include <node_pqdj.hpp>

#include <../cell/cell.hpp>

node_pqdj::node_pqdj() {
  pos.row = -1;
  pos.col = -1;
  dist = -1;
}

node_pqdj::node_pqdj(int r, int c, double d) {
  pos = cell(r, c);
  dist = d;
}