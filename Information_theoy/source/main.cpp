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

bool pred(const std::pair<std::string, int > &a, const std::pair<std::string, int > &b) {
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

    int get_count_sym() {
        int r = 0;
        for (auto i(arraySym.begin()); i != arraySym.end(); i++)
            r += i->second;
        
        return r;
    }

    void set_size_txt(int a) {
        size_txt = a;
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
        std::cout << arraySym.size() << std::endl;
        for (auto i = arraySym.begin(); i != arraySym.end(); i++)
            std::cout << i->first << " - " << i->second << std::endl;
    }
    
    void show_vec() {
        std::cout << vecSym->size() << std::endl;
        for (auto i = vecSym->begin(); i != vecSym->end(); i++)
            std::cout << i->first << " - " << i->second << std::endl;
    }

    double get_intr_txt(double a) {
        double resoult(0);
        for (auto it_v = vecSym->begin(); it_v != vecSym->end(); it_v++) {
            resoult += -(1.0 * it_v->second / get_size_txt()) * log2(1.0 * it_v->second / get_size_txt());
        }
        return resoult / a;
    }

    std::vector<std::pair<std::string, int>> get_vec() {
        return *vecSym;
    }    

    ~Texter() {
        delete vecSym;
    };
};

std::map<std::string, std::string> map_tree;

class tree {
public:
    tree *left;
    tree *right;
    std::string code;
    std::vector<std::pair<std::string, int>> *vec;

    tree(std::vector<std::pair<std::string, int>> v, std::string c = "") {
        vec = new auto(v);
        code = c;
        if (vec->size() >= 2) {
            auto mid = get_mid(vec->begin(), vec->end());
            left = new tree(std::vector<std::pair<std::string, int>>(vec->begin(), mid), "0");
            right = new tree(std::vector<std::pair<std::string, int>>(mid, vec->end()), "1");
        }
    };

    ~tree() {
        delete vec, left, right;
    };

    void show_vec_tree() {
        std::cout << map_tree.size(); 
        //for (auto it(vec_tree.begin()); it != vec_tree.end(); it++)
          //  std::cout << it->first << " - " << it->second << std::endl;
    }

    void add_map_tree(std::string key, std::string d) {
        map_tree.insert(std::pair<std::string, std::string>(d, key));
    }

    void creat_vect_tree(std::string s) {
        if (left == NULL && right == NULL) {
            add_map_tree(s + code, vec->begin()->first);
        } else {
            left->creat_vect_tree(s + code);
            right->creat_vect_tree(s + code);
        }
    }
    
    auto sum_vec(std::vector<std::pair<std::string, int>>::iterator a, std::vector<std::pair<std::string, int>>::iterator b) {
        auto sum(0);
        for (;a != b; a++) {
            sum += a->second;
        }
        return sum;
    }

    std::vector<std::pair<std::string, int>>::iterator get_mid(std::vector<std::pair<std::string, int>>::iterator a, std::vector<std::pair<std::string, int>>::iterator b) {
        auto mid = a + 1;
        while (sum_vec(a, mid) < sum_vec(mid, b))
            mid++;
        return mid;
    }
};

class fono {
public:
    std::map<std::string, std::string> *vec;

    fono(std::map<std::string, std::string> a) {
        vec = new auto(a);
    }
    
    ~fono() {
        delete vec;
    }

    void show() {
        for (auto i(vec->begin()); i != vec->end(); i++) {
            std::cout << i->first << " - " << i->second << std::endl;
        }
    }

    double get_max_H() {
        return log2(1.0 * vec->size());
    }

    double get_R(double H) {
        return 1 - H / get_max_H();
    }

    std::string encode_my(std::string str, int size = 1) {
        std::string str_bit;
        for (auto it_str(str.begin()); it_str != str.end() - size + 1; it_str++) {
            auto it_map = vec->find(std::string(it_str, it_str + size));
            if (it_map != vec->end()) {
                str_bit += it_map->second;
            }
        }
        return str_bit;
    }

    std::string decode_my(std::string a) {
        std::string str(a);
        std::string r("");
        while (str != "") {
            for (auto it(vec->begin()); it != vec->end(); it++)
                if (!str.find(it->second)) {
                    r += it->first;
                    str = std::string(str.begin() + it->second.length(), str.end());
                }
        }
        return r;
    }

};

int main(int argc, char const *argv[]) {
    int sym = 2;
    if (argc != 2) return -1;
    std::ifstream text(argv[1]);
    
    std::string str;
    Texter t;
    while (getline(text, str)) {
        t.set_text(str, sym);
    }
    //t.set_size_txt(t.get_count_sym());
    //t.set_text(std::string("Ttaweeea"), 1);
    //t.show_map();
    t.map2vec();
    t.sort_vec();
    //t.show_vec();
    std::cout << t.get_size_txt() << std::endl;  
    
    std::cout << t.get_intr_txt(1.0 * sym) << std::endl;  
    
    tree tr(t.get_vec());
    tr.creat_vect_tree("");
    //tr.show_vec_tree();

    fono f(map_tree);
    //f.show();
    //std::cout << f.decode_my(f.encode_my("xxj"));
    std::cout << "izb = " << f.get_R(t.get_intr_txt(1.0 * sym)) << std::endl;
    text.close();
    //std::ifstream text1(argv[1]);
    //std::ofstream text_code(argv[2]);
    //while (getline(text1, str)) {
    //    text_code << f.encode_my(str, sym) << std::endl;
    //}
    //text_code.close();
    //text1.close();
    return 0;
}
