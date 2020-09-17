#include <vector>
#include <iostream>
#include <string>

#include <robot_dj.hpp>
#include <../arena/arena.hpp>
#include <../cell/cell.hpp>

using namespace std;

robot_dj::robot_dj(arena a) {
  env = a;
  cur_pos = cell(env.start.row, env.start.col);

  scanned_env = new cell_type*[env.height]; // robot_dj memory of arena
  dist = new double*[env.height]; // distance matrix
  parent = new cell*[env.height]; // parent matrix

  const double INF = 10000000;
  for(int i=0;i<env.height;i++) {
    scanned_env[i] = new cell_type[env.width];
    dist[i] = new double[env.width];
    parent[i] = new cell[env.width];

    for(int j=0;j<env.width;j++) {
      // initialise arena memory
      scanned_env[i][j] = UNVISITED;

      // initialise distance matrix
      dist[i][j] = INF;

      // initialise parent matrix
      parent[i][j] = cell(i, j);
    }
  }

  // initialise start positions
  scanned_env[cur_pos.row][cur_pos.col] = FREE;
  dist[cur_pos.row][cur_pos.col] = 0;
}

robot_dj::~robot_dj() {
  for(int i=0;i<env.height;i++) {
    delete scanned_env[i];
    delete dist[i];
    delete parent[i];
    path.clear();
  }
}

void robot_dj::set_pos(cell pos) {
  cur_pos = pos;
}

void robot_dj::reset_memory() {
  cur_pos = cell(env.start.row, env.start.col);

  // reset values
  const double INF = 10000000;

  for(int i=0;i<env.height;i++) {

    for(int j=0;j<env.width;j++) {
      // initialise arena memory
      scanned_env[i][j] = UNVISITED;

      // initialise distance matrix
      dist[i][j] = INF;

      // initialise parent matrix
      parent[i][j] = cell(i, j);
    }
  }

  // initialise start positions
  scanned_env[cur_pos.row][cur_pos.col] = FREE;
  dist[cur_pos.row][cur_pos.col] = 0;

  // clear path
  path.clear();
}

bool robot_dj::is_destination_reached(cell &destination) {
  return (cur_pos.row == destination.row && cur_pos.col == destination.col);
}

bool robot_dj::is_deadend(cell &destination) {
  // test("#12", destination.row>=0);
  // test("#13", destination.col>=0);
  // test("#14", destination.row<env.height);
  // test("#15", destination.col<env.width);

  return (cur_pos.row==-1 || cur_pos.col==-1 || scanned_env[destination.row][destination.col] == BLOCK);
}

void robot_dj::generate_path(cell target) {
  path.push_back(target);

  while(!target.is_equal(parent[target.row][target.col])) {
    target = parent[target.row][target.col];
    path.push_back(target);
  }
}

