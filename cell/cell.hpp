#ifndef CELL_INCLUDE
#define CELL_INCLUDE

enum cell_type {
  UNVISITED,
  VISITED,
  FREE,
  BLOCK
};

// cell is a single point in the grid environment
class cell {
  public:
    int row;
    int col;

    cell();
    cell(int r, int c);
    double euclidean_distance(cell& other);
    bool is_equal(cell& other);
};

#endif