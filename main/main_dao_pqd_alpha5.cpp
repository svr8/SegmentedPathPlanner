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

const string scene_list[] = {  
    "arena2.map.scen",
    "arena.map.scen",
    "brc000d.map.scen",
    "brc100d.map.scen",
    "brc101d.map.scen",
    "brc200d.map.scen",
    "brc201d.map.scen",
    "brc202d.map.scen",
    "brc203d.map.scen",
    "brc204d.map.scen",
    "brc300d.map.scen",
    "brc501d.map.scen",
    "brc502d.map.scen",
    "brc503d.map.scen",
    "brc504d.map.scen",
    "brc505d.map.scen",
    "brc997d.map.scen",
    "brc999d.map.scen",
    "combat2.map.scen",
    "combat.map.scen",
    "den000d.map.scen",
    "den001d.map.scen",
    "den005d.map.scen",
    "den009d.map.scen",
    "den011d.map.scen",
    "den012d.map.scen",
    "den020d.map.scen",
    "den101d.map.scen",
    "den200d.map.scen",
    "den200n.map.scen",
    "den201d.map.scen",
    "den202d.map.scen",
    "den203d.map.scen",
    "den204d.map.scen",
    "den206d.map.scen",
    "den207d.map.scen",
    "den308d.map.scen",
    "den312d.map.scen",
    "den400d.map.scen",
    "den401d.map.scen",
    "den403d.map.scen",
    "den404d.map.scen",
    "den405d.map.scen",
    "den407d.map.scen",
    "den408d.map.scen",
    "den500d.map.scen",
    "den501d.map.scen",
    "den502d.map.scen",
    "den504d.map.scen",
    "den505d.map.scen",
    "den510d.map.scen",
    "den520d.map.scen",
    "den600d.map.scen",
    "den601d.map.scen",
    "den602d.map.scen",
    "den900d.map.scen",
    "den901d.map.scen",
    "den998d.map.scen",
    "hrt000d.map.scen",
    "hrt001d.map.scen",
    "hrt002d.map.scen",
    "hrt201d.map.scen",
    "hrt201n.map.scen",
    "isound1.map.scen",
    "lak100c.map.scen",
    "lak100d.map.scen",
    "lak100n.map.scen",
    "lak101d.map.scen",
    "lak102d.map.scen",
    "lak103d.map.scen",
    "lak104d.map.scen",
    "lak105d.map.scen",
    "lak106d.map.scen",
    "lak107d.map.scen",
    "lak108d.map.scen",
    "lak109d.map.scen",
    "lak110d.map.scen",
    "lak200d.map.scen",
    "lak201d.map.scen",
    "lak202d.map.scen",
    "lak203d.map.scen",
    "lak250d.map.scen",
    "lak300d.map.scen",
    "lak302d.map.scen",
    "lak303d.map.scen",
    "lak304d.map.scen",
    "lak307d.map.scen",
    "lak308d.map.scen",
    "lak400d.map.scen",
    "lak401d.map.scen",
    "lak403d.map.scen",
    "lak404d.map.scen",
    "lak405d.map.scen",
    "lak503d.map.scen",
    "lak504d.map.scen",
    "lak505d.map.scen",
    "lak506d.map.scen",
    "lak507d.map.scen",
    "lak510d.map.scen",
    "lak511d.map.scen",
    "lak512d.map.scen",
    "lak513d.map.scen",
    "lak514d.map.scen",
    "lak515d.map.scen",
    "lak519d.map.scen",
    "lak526d.map.scen",
    "lgt101d.map.scen",
    "lgt300d.map.scen",
    "lgt600d.map.scen",
    "lgt601d.map.scen",
    "lgt602d.map.scen",
    "lgt603d.map.scen",
    "lgt604d.map.scen",
    "lgt605d.map.scen",
    "orz000d.map.scen",
    "orz100d.map.scen",
    "orz101d.map.scen",
    "orz102d.map.scen",
    "orz103d.map.scen",
    "orz105d.map.scen",
    "orz106d.map.scen",
    "orz107d.map.scen",
    "orz200d.map.scen",
    "orz201d.map.scen",
    "orz203d.map.scen",
    "orz300d.map.scen",
    "orz301d.map.scen",
    "orz302d.map.scen",
    "orz303d.map.scen",
    "orz304d.map.scen",
    "orz500d.map.scen",
    "orz601d.map.scen",
    "orz700d.map.scen",
    "orz701d.map.scen",
    "orz702d.map.scen",
    "orz703d.map.scen",
    "orz704d.map.scen",
    "orz800d.map.scen",
    "orz900d.map.scen",
    "orz901d.map.scen",
    "orz999d.map.scen",
    "ost000a.map.scen",
    "ost000t.map.scen",
    "ost001d.map.scen",
    "ost002d.map.scen",
    "ost003d.map.scen",
    "ost004d.map.scen",
    "ost100d.map.scen",
    "ost101d.map.scen",
    "ost102d.map.scen",
    "oth000d.map.scen",
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
    output_path = TEST_PATH_PREFIX + "pq_dijkstra.csv";
    output_file.open(output_path);
    output_file << "Bucket, Map Name, Path Length, Time(ms)" << endl;
    for(int i=0;i<156;i++) {
        string map = scene_list[i];
        string scenepath = SCENE_PATH_PREFIX + map;
        solve_map_pqdj(scenepath, application, map, output_file);
    }
    output_file.flush();
    output_file.close();


  
  return 0;
}