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
const string TEST_PATH_PREFIX = "tests/grids/moving_ai/game_dragon_age_origins/alpha10/";

const string application = "game_dragon_age_origins/";
const string SCENE_PATH_PREFIX = "datasets/grids/moving_ai/game_dragon_age_origins/benchmark-probems/";

const string scene_list[] = {  
    "oth001d.map.scen",
    "oth999d.map.scen",
    "rmtst01.map.scen",
    "rmtst03.map.scen",
    "rmtst.map.scen"
};

int get_scene_tests_count(string scenepath) {
    ifstream scenefile(scenepath);
    string line;
    int tests = 0;

    // skip version line
    getline(scenefile, line);

    // count tests
    while(getline(scenefile, line)) tests++;

    return tests;
}

void print_path(int &path_length, vector<cell> &path) {
  cout << path_length << '\n'; 
  for(int i=path.size()-1;i>=0;i--)
    cout << path[i].col << " " << path[i].row << '\n';
}


void solve_map_pqdj(string scenepath, string root, string map_name, ofstream &output_file) {
    int test_count = get_scene_tests_count(scenepath);

    for(int test_index=0; test_index<test_count; test_index++) {
        arena env = arena(scenepath, root, test_index, ARENA_MOVING_AI);
        robot_pqdj bot = robot_pqdj(env);

        int path_length;
        vector<cell> path;
        
        bot.set_pos(env.start);
        auto start_time = chrono::steady_clock::now();
        path = bot.move(env.destination);
        auto end_time = chrono::steady_clock::now();
        auto diff_time = end_time - start_time;
        path_length = path.size();

        output_file << env.bucket << ", " << map_name << ", " << path_length << ", " << chrono::duration <double, milli> (diff_time).count() << '\n';
        cout << "pq_dijkstra: " << (test_index+1) <<"/" << test_count << " " << env.bucket << ", " << map_name << ", " << path_length << ", " << chrono::duration <double, milli> (diff_time).count() << '\n';

        env.clear();
    }
}


int main() {
  
  string output_path;
  ofstream output_file;

  // Priority Queue based Dijkstra
    output_path = TEST_PATH_PREFIX + "pq_dijkstra (1).csv";
    output_file.open(output_path);
    output_file << "Bucket, Map Name, Path Length, Time(ms)" << endl;
    for(int i=0;i<5;i++) {
        string map = scene_list[i];
        string scenepath = SCENE_PATH_PREFIX + map;
        solve_map_pqdj(scenepath, application, map, output_file);
    }
    output_file.flush();
    output_file.close();


  
  return 0;
}