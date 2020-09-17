#ifndef ROBOT_DJ_INCLUDE
#define ROBOT_DJ_INCLUDE

#include <vector>

#include <../cell/cell.hpp>
#include <../arena/arena.hpp>

using namespace std;

class robot_dj {
  private:
    cell cur_pos;
    arena env;
    cell_type **scanned_env;
    double **dist;
    vector<cell> path;
    cell **parent;

    bool is_destination_reached(cell &destination);
    bool is_deadend(cell &destination);
    cell get_layer0_destination(cell &destination, int &alpha);
    void generate_path(cell target);
    void test(string message, bool flag);

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