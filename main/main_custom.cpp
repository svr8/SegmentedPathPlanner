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
const int map_count = 1000;

void print_path(int &path_length, vector<cell> &path) {
  cout << path_length << '\n'; 
  for(int i=path.size()-1;i>=0;i--)
    cout << path[i].col << " " << path[i].row << '\n';
}

void solve_map_dijkstra(string input_path, ofstream &output_file) {
  arena env = arena(input_path, ARENA_CUSTOM);
  robot_dj bot = robot_dj(env);
  int path_length;
  vector<cell> path;
  
  bot.set_pos(env.start);
  auto start_time = chrono::steady_clock::now();
  path = bot.move(env.destination);
  auto end_time = chrono::steady_clock::now();
  auto diff_time = end_time - start_time;
  path_length = path.size();

  output_file << input_path << ", " << path_length << ", " << chrono::duration <double, milli> (diff_time).count() << '\n';
  cout << "dijkstra: " << input_path << ", " << path_length << ", " << chrono::duration <double, milli> (diff_time).count() << '\n';
  
  // for visualisation
  // print_path(path_length, path);
}

void solve_map_dijkstra_segmented(string input_path, ofstream &output_file) {
  arena env = arena(input_path, ARENA_CUSTOM);
  robot_dj bot = robot_dj(env);
  int path_length;
  vector<cell> path;
  
  bot.set_pos(env.start);
  auto start_time = chrono::steady_clock::now();
  path = bot.move_segmented(env.destination, ALPHA);
  auto end_time = chrono::steady_clock::now();
  auto diff_time = end_time - start_time;
  path_length = path.size();

  output_file << input_path << ", " << path_length << ", " << chrono::duration <double, milli> (diff_time).count() << '\n';
  cout << "dijkstra_segmented: " << input_path << ", " << path_length << ", " << chrono::duration <double, milli> (diff_time).count() << '\n';

  // for visualisation
  // print_path(path_length, path);
}

void solve_map_astar(string input_path, ofstream &output_file) {
  arena env = arena(input_path, ARENA_CUSTOM);
  robot_astar bot = robot_astar(env);
  int path_length;
  vector<cell> path;
  
  bot.set_pos(env.start);
  auto start_time = chrono::steady_clock::now();
  path = bot.move(env.destination);
  auto end_time = chrono::steady_clock::now();
  auto diff_time = end_time - start_time;
  path_length = path.size();

  output_file << input_path << ", " << path_length << ", " << chrono::duration <double, milli> (diff_time).count() << '\n';
  cout << "a_star: " << input_path << ", " << path_length << ", " << chrono::duration <double, milli> (diff_time).count() << '\n';
  
  // for visualisation
  // print_path(path_length, path);
}

void solve_map_astar_segmented(string input_path, ofstream &output_file) {
  arena env = arena(input_path, ARENA_CUSTOM);
  robot_astar bot = robot_astar(env);
  int path_length;
  vector<cell> path;
  
  bot.set_pos(env.start);
  auto start_time = chrono::steady_clock::now(); 
  path = bot.move_segmented(env.destination, ALPHA);
  auto end_time = chrono::steady_clock::now();
  auto diff_time = end_time - start_time;
  path_length = path.size();
 
  output_file << input_path << ", " << path_length << ", " << chrono::duration <double, milli> (diff_time).count() << '\n';
  cout << "a_star_segmented: " << input_path << ", " << path_length << ", " << chrono::duration <double, milli> (diff_time).count() << '\n';

  // for visualisation
  // print_path(path_length, path);
}

void solve_map_pqdj(string input_path, ofstream &output_file) {
  arena env = arena(input_path, ARENA_CUSTOM);
  robot_astar bot = robot_astar(env);
  int path_length;
  vector<cell> path;
  
  bot.set_pos(env.start);
  auto start_time = chrono::steady_clock::now();
  path = bot.move(env.destination);
  auto end_time = chrono::steady_clock::now();
  auto diff_time = end_time - start_time;
  path_length = path.size();

  output_file << input_path << ", " << path_length << ", " << chrono::duration <double, milli> (diff_time).count() << '\n';
  cout << "pqdj: " << input_path << ", " << path_length << ", " << chrono::duration <double, milli> (diff_time).count() << '\n';
  
  // for visualisation
  // print_path(path_length, path);
}

void solve_map_pqdj_segmented(string input_path, ofstream &output_file) {
  arena env = arena(input_path, ARENA_CUSTOM);
  robot_astar bot = robot_astar(env);
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

void test_a_star() {
    string output_path;
    ofstream output_file;

    output_path = TEST_PATH_PREFIX + "a_star.csv";
    output_file.open(output_path);
    output_file << "Map Label, Path Length, Time (ms)\n";
    for(int i=0;i<map_count;i++) {
      string input_path = MAP_PATH_PREFIX + to_string(i);
      solve_map_astar(input_path, output_file);
    }

    output_file.flush();
    output_file.close();
}

void test_a_star_segmented() {
    string output_path;
    ofstream output_file;

    output_path = TEST_PATH_PREFIX + "a_star_segmented.csv";
    output_file.open(output_path);
    output_file << "Map Label, Path Length, Time (ms)\n";
    for(int i=0;i<map_count;i++) {
      string input_path = MAP_PATH_PREFIX + to_string(i);
      solve_map_astar_segmented(input_path, output_file);
    }

    output_file.flush();
    output_file.close();
}

void test_dijkstra() {
    string output_path;
    ofstream output_file;

    output_path = TEST_PATH_PREFIX + "dijkstra.csv";
    output_file.open(output_path);
    output_file << "Map Label, Path Length, Time (ms)\n";
    for(int i=0;i<map_count;i++) {
      string input_path = MAP_PATH_PREFIX + to_string(i);
      solve_map_dijkstra(input_path, output_file);
    }

    output_file.flush();
    output_file.close();
}

void test_dijkstra_segmented() {
    string output_path;
    ofstream output_file;

    output_path = TEST_PATH_PREFIX + "dijkstra_segmented.csv";
    output_file.open(output_path);
    output_file << "Map Label, Path Length, Time (ms)\n";
    for(int i=0;i<map_count;i++) {
      string input_path = MAP_PATH_PREFIX + to_string(i);
      solve_map_dijkstra_segmented(input_path, output_file);
    }

    output_file.flush();
    output_file.close();
}

void test_pqdj() {
    string output_path;
    ofstream output_file;

    output_path = TEST_PATH_PREFIX + "pq_dijkstra.csv";
    output_file.open(output_path);
    output_file << "Map Label, Path Length, Time (ms)\n";
    for(int i=0;i<map_count;i++) {
      string input_path = MAP_PATH_PREFIX + to_string(i);
      solve_map_pqdj(input_path, output_file);
    }

    output_file.flush();
    output_file.close();
}

void test_pqdj_segmented() {
    string output_path;
    ofstream output_file;
    
    output_path = TEST_PATH_PREFIX + "pq_dijkstra_segmented.csv";
    output_file.open(output_path);
    output_file << "Map Label, Path Length, Time (ms)\n";
    for(int i=0;i<map_count;i++) {
      string input_path = MAP_PATH_PREFIX + to_string(i);
      solve_map_pqdj_segmented(input_path, output_file);
    }

    output_file.flush();
    output_file.close();
}

int main() {
  test_a_star();
  test_a_star_segmented();
  test_dijkstra();
  test_dijkstra_segmented();
  test_pqdj();
  test_pqdj_segmented();
  
  

  return 0;
}