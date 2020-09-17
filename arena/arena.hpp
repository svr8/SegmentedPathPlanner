#ifndef ARENA_INCLUDE
#define ARENA_INCLUDE

#include <string>

#include <../cell/cell.hpp>

using namespace std;

// arean represents the robot environment.
// once the arena has been initialised and map file has been parsed,
// it is not meant to be modified again.

class arena {
  private:
    cell_type** graph;

  public:
    cell start;
    cell destination;
    int width;
    int height;

    arena();
    arena(string& filepath);
    cell_type get(int i, int j);
    void set(int i, int j, cell_type type);
};

#endif