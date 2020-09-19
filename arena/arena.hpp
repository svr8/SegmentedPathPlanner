#ifndef ARENA_INCLUDE
#define ARENA_INCLUDE

#include <string>

#include <../cell/cell.hpp>

using namespace std;

enum arena_type {
  ARENA_CUSTOM,
  ARENA_MOVING_AI
};

class arena {
  private:
    cell_type** graph;
    void parse_custom(string& filepath);
    void parse_movingai(string& scenepath, string& root, int test_index);

  public:
    cell start;
    cell destination;
    int width;
    int height;
    int bucket;

    arena();
    arena(string& filepath, arena_type map_type);
    arena(string& scenepath, string& root, int test_index, arena_type map_type);
    cell_type get(int i, int j);
    void set(int i, int j, cell_type type);
};

#endif