#include <vector>
#include <iostream>
#include <string>
#include <queue>

#include <robot_astar.hpp>
#include <../arena/arena.hpp>
#include <../cell/cell.hpp>
#include <../node/node_astar.hpp>

using namespace std;

robot_astar::robot_astar(arena a) {
  env = a;
  cur_node = node_astar(env.start.row, env.start.col);

  parent = new cell*[env.height]; // parent matrix
  open_list_state = new double*[env.height]; // open_list tracker
  closed_list_state = new double*[env.height]; // closed_list tracker

  for(int i=0;i<env.height;i++) {
    parent[i] = new cell[env.width];
    open_list_state[i] = new double[env.width];
    closed_list_state[i] = new double[env.width];

    for(int j=0;j<env.width;j++) {
      // initialise parent matrix
      parent[i][j] = cell(i, j);

      // initialise open_list tracker
      open_list_state[i][j] = -1;

      // initialise open_list tracker
      closed_list_state[i][j] = -1;
    }
  }

  found = false;
}

robot_astar::~robot_astar() {
  for(int i=0;i<env.height;i++) {
    delete[] open_list_state[i];
    delete[] closed_list_state[i];
    delete[] parent[i];
  }
  delete[] open_list_state;
  delete[] closed_list_state;
  delete[] parent;

  path.clear();
  open_list = priority_queue<node_astar, vector<node_astar>, node_compare_on_f>();
  closed_list = priority_queue<node_astar, vector<node_astar>, node_compare_on_f>();
}

void robot_astar::set_pos(cell pos) {
  cur_node.pos = pos;
}

void robot_astar::generate_path(cell target) {
  path.push_back(target);

  while(!target.is_equal(parent[target.row][target.col])) {
    target = parent[target.row][target.col];
    path.push_back(target);
  }
}

vector<cell> robot_astar::move(cell destination) {

  // update openlist with current position
  node_astar next_node = node_astar(cur_node.pos.row, cur_node.pos.col);
  open_list.push(next_node);
  open_list_state[next_node.pos.row][next_node.pos.col] = 0;

  while(!open_list.empty() && !found) {
    // get next node
    next_node = open_list.top();
    open_list.pop();

    while(closed_list_state[next_node.pos.row][next_node.pos.col]!=-1 && !open_list.empty()) {
      next_node = open_list.top();
      open_list.pop();
    }
    open_list_state[next_node.pos.row][next_node.pos.col] = -1;

    // update current node
    cur_node = next_node;
    found = cur_node.pos.is_equal(destination);
    
    // update environment
    scan_arena(destination);
    closed_list.push(next_node);
    closed_list_state[next_node.pos.row][next_node.pos.col] = next_node.f;   
  }

  if(found)
    generate_path(destination);
  
  return path;
}

vector<cell> robot_astar::move_segmented(cell destination, int alpha) {
  
  // update openlist
  node_astar next_node = node_astar(cur_node.pos.row, cur_node.pos.col);
  open_list.push(next_node);
  open_list_state[next_node.pos.row][next_node.pos.col] = 0;
  cell t_destination;
  bool t_found = false;

  while(!found && !open_list.empty()) {
    // calculate segment
    t_destination = get_next_segment(destination, alpha);
    t_found = false;

    while(!found && !t_found && !open_list.empty()) {
      // get next node
      next_node = open_list.top();
      open_list.pop();

      while(closed_list_state[next_node.pos.row][next_node.pos.col]!=-1 && !open_list.empty()) {
        next_node = open_list.top();
        open_list.pop();
      }
      open_list_state[next_node.pos.row][next_node.pos.col] = -1;

      // update current node
      cur_node = next_node;
      t_found = cur_node.pos.is_equal(t_destination);
      found = cur_node.pos.is_equal(destination);

      // update environment
      scan_arena(destination);      
      closed_list.push(next_node);
      closed_list_state[next_node.pos.row][next_node.pos.col] = next_node.f;   
    }

    found = cur_node.pos.is_equal(destination);
  }

  if(found)
    generate_path(destination);
  
  return path;
}

