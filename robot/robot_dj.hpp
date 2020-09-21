#ifndef ROBOT_DJ_INCLUDE
#define ROBOT_DJ_INCLUDE

#include <vector>

#include <../cell/cell.hpp>
#include <../arena/arena.hpp>

using namespace std;

// robot_dj solves path planning problem using Dijkstra and Segmented Dijkstra(Proposed) algorithms.

class robot_dj {
  private:
    arena env;
    cell cur_pos;
    cell_type **scanned_env;
    double **dist;
    vector<cell> path;
    cell **parent;

    bool is_destination_reached(cell &destination);
    bool is_deadend(cell &destination);
    cell get_next_segment(cell &destination, int &alpha);
    void generate_path(cell target);

  public:
    robot_dj(arena a);
    ~robot_dj();
    void set_pos(cell pos);
    void reset_memory();
    vector<cell> move(cell destination);
    vector<cell> move_segmented(cell destination, int alpha);
    void scan_arena();
    void scan_cell(cell c);
};

#endif