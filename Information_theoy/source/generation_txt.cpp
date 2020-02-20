#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include <iostream>

using namespace std;

#define LEN_STR 80
#define SIZE_FILE 10

vector<pair<string, int>> alf;

int count_sym = SIZE_FILE * 1024;

void init() {
    srand(time(NULL));
    alf.push_back(pair<string, int>("q", 50));
    alf.push_back(pair<string, int>("w", 30));
    alf.push_back(pair<string, int>("e", 15));
    alf.push_back(pair<string, int>("r", 5));
    

}

string generation_str(int len) {
    string str;
    for(auto i(0); i < len; i++) {
        int R(rand() % 100);
        int P(0);
        for(auto it(alf.begin()); it != alf.end(); it++) {
            P += it->second;
            if(R < P) {
                str += it->first;
                it = alf.end() - 1;
            }
        }
    }
    return str;
}

int main(int argc, char const *argv[]) {
    if (argc != 2) return -1;
    string path(argv[1]);

    init();

    ofstream txt(path);

    while (count_sym > 0) {
        txt << generation_str(count_sym < LEN_STR ? count_sym : LEN_STR) << endl;
        count_sym -= LEN_STR;
    }
    
    
    txt.close();

    return 0;
}
