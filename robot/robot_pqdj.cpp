#include <vector>
#include <iostream>
#include <string>
#include <queue>

#include <robot_pqdj.hpp>
#include <../arena/arena.hpp>
#include <../cell/cell.hpp>
#include <../node/node_pqdj.hpp>

using namespace std;

robot_pqdj::robot_pqdj(arena a) {
  env = a;
  cur_node = node_pqdj(env.start.row, env.start.col, 0);

  cell_state = new cell_type*[env.height]; // cell type history in robot_pqdj memory

  dist = new double*[env.height]; // distance matrix
  parent = new cell*[env.height]; // parent matrix

  const double INF = 10000000;
  for(int i=0;i<env.height;i++) {
    dist[i] = new double[env.width];
    parent[i] = new cell[env.width];
    cell_state[i] = new cell_type[env.width];

    for(int j=0;j<env.width;j++) {
      // initialise arena memory
      cell_state[i][j] = UNVISITED;

      // initialise distance matrix
      dist[i][j] = INF;

      // initialise parent matrix
      parent[i][j] = cell(i, j);
    }
  }

  cell_state[cur_node.pos.row][cur_node.pos.col] = FREE;
  dist[cur_node.pos.row][cur_node.pos.col] = 0;
}

robot_pqdj::~robot_pqdj() {
  for(int i=0;i<env.height;i++) {
    delete[] cell_state[i];
    delete[] dist[i];
    delete[] parent[i];
  }
  
  delete[] cell_state;
  delete[] dist;
  delete[] parent;
  path.clear();
}


void robot_pqdj::set_pos(cell pos) {
  cur_node.pos = pos;
}

void robot_pqdj::reset_memory() {

  cur_node = node_pqdj(env.start.row, env.start.col, 0);

  // reset values
  const double INF = 10000000;
  cell_state = new cell_type*[env.height]; /// cell type history in robot_pqdj memory
  dist = new double*[env.height]; // distance matrix

  for(int i=0;i<env.height;i++) {
    cell_state[i] = new cell_type[env.width];
    dist[i] = new double[env.width];

    for(int j=0;j<env.width;j++) {
      // initialise arena memory
      cell_state[i][j] = UNVISITED;

      // initialise distance matrix
      dist[i][j] = INF;
     
      // initialise parent matrix
      parent[i][j] = cell(i, j);
    }
  }

  // initialise start positions
  cell_state[cur_node.pos.row][cur_node.pos.col] = FREE;
  dist[cur_node.pos.row][cur_node.pos.col] = 0;

  // reset environment history
  scanned_env = priority_queue<node_pqdj, vector<node_pqdj>, node_compare>();

  // clear path
  path.clear();
}

bool robot_pqdj::is_destination_reached(cell &destination) {
  return (cur_node.pos.row == destination.row && cur_node.pos.col == destination.col);
}

bool robot_pqdj::is_deadend(cell &destination) {
  // test("#12", destination.row>=0);
  // test("#13", destination.col>=0);
  // test("#14", destination.row<env.height);
  // test("#15", destination.col<env.width);

  return (cur_node.pos.row==-1 || cur_node.pos.col==-1 || cell_state[destination.row][destination.col] == BLOCK);
}

void robot_pqdj::generate_path(cell target) {
  path.push_back(target);

  while(!target.is_equal(parent[target.row][target.col])) {
    target = parent[target.row][target.col];
    path.push_back(target);
  }
}

vector<cell> robot_pqdj::move(cell destination) {

  const double INF = 10000000;
  const int TOTAL_CELLS = env.width * env.height * 100;
  bool found = false;

  double minD;
  node_pqdj next_node = node_pqdj(cur_node.pos.row, cur_node.pos.col, 0);
  scanned_env.push(next_node);

  for(int i=0;i<TOTAL_CELLS;i++) {

    minD = INF;
    next_node = node_pqdj();

    while(!scanned_env.empty()) {
      next_node = scanned_env.top();
      scanned_env.pop();
      if(cell_state[next_node.pos.row][next_node.pos.col] == FREE)
        break;
    }

    cur_node = next_node;

    // deadend check
    if(is_deadend(destination))
      break;

    // update robot_pqdj memory
    cell_state[cur_node.pos.row][cur_node.pos.col] = VISITED;

    // destination check
    if(is_destination_reached(destination)) {
      found = true;
      break;
    }

    scan_arena();    
  }

  if(found) {
    cell target = cell(destination);
    generate_path(target);
  }

  return path;
}

