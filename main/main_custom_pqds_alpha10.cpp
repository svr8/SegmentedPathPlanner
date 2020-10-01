#include <iostream>
#include <string>
#include <vector> 
#include <chrono>
#include <cmath>
#include <fstream>

#include <../arena/arena.hpp>
#include <../robot/robot_astar.hpp>
#include <../robot/robot_dj.hpp>
#include <../robot/robot_pqdj.hpp>

using namespace std;

const int ALPHA = 10;
const string TEST_PATH_PREFIX = "tests/grids/custom_random/maps_250x250/alpha10/";
const string MAP_PATH_PREFIX = "datasets/grids/custom_random/maps_250x250/sample";

void solve_map_pqdj_segmented(string input_path, ofstream &output_file) {
  arena env = arena(input_path, ARENA_CUSTOM);
  robot_pqdj bot = robot_pqdj(env);
  int path_length;
  vector<cell> path;
  
  bot.set_pos(env.start);
  auto start_time = chrono::steady_clock::now(); 
  path = bot.move_segmented(env.destination, ALPHA);
  auto end_time = chrono::steady_clock::now();
  auto diff_time = end_time - start_time;
  path_length = path.size();
 
  output_file << input_path << ", " << path_length << ", " << chrono::duration <double, milli> (diff_time).count() << '\n';
  cout << "pqdj_segmented: " << input_path << ", " << path_length << ", " << chrono::duration <double, milli> (diff_time).count() << '\n';

  // for visualisation
  // print_path(path_length, path);
}

int main() {
  
  string output_path;
  ofstream output_file;

  // Priority Queue Based Dijkstra Segmented
  output_path = TEST_PATH_PREFIX + "pq_dijkstra_segmented.csv";
  output_file.open(output_path);
  output_file << "Map Label, Path Length, Time (ms)\n";
  for(int i=0;i<1000;i++) {
    string input_path = MAP_PATH_PREFIX + to_string(i);
    solve_map_pqdj_segmented(input_path, output_file);
  }
  output_file.flush();
  output_file.close();

  return 0;
}