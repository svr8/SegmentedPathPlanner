#include <iostream>
#include <string>
#include <fstream>

#include <../string_tokenizer/string_tokenizer.hpp>

using namespace std;

int main() {
    ifstream a("tests/grids/moving_ai/game_dragon_age_origins/alpha5/a_star.csv");
    ifstream a_seg("tests/grids/moving_ai/game_dragon_age_origins/alpha5/a_star_segmented.csv");
    ifstream pqdj("tests/grids/moving_ai/game_dragon_age_origins/alpha5/pq_dijkstra.csv");
    ifstream pqdj_seg("tests/grids/moving_ai/game_dragon_age_origins/alpha5/pq_dijkstra_segmented.csv");

    string line_a, line_a_seg, line_pqdj, line_pqdj_seg;
    string_tokenizer st;

    // skip first line
    getline(a, line_a);
    getline(a_seg, line_a_seg);
    getline(pqdj, line_pqdj);
    getline(pqdj_seg, line_pqdj_seg);

    cout << "Test Index, Map Name, A* Path Length, A* Time(ms), A* Segmented Path Length, A* Segmented Time(ms), PQ Dijkstra Path Length, PQ Dijkstra Time(ms)" << endl;

    for(int i=1;i<=155620;i++) {
        getline(a, line_a);
        getline(a_seg, line_a_seg);
        getline(pqdj, line_pqdj);
        getline(pqdj_seg, line_pqdj_seg);

        st = string_tokenizer(line_a, ',');
        st.next();
        cout << i << ", " << st.next() << ", " << st.next() << ", " << st.next() << ", ";

        st = string_tokenizer(line_a_seg, ',');
        st.next(); st.next();
        cout << st.next() << ", " << st.next() << ", ";

        st = string_tokenizer(line_pqdj, ',');
        st.next(); st.next();
        cout << st.next() << ", " << st.next() << ", ";

        st = string_tokenizer(line_pqdj_seg, ',');
        st.next(); st.next();
        cout << st.next() << ", " << st.next();        
        
        cout << endl;
    }

    return 0;
}