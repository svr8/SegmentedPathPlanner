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
    delete[] scanned_env[i];
    delete[] dist[i];
    delete[] parent[i];
    path.clear();
  }
  delete[] scanned_env;
  delete[] dist;
  delete[] parent;
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
  return (
    cur_pos.row == destination.row && 
    cur_pos.col == destination.col
  );
}

bool robot_dj::is_deadend(cell &destination) {
  return (
    cur_pos.row==-1 || 
    cur_pos.col==-1 || 
    scanned_env[destination.row][destination.col] == BLOCK
  );
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

  cell segment;
  double minD;
  cell next_pos;
  int i0, j0, i1, j1, p;
  const int max_alpha = max(env.width, env.height);
  const int copy_alpha = alpha;

  while(!found) {
    segment = get_next_segment(destination, alpha);
    
    for(int i=0;i<TOTAL_CELLS;i++) {
      // get minimum distance cell
      minD = INF;
      next_pos = cell();
      i0 = max(0, cur_pos.row-alpha);
      i1 = min(env.height, cur_pos.row+alpha);
      j0 = max(0, cur_pos.col-alpha);
      j1 = min(env.width, cur_pos.col+alpha);
      for(int i=i0;i<i1;i++) {
        for(int j=j0;j<j1;j++) {
          if(scanned_env[i][j] == FREE && dist[i][j] < minD) {
            minD = dist[i][j];
            next_pos = cell(i,j);
          }
        }
      }

      // update current position
      cur_pos = next_pos;
      if(cur_pos.row==-1 && alpha<max_alpha) {
        alpha += 5;
        continue;
      }
      if(is_deadend(destination))
        break;
      scanned_env[cur_pos.row][cur_pos.col] = VISITED;

      // destination check
      found = is_destination_reached(destination);
      if(found || is_destination_reached(segment))
        break;

      // update environment
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

cell robot_dj::get_next_segment(cell &destination, int &alpha) {
  cell res;
  res.row = cur_pos.row;
  res.col = cur_pos.col;

  cell t;
  double d1 = res.euclidean_distance(destination);
  double d2;
  bool flag = true;

  for(int i=cur_pos.row-alpha; i<=cur_pos.row+alpha; i+=alpha) {
    for(int j=cur_pos.col-alpha; j<=cur_pos.col+alpha; j+=alpha) {
      if(i>=0 && j>=0 && i<env.height && j<env.width) {
        t.row = i;
        t.col = j;
        d2 = t.euclidean_distance(destination);
        if(d2<d1) {
          res.row = t.row;
          res.col = t.col;
          d1 = d2;
          flag = false;
        }
      }
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

  double d = dist[cur_pos.row][cur_pos.col] + cur_pos.euclidean_distance(c);
  if(d < dist[row][col]) {
    dist[row][col] = d;

    if(!parent[cur_pos.row][cur_pos.col].is_equal(c))
      parent[row][col] = cell(cur_pos.row, cur_pos.col);
  }

  if(scanned_env[row][col] == UNVISITED)
    scanned_env[row][col] = env.get(row,col);
}