cell robot_astar::get_next_segment(cell &destination, int &alpha) {
  cell res;
  res.row = cur_node.pos.row;
  res.col = cur_node.pos.col;

  cell t;
  double d1 = res.euclidean_distance(destination);
  double d2;
  bool flag = true;

  // bottom left
  if(cur_node.pos.row-alpha>=0 && cur_node.pos.col-alpha>=0) {
    t.row = cur_node.pos.row-alpha;
    t.col = cur_node.pos.col-alpha;
    d2 = t.euclidean_distance(destination);
    if(d2<d1) {
      res.row = t.row;
      res.col = t.col;
      d1 = d2;
      flag = false;
    }
  }
 
  // bottom
  if(cur_node.pos.row-alpha>=0) {
    t.row = cur_node.pos.row-alpha;
    t.col = cur_node.pos.col;
    d2 = t.euclidean_distance(destination);
    if(d2<d1) {
      res.row = t.row;
      res.col = t.col;
      d1 = d2;
      flag = false;
    }
  }
 
  // bottom right
  if(cur_node.pos.row-alpha>=0 && cur_node.pos.col+alpha<env.width) {
    t.row = cur_node.pos.row-alpha;
    t.col = cur_node.pos.col+alpha;
    d2 = t.euclidean_distance(destination);
    if(d2<d1) {
      res.row = t.row;
      res.col = t.col;
      d1 = d2;
      flag = false;
    }
  }
  
  // left
  if(cur_node.pos.col-alpha>=0) {
    t.row = cur_node.pos.row;
    t.col = cur_node.pos.col-alpha;
    d2 = t.euclidean_distance(destination);
    if(d2<d1) {
      res.row = t.row;
      res.col = t.col;
      d1 = d2;
      flag = false;
    }
  }
  
  // right
  if(cur_node.pos.col+alpha<env.width) {
    t.row = cur_node.pos.row;
    t.col = cur_node.pos.col+alpha;
    d2 = t.euclidean_distance(destination);
    if(d2<d1) {
      res.row = t.row;
      res.col = t.col;
      d1 = d2;
      flag = false;
    }
  }
  
  // top left
  if(cur_node.pos.row+alpha<env.height && cur_node.pos.col-alpha>=0) {
    t.row = cur_node.pos.row+alpha;
    t.col = cur_node.pos.col-alpha;
    d2 = t.euclidean_distance(destination);
    if(d2<d1) {
      res.row = t.row;
      res.col = t.col;
      d1 = d2;
      flag = false;
    }
  }
  
  // top
  if(cur_node.pos.row+alpha<env.height) {
    t.row = cur_node.pos.row+alpha;
    t.col = cur_node.pos.col;
    d2 = t.euclidean_distance(destination);
    if(d2<d1) {
      res.row = t.row;
      res.col = t.col;
      d1 = d2;
      flag = false;
    }
  }

  // top right
  if(cur_node.pos.row+alpha<env.height && cur_node.pos.col+alpha<env.width) {
    t.row = cur_node.pos.row+alpha;
    t.col = cur_node.pos.col+alpha;
    d2 = t.euclidean_distance(destination);
    if(d2<d1) {
      res.row = t.row;
      res.col = t.col;
      d1 = d2;
      flag = false;
    }
  }

  if(flag) {
    res.row = destination.row;
    res.col = destination.col;
  }

  return res;
}

// update neighbour edges
void robot_astar::scan_arena(cell  &destination) {
  cell c = cell(0,0);

  // bottom left
  if(cur_node.pos.row-1>=0 && cur_node.pos.col-1>=0) {
    c.row = cur_node.pos.row-1;
    c.col = cur_node.pos.col-1;
    scan_cell(c, destination);
  }
  
  // bottom
  if(cur_node.pos.row-1>=0) {
    c.row = cur_node.pos.row-1;
    c.col = cur_node.pos.col;
    scan_cell(c, destination);
  }

  // bottom right
  if(cur_node.pos.row-1>=0 && cur_node.pos.col+1<env.width) {
    c.row = cur_node.pos.row-1;
    c.col = cur_node.pos.col+1;
    scan_cell(c, destination);
  }
  
  // left
  if(cur_node.pos.col-1>=0) {
    c.col = cur_node.pos.row;
    c.col = cur_node.pos.col-1;
    scan_cell(c, destination);
  }
  
  // right
  if(cur_node.pos.col+1<env.width) {
    c.row = cur_node.pos.row;
    c.col = cur_node.pos.col+1;
    scan_cell(c, destination);
  }

  // top left
  if(cur_node.pos.row+1<env.height && cur_node.pos.col-1>=0) {
    c.row = cur_node.pos.row+1;
    c.col = cur_node.pos.col-1;
    scan_cell(c, destination);
  }

  // top
  if(cur_node.pos.row+1<env.height) {
    c.row = cur_node.pos.row+1;
    c.col = cur_node.pos.col;
    scan_cell(c, destination);
  }

  // top right
  if(cur_node.pos.row+1<env.height && cur_node.pos.col+1>=0) {
    c.row = cur_node.pos.row+1;
    c.col = cur_node.pos.col+1;
    scan_cell(c, destination);
  }
}

void robot_astar::scan_cell(cell c, cell &destination) {
  if(env.get(c.row, c.col)==BLOCK)
    return;

  int row = c.row;
  int col = c.col;

  node_astar successor = node_astar(row, col);
  successor.g = cur_node.g + cur_node.euclidean_distance(successor);
  successor.h = c.euclidean_distance(destination);
  successor.f = successor.g + successor.h; 

  if(
      open_list_state[successor.pos.row][successor.pos.col] != -1 &&
      open_list_state[successor.pos.row][successor.pos.col] < successor.f
    ) {
      return;
    }
  
  else if( 
      closed_list_state[successor.pos.row][successor.pos.col] != -1 && 
      closed_list_state[successor.pos.row][successor.pos.col] < successor.f
    ) {
      return;
    }
  else {
    open_list_state[successor.pos.row][successor.pos.col] = successor.f;
    open_list.push(successor);
    if(!parent[cur_node.pos.row][cur_node.pos.col].is_equal(c))
          parent[row][col] = cell(cur_node.pos.row, cur_node.pos.col);
  }
}