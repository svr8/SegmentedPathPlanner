#ifndef ROBOT_ASTAR_INCLUDE
#define ROBOT_ASTAR_INCLUDE

#include <vector>
#include <queue>

#include <../cell/cell.hpp>
#include <../node/node_astar.hpp>
#include <../arena/arena.hpp>

// robot_astar solves path planning problem using A* and Segmented A*(Proposed) algorithms.
using namespace std;

class robot_astar {
  private:
    arena env;
    node_astar cur_node;
    priority_queue<node_astar, vector<node_astar>, node_compare_on_f> open_list;
    priority_queue<node_astar, vector<node_astar>, node_compare_on_f> closed_list;
    double **open_list_state;
    double **closed_list_state;
    bool found;
    vector<cell> path;
    cell **parent;

    void generate_path(cell target);

  public:
    robot_astar(arena a);
    ~robot_astar();
    void set_pos(cell pos);
    vector<cell> move(cell destination);
    vector<cell> move_segmented(cell destination, int alpha);
    cell get_next_segment(cell &destination, int &alpha);
    void scan_arena(cell &destination);
    void scan_cell(cell c, cell &destination);
};

#endif