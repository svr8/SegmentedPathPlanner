#ifndef ARENA_INCLUDE
#define ARENA_INCLUDE

#include <string>

#include <../cell/cell.hpp>

using namespace std;

// arena_type represents different types of datasets
// that the algorithm will be tested on.
enum arena_type {
  ARENA_CUSTOM,
  ARENA_MOVING_AI
};

// arena is a a simple parser for different dataset types.
// it is the outside world for a robot for simulation.
class arena {
  private:
    cell_type** graph;
    void parse_custom(string& filepath);
    void parse_movingai(string& scenepath, string& root, int test_index);

  public:
    int bucket; // bucket is a group of tests for the same map
    cell start;
    cell destination;
    int width;
    int height;

    arena();
    arena(string& filepath, arena_type map_type);
    arena(string& scenepath, string& root, int test_index, arena_type map_type);
    cell_type get(int i, int j);
    void set(int i, int j, cell_type type);
    void clear();
};

#endif