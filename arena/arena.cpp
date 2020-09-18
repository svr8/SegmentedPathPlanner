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
  c = stoi(st.next());
  r = stoi(st.next());
  start = cell(r, c);

  // // input destination cell
  getline(file, line);
  st = string_tokenizer(line, ' ');
  c = stoi(st.next());
  r = stoi(st.next());
  destination = cell(r, c);
}

cell_type arena::get(int i, int j) {
  return graph[i][j];
}

void arena::set(int i, int j, cell_type type) {
  graph[i][j] = type;
}