vector<cell> robot_pqdj::move_segmented(cell destination, int alpha) {

  const double INF = 10000000;
  const int TOTAL_CELLS = env.width * env.height*100;
  bool found = false;
  const int max_alpha = max(env.width, env.height);

  cell layer0_destination;
  double minD;
  node_pqdj next_node = node_pqdj(cur_node.pos.row, cur_node.pos.col, 0);
  scanned_env.push(next_node);
  int i0, j0, i1, j1, p;

  while(!found) {
    layer0_destination = get_layer0_destination(destination, alpha);

    for(int i=0;i<TOTAL_CELLS;i++) {
      minD = INF;
      // next_pos = cell();
      next_node = node_pqdj();

      while(!scanned_env.empty()) {
        next_node = scanned_env.top();
        scanned_env.pop();
        if(cell_state[next_node.pos.row][next_node.pos.col] == FREE)
          break;
      }

      // cur_pos = next_pos;
      cur_node = next_node;
      if(cur_node.pos.row==-1 && alpha<max_alpha) {
        alpha += 5;
        continue;
      }

      if(is_deadend(destination))
        break;

      // test("#4", cur_pos.row>=0);
      // test("#5", cur_pos.col>=0);
      // test("#6", cur_pos.row<env.height);
      // test("#7", cur_pos.col<env.width);
      cell_state[cur_node.pos.row][cur_node.pos.col] = VISITED;

      // destination check
      found = is_destination_reached(destination);
      if(found || is_destination_reached(layer0_destination))
        break;

      scan_arena();    
    }
    
    if(is_deadend(destination))
      break;
    
    scan_arena();
  }

  if(found) {
    cell target = cell(destination);
    generate_path(target);
  }

  return path;
}

cell robot_pqdj::get_layer0_destination(cell &destination, int &alpha) {
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
void robot_pqdj::scan_arena() {
  cell c = cell(0,0);

  // bottom left
  if(cur_node.pos.row-1>=0 && cur_node.pos.col-1>=0) {
    c.row = cur_node.pos.row-1;
    c.col = cur_node.pos.col-1;
    scan_cell(c);
  }
  
  // bottom
  if(cur_node.pos.row-1>=0) {
    c.row = cur_node.pos.row-1;
    c.col = cur_node.pos.col;
    scan_cell(c);
  }

  // bottom right
  if(cur_node.pos.row-1>=0 && cur_node.pos.col+1<env.width) {
    c.row = cur_node.pos.row-1;
    c.col = cur_node.pos.col+1;
    scan_cell(c);
  }
  
  // left
  if(cur_node.pos.col-1>=0) {
    c.col = cur_node.pos.row;
    c.col = cur_node.pos.col-1;
    scan_cell(c);
  }
  
  // right
  if(cur_node.pos.col+1<env.width) {
    c.row = cur_node.pos.row;
    c.col = cur_node.pos.col+1;
    scan_cell(c);
  }

  // top left
  if(cur_node.pos.row+1<env.height && cur_node.pos.col-1>=0) {
    c.row = cur_node.pos.row+1;
    c.col = cur_node.pos.col-1;
    scan_cell(c);
  }

  // top
  if(cur_node.pos.row+1<env.height) {
    c.row = cur_node.pos.row+1;
    c.col = cur_node.pos.col;
    scan_cell(c);
  }

  // top right
  if(cur_node.pos.row+1<env.height && cur_node.pos.col+1>=0) {
    c.row = cur_node.pos.row+1;
    c.col = cur_node.pos.col+1;
    scan_cell(c);
  }
}

void robot_pqdj::scan_cell(cell c) {
  int row = c.row;
  int col = c.col;

  // test("#8", row>=0);
  // test("#9", col>=0);
  // test("#10", row<env.height);
  // test("#11", col<env.width);

  double d = dist[cur_node.pos.row][cur_node.pos.col] + cur_node.pos.euclidean_distance(c);
  if(d < dist[row][col]) {
    dist[row][col] = d;

    if(!parent[cur_node.pos.row][cur_node.pos.col].is_equal(c))
      parent[row][col] = cell(cur_node.pos.row, cur_node.pos.col);
    
    node_pqdj n = node_pqdj(row, col, d);
    scanned_env.push(n);
  }

  if(cell_state[row][col] == UNVISITED)
    cell_state[row][col] = env.get(row,col);
}

void robot_pqdj::test(string message, bool flag) {
  if(!flag) {
    cout << message << endl;
    abort();
  }
}