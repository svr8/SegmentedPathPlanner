#include <iostream>
#include <string>
#include <fstream>

#include <arena.hpp>
#include <../string_tokenizer/string_tokenizer.hpp>

using namespace std;

arena::arena() {
}

arena::arena(string& filepath, arena_type map_type) {
  if(map_type == ARENA_CUSTOM) {
    parse_custom(filepath);
  }
}

arena::arena(string& scenepath, string& root, int test_index, arena_type map_type) {
  if(map_type == ARENA_MOVING_AI) {
    parse_movingai(scenepath, root, test_index);
  }
}

void arena::parse_custom(string& filepath) {
  ifstream file(filepath);
  string line;
  string_tokenizer st;
  int r, c;
 
  // input width, height
  getline(file, line);
  st = string_tokenizer(line, ' ');
  width = stoi(st.next());
  height = stoi(st.next());
 
  // input graph
  graph = new cell_type*[height];
  for(int row=0;row<height;row++) {
    getline(file, line);
    graph[row] = new cell_type[width];
 
    for(int col=0;col<width;col++) {
      graph[row][col] = line[col] == '0' ? FREE : BLOCK;
    }
  }
 
  // input start cell
  getline(file, line);
  st = string_tokenizer(line, ' ');
  c = stoi(st.next()); r = stoi(st.next());
  start = cell(r, c);

  // // input destination cell
  getline(file, line);
  st = string_tokenizer(line, ' ');
  c = stoi(st.next()); r = stoi(st.next());
  destination = cell(r, c);
}

void arena::parse_movingai(string& scenepath, string& root, int test_index) {
  ifstream scenefile(scenepath);
  string line;
  string_tokenizer st;
  string map_name;
  int r, c;

  // skip version line
  getline(scenefile, line);

  // jump to required test index
  for(int i=0;i<test_index;i++)
    getline(scenefile, line);
  
  // input bucket, map_name, width, height, start_cell, destination_cell
  getline(scenefile, line);
  st = string_tokenizer(line, '\t');
  bucket = stoi(st.next());
  map_name = st.next();
  
  width = stoi(st.next());
  height = stoi(st.next());
  
  c = stoi(st.next()); r = stoi(st.next());
  start = cell(r, c);
  c = stoi(st.next()); r = stoi(st.next());
  destination = cell(r, c);

  // input mapfile
  string mapfilepath = "datasets/grids/moving_ai/" + root + "maps/" + map_name;
  ifstream mapfile(mapfilepath);

  // skip type line
  getline(mapfile, line);

  // skip height line
  getline(mapfile, line);

  // skip width line
  getline(mapfile, line);

  // skip line
  getline(mapfile, line);

  // input graph
  graph = new cell_type*[height];
  for(int row=0;row<height;row++) {
    getline(mapfile, line);
    graph[row] = new cell_type[width];

    for(int col=0;col<width;col++) {
      if(line[col] == '.' || 
         line[col] == 'G'
      ) {
        graph[row][col] = FREE;
      } else if(line[col] == '@' ||
          line[col] == '0' ||
          line[col] == 'T'
      ) {
        graph[row][col] == BLOCK;
      } else {
        cout << "INVALID MAP: " << line[col] << "found at row: " << row << ", col: " << col << "| " << map_name << endl;
        return;
      }
    }
  }
}

cell_type arena::get(int i, int j) {
  return graph[i][j];
}

void arena::set(int i, int j, cell_type type) {
  graph[i][j] = type;
}
