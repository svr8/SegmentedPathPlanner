#ifndef ROBOT_PQDJ_INCLUDE
#define ROBOT_PQDJ_INCLUDE

#include <vector>
#include <queue>

#include <../cell/cell.hpp>
#include <../node/node_pqdj.hpp>
#include <../arena/arena.hpp>

using namespace std;

// robot_pqdj solves path planning problem using PriorityQueue based Dijkstra and 
// PriorityQueue based Segmented Dijkstra(Proposed) algorithms.

class robot_pqdj {
  private:
    arena env;
    node_pqdj cur_node;
    priority_queue<node_pqdj, vector<node_pqdj>, node_compare> scanned_env;
    cell_type **cell_state;
    double **dist;
    vector<cell> path;
    cell **parent;

    bool is_destination_reached(cell &destination);
    bool is_deadend(cell &destination);
    cell get_next_segment(cell &destination, int &alpha);
    void generate_path(cell target);

  public:
    robot_pqdj(arena a);
    ~robot_pqdj();
    void set_pos(cell pos);
    void reset_memory();
    vector<cell> move(cell destination);
    vector<cell> move_segmented(cell destination, int alpha);
    void scan_arena();
    void scan_cell(cell c);
};

#endif