vector<cell> robot_dj::move(cell destination) {

  const double INF = 10000000;
  const int TOTAL_CELLS = env.width * env.height * 100;
  bool found = false;

  double minD;
  cell next_pos;
  for(int i=0;i<TOTAL_CELLS;i++) {

    minD = INF;
    next_pos = cell();

    // get minimum distance cell
    for(int i=0;i<env.height;i++) {
      for(int j=0;j<env.width;j++) {
        if(scanned_env[i][j] == FREE && dist[i][j] < minD) {
          minD = dist[i][j];
          next_pos = cell(i,j);
        }
      }
    }

    cur_pos = next_pos;

    // deadend check
    if(is_deadend(destination))
      break;

    scanned_env[cur_pos.row][cur_pos.col] = VISITED;

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

vector<cell> robot_dj::move_segmented(cell destination, int alpha) {

  const double INF = 10000000;
  const int TOTAL_CELLS = env.width * env.height*100;
  bool found = false;

  cell layer0_destination;
  double minD;
  cell next_pos;
  int i0, j0, i1, j1, p;
  const int max_alpha = max(env.width, env.height);
  const int copy_alpha = alpha;

  while(!found) {
    layer0_destination = get_layer0_destination(destination, alpha);
    
    for(int i=0;i<TOTAL_CELLS;i++) {
      minD = INF;
      next_pos = cell();

      // get minimum distance cell
      i0 = max(0, cur_pos.row-alpha);
      i1 = min(env.height, cur_pos.row+alpha);
      j0 = max(0, cur_pos.col-alpha);
      j1 = min(env.width, cur_pos.col+alpha);
      for(int i=i0;i<i1;i++) {
        for(int j=j0;j<j1;j++) {
          // test("#0",i>=0);
          // test("#1", j>=0);
          // test("#2", i<env.height);
          // test("#3", j<env.width);

          if(scanned_env[i][j] == FREE && dist[i][j] < minD) {
            minD = dist[i][j];
            next_pos = cell(i,j);
          }
        }
      }

      cur_pos = next_pos;
      if(cur_pos.row==-1 && alpha<max_alpha) {
        alpha += 5;
        continue;
      }

      if(is_deadend(destination))
        break;

      // test("#4", cur_pos.row>=0);
      // test("#5", cur_pos.col>=0);
      // test("#6", cur_pos.row<env.height);
      // test("#7", cur_pos.col<env.width);
      scanned_env[cur_pos.row][cur_pos.col] = VISITED;

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

cell robot_dj::get_layer0_destination(cell &destination, int &alpha) {
  cell res;
  res.row = cur_pos.row;
  res.col = cur_pos.col;

  cell t;
  double d1 = res.euclidean_distance(destination);
  double d2;
  bool flag = true;

  // bottom left
  if(cur_pos.row-alpha>=0 && cur_pos.col-alpha>=0) {
    t.row = cur_pos.row-alpha;
    t.col = cur_pos.col-alpha;
    d2 = t.euclidean_distance(destination);
    if(d2<d1) {
      res.row = t.row;
      res.col = t.col;
      d1 = d2;
      flag = false;
    }
  }
 
  // bottom
  if(cur_pos.row-alpha>=0) {
    t.row = cur_pos.row-alpha;
    t.col = cur_pos.col;
    d2 = t.euclidean_distance(destination);
    if(d2<d1) {
      res.row = t.row;
      res.col = t.col;
      d1 = d2;
      flag = false;
    }
  }
 
  // bottom right
  if(cur_pos.row-alpha>=0 && cur_pos.col+alpha<env.width) {
    t.row = cur_pos.row-alpha;
    t.col = cur_pos.col+alpha;
    d2 = t.euclidean_distance(destination);
    if(d2<d1) {
      res.row = t.row;
      res.col = t.col;
      d1 = d2;
      flag = false;
    }
  }
  
  // left
  if(cur_pos.col-alpha>=0) {
    t.row = cur_pos.row;
    t.col = cur_pos.col-alpha;
    d2 = t.euclidean_distance(destination);
    if(d2<d1) {
      res.row = t.row;
      res.col = t.col;
      d1 = d2;
      flag = false;
    }
  }
  
  // right
  if(cur_pos.col+alpha<env.width) {
    t.row = cur_pos.row;
    t.col = cur_pos.col+alpha;
    d2 = t.euclidean_distance(destination);
    if(d2<d1) {
      res.row = t.row;
      res.col = t.col;
      d1 = d2;
      flag = false;
    }
  }
  
  // top left
  if(cur_pos.row+alpha<env.height && cur_pos.col-alpha>=0) {
    t.row = cur_pos.row+alpha;
    t.col = cur_pos.col-alpha;
    d2 = t.euclidean_distance(destination);
    if(d2<d1) {
      res.row = t.row;
      res.col = t.col;
      d1 = d2;
      flag = false;
    }
  }
  
  // top
  if(cur_pos.row+alpha<env.height) {
    t.row = cur_pos.row+alpha;
    t.col = cur_pos.col;
    d2 = t.euclidean_distance(destination);
    if(d2<d1) {
      res.row = t.row;
      res.col = t.col;
      d1 = d2;
      flag = false;
    }
  }

  // top right
  if(cur_pos.row+alpha<env.height && cur_pos.col+alpha<env.width) {
    t.row = cur_pos.row+alpha;
    t.col = cur_pos.col+alpha;
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
void robot_dj::scan_arena() {
  cell c = cell(0,0);

  // bottom left
  if(cur_pos.row-1>=0 && cur_pos.col-1>=0) {
    c.row = cur_pos.row-1;
    c.col = cur_pos.col-1;
    scan_cell(c);
  }
  
  // bottom
  if(cur_pos.row-1>=0) {
    c.row = cur_pos.row-1;
    c.col = cur_pos.col;
    scan_cell(c);
  }

  // bottom right
  if(cur_pos.row-1>=0 && cur_pos.col+1<env.width) {
    c.row = cur_pos.row-1;
    c.col = cur_pos.col+1;
    scan_cell(c);
  }
  
  // left
  if(cur_pos.col-1>=0) {
    c.col = cur_pos.row;
    c.col = cur_pos.col-1;
    scan_cell(c);
  }
  
  // right
  if(cur_pos.col+1<env.width) {
    c.row = cur_pos.row;
    c.col = cur_pos.col+1;
    scan_cell(c);
  }

  // top left
  if(cur_pos.row+1<env.height && cur_pos.col-1>=0) {
    c.row = cur_pos.row+1;
    c.col = cur_pos.col-1;
    scan_cell(c);
  }

  // top
  if(cur_pos.row+1<env.height) {
    c.row = cur_pos.row+1;
    c.col = cur_pos.col;
    scan_cell(c);
  }

  // top right
  if(cur_pos.row+1<env.height && cur_pos.col+1>=0) {
    c.row = cur_pos.row+1;
    c.col = cur_pos.col+1;
    scan_cell(c);
  }
}

void robot_dj::scan_cell(cell c) {
  int row = c.row;
  int col = c.col;

  // test("#8", row>=0);
  // test("#9", col>=0);
  // test("#10", row<env.height);
  // test("#11", col<env.width);

  double d = dist[cur_pos.row][cur_pos.col] + cur_pos.euclidean_distance(c);
  if(d < dist[row][col]) {
    dist[row][col] = d;

    if(!parent[cur_pos.row][cur_pos.col].is_equal(c))
      parent[row][col] = cell(cur_pos.row, cur_pos.col);
  }

  if(scanned_env[row][col] == UNVISITED)
    scanned_env[row][col] = env.get(row,col);
}

void robot_dj::test(string message, bool flag) {
  if(!flag) {
    cout << message << endl;
    abort();
  }
}