#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <map>
#include <vector>
#include <math.h>

#define register false
#define space false
std::string one_sym(",.");

bool pred(const std::pair< std::string, int > &a, const std::pair< std::string, int > &b) {
    return a.second > b.second;
}

class Texter {
private:
    int size_txt;
    std::map<std::string, int> arraySym;
    std::map<std::string, int>::iterator arraySymIter;
    std::vector<std::pair<std::string, int>> *vecSym;


public:
    Texter() {
        size_txt = 0;
    };
    
    int get_size_txt() {
        return size_txt;
    }

    void set_size_txt(int a) {
        size_txt += a;
    }

    void add(std::string a) {
        size_txt++;
        if (!register) 
            std::transform(a.begin(), a.end(), a.begin(), (int (*)(int))std::tolower);

        if (!space)
            if (a.find(" ") != -1)
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

    double get_intr_txt() {
        double resoult(0);
        for (auto it_v = vecSym->begin(); it_v != vecSym->end(); it_v++) {
            resoult += -log2(1.0 * it_v->second / get_size_txt());
        }
        return resoult;
    }

    std::vector<std::pair<std::string, int>> get_vec() {
        return *vecSym;
    }    

    ~Texter() {
        delete vecSym;
    };
};

class tree {
public:
    tree *left;
    tree *right;
    int code;
    std::pair<std::string, int> data;

    tree() {};
    ~tree() {};
};

class fono {
public:
    std::vector<std::pair<std::string, int>> *vec;
    tree root;

    fono(std::vector<std::pair<std::string, int>> a) {
        vec = new auto(a);
    }
    
    ~fono() {
        delete vec;
    }

    auto sum_vec(std::vector<std::pair<std::string, int>>::iterator a, std::vector<std::pair<std::string, int>>::iterator b) {
        auto sum(0);
        for (;a != b; a++) {
            sum += a->second;
        }
        return sum;
    }

    auto get_mid(std::vector<std::pair<std::string, int>>::iterator a, std::vector<std::pair<std::string, int>>::iterator b) {
        auto mid = a + 1;
        while (sum_vec(a, mid) < sum_vec(mid, b))
            mid++;
        return mid;
    }
};


int main(int argc, char const *argv[]) {

    std::ifstream text(argv[1]);
    std::string str;
    Texter t;
    while (getline(text, str)) {
        t.set_text(str);
        //t.set_size_txt(t.get_size_txt() + str.length());
    }
    
    //t.set_text(std::string("Ttaweeea"), 1);
    //t.show_map();
    t.map2vec();
    t.sort_vec();
    t.show_vec();
    std::cout << t.get_size_txt() << std::endl;  
    
    std::cout << t.get_intr_txt() << std::endl;  
    
    fono f(t.get_vec());
    std::cout << f.get_mid(f.vec->begin(), f.vec->end())->first << " - " << f.get_mid(f.vec->begin(), f.vec->end())->second << std::endl;

    

    text.close();
    return 0;
}
