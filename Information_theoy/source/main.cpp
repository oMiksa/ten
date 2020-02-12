#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <map>
#include <vector>

#define register false
#define space false
std::string one_sym(",.");

bool pred(const std::pair< std::string, int > &a, const std::pair< std::string, int > &b) {
    return a.second > b.second;
}

class Texter {
private:
    std::map<std::string, int> arraySym;
    std::map<std::string, int>::iterator arraySymIter;
    std::vector<std::pair<std::string, int>> *vecSym;


public:
    Texter() {};
    
    void add(std::string a) {
        if (!register) 
            std::transform(a.begin(), a.end(), a.begin(), (int (*)(int))std::tolower);

        if (!space)
            if (a.find(" "))
                return;

        for (auto i(one_sym.begin()); i != one_sym.end(); i++) {
            int temp = a.find(*i);
            if (temp != -1)
                a[temp] = '~';
        }

        arraySymIter = arraySym.find(a);
        if (arraySymIter != arraySym.end())
            arraySymIter->second += 1; 
        else
            arraySym.insert(std::pair<std::string, int>(a, 1));
    }

    void map2vec() {
        vecSym = new std::vector<std::pair<std::string, int>>(arraySym.begin(), arraySym.end());
    }

    void sort_vec() {
        std::sort(vecSym->begin(), vecSym->end(), pred);
    }

    void set_text(std::string a, int size = 1) {
        for (auto it = a.begin(); it < a.end() - size + 1; it++) {
            std::string temp;
            for (auto j(0); j < size; j++) 
                temp.append(sizeof(*(it + j)), *(it + j));

            this->add(temp);
        }
    }

    int get_size_map() {
        return arraySym.size();
    }

    void show_map() {
        for (auto i = arraySym.begin(); i != arraySym.end(); i++)
            std::cout << i->first << " - " << i->second << std::endl;
    }
    
    void show_vec() {
        for (auto i = vecSym->begin(); i != vecSym->end(); i++)
            std::cout << i->first << " - " << i->second << std::endl;
    }

    ~Texter() {
        delete vecSym;
    };
};

int main(int argc, char const *argv[]) {

    std::ifstream text(argv[1]);
    std::string str;
    Texter t;
    while (getline(text, str)) {
        t.set_text(str);
    }
    
    //t.set_text(std::string("Ttaweeea"), 1);
    //t.show_map();
    t.map2vec();
    t.sort_vec();
    t.show_vec();

    


    text.close();
    return 0;
}
