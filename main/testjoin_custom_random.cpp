#include <iostream>
#include <string>
#include <fstream>

#include <../string_tokenizer/string_tokenizer.hpp>

using namespace std;

string trim(const string& str)
{
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first)
    {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

int main() {
    ifstream a("tests/grids/custom_random/maps_250x250/alpha5/a_star.csv");
    ifstream a_seg("tests/grids/custom_random/maps_250x250/alpha5/a_star_segmented.csv");
    ifstream pqdj("tests/grids/custom_random/maps_250x250/alpha5/pq_dijkstra.csv");
    ifstream pqdj_seg("tests/grids/custom_random/maps_250x250/alpha5/pq_dijkstra_segmented.csv");

    string line_a, line_a_seg, line_pqdj, line_pqdj_seg;
    string_tokenizer st;
    
    string data;
    double diff;
    double time_l, time_r, av_x=0, av_y=0;
    double max_x=0, max_y=0;
    int count_x=0, count_y=0;
    
    // skip first line
    getline(a, line_a);
    getline(a_seg, line_a_seg);
    getline(pqdj, line_pqdj);
    getline(pqdj_seg, line_pqdj_seg);

    for(int i=1;i<=1000;i++) {
        getline(a, line_a);
        getline(a_seg, line_a_seg);
        getline(pqdj, line_pqdj);
        getline(pqdj_seg, line_pqdj_seg);

        st = string_tokenizer(line_a, ',');
        st.next();
        cout << i << ", " << st.next() << ", ";
        data = st.next();
        time_l = stod(trim(data));
        cout << data << ", ";

        st = string_tokenizer(line_pqdj_seg, ',');
        st.next();
        cout << st.next() << ", ";
        data = st.next();
        time_l = stod(trim(data));
        cout << data << ", ";
        
        if(time_l < time_r) { 
            count_x++; 
            diff = time_r-time_l;
            av_x += diff; 
            max_x = diff>max_x ? diff : max_x;
        }
        else if(time_l>time_r) {
            count_y++; 
            diff = time_l-time_r;
            av_y += diff;
            max_y = diff>max_y ? diff : max_y;
        }

        cout << (time_l<time_r);

        // st = string_tokenizer(line_pqdj, ',');
        // st.next(); st.next();
        // cout << st.next() << ", " << st.next() << ", ";

        // st = string_tokenizer(line_pqdj_seg, ',');
        // st.next(); st.next();
        // cout << st.next() << ", " << st.next();        
        
        cout << endl;
    }

    cout << "A* Seg < PQDJ Seg" << endl;
    cout << "count: " << count_x << endl;
    cout << "max_diff: " << max_x << endl;
    cout << "average time difference: " << (av_x/count_x) << endl << endl;

    cout << "A* Seg > PQDJ Seg" << endl;
    cout << "count: " << count_y << endl;
    cout << "max_diff: " << max_y << endl;
    cout << "average time difference: " << (av_y/count_y) << endl << endl;

    cout << "----------------" << endl << endl << endl;


    return 0;
}