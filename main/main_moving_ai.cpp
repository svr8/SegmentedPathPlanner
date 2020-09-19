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

const int ALPHA = 5;
const string TEST_PATH_PREFIX = "tests/grids/moving_ai/game_dragon_age_origins/alpha5/";
const string application = "game_dragon_age_origins/";
const string SCENE_PATH_PREFIX = "datasets/grids/moving_ai/game_dragon_age_origins/benchmark-probems/";

void solve_map_astar(string scenepath, string root, string map_name, int test_index, ofstream &output_file) {
    arena env = arena(scenepath, root, test_index, ARENA_MOVING_AI);
    robot_astar bot = robot_astar(env);

    int path_length;
    vector<cell> path;
    
    bot.set_pos(env.start);
    auto start_time = chrono::steady_clock::now();
    path = bot.move(env.destination);
    auto end_time = chrono::steady_clock::now();
    auto diff_time = end_time - start_time;
    path_length = path.size() - 1;

    output_file << env.bucket << ", " << map_name << ", " << path_length << ", " << chrono::duration <double, milli> (diff_time).count() << '\n';
    cout << "a_star: " << env.bucket << ", " << map_name << ", " << path_length << ", " << chrono::duration <double, milli> (diff_time).count() << '\n';
}

int main() {

    string output_path;
    ofstream output_file;

    output_path = TEST_PATH_PREFIX + "a_star.csv";
    output_file.open(output_path);
    output_file << "Bucket, Map Name, Path Length, Time(ms)" << endl;
    string map = "arena.map.scen";
    string scenepath = SCENE_PATH_PREFIX + map;
    solve_map_astar(scenepath, application, map, 0, output_file);
    output_file.flush();
    output_file.close();

    return 0;
}