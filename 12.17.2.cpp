#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include<iomanip> // 要用setw

struct Pokemon {
    int id;
    std::string name;
    std::string type1, type2;
    int total, hp, attack, defense;
    int sp_atk, sp_def, speed;
    int generation;
    bool legendary;

    Pokemon(int id , std::string name , std::string type1 , std::string type2,
            int total, int hp, int attack, int defense, int sp_atk, int sp_def, int speed,
            int generation , bool legendary) : id(id) , name(name) , type1(type1) , type2(type2),
            total(total) , hp(hp) , attack(attack) , defense(defense) , sp_atk(sp_atk) , sp_def(sp_def) , speed(speed) , 
            generation(generation) , legendary(legendary){}

    Pokemon() {}

};

struct Data {
    int hp;
    std::vector<int> id;
    Data(int hp , int id) {
        this->hp = hp;
        this->id.push_back(id);
    }

    Data() {}
    
};

struct Node {
    Data data;
    Node* left;
    Node* right;
};

//-------------------宣告-------------------//
void PrintMenu();
std::string RemoveSpace(std::string target);
bool IsInt(std::string num);
bool Getrange(int &range);
void Sort(std::vector<std::pair<int,int>> &result);
Pokemon GetPokemon(std::vector<Pokemon> data, int id);
void Print2(std::vector<Pokemon> data, std::vector<std::pair<int,int>> result);
//-------------------宣告-------------------//

class Tree {
  private:
    //datd
    Node *root = nullptr;
    int delete_time = 0;//任務三計數用

    //function
    int CountHeight(Node *node);
    bool deleteMin(std::vector<Pokemon> data);
    bool deleteMax(std::vector<Pokemon> data);
    void Cleer(Node *node);
  
  public:
    
    void Cleer() {
        Cleer(root);
        root = nullptr;
        return;
    }
    int GetHeight() {
      return CountHeight(root);
    }
    Node *GetRoot() {
        return root;
    }
    void Insert(Data data);
    bool DeleteNode(std::vector<Pokemon> data);
    void RangeSearch(Node* node , int low , int high , std::vector<std::pair<int,int>> &result , int &visited);
    bool LoadFromFile(std::string &filename , std::vector<Pokemon> &data);
};

int main() {
    std::vector<Pokemon> data;
    //所有資料放在這裡，因為他說節點只能放兩個東西
    //(我在想可以寫一個function要用的時候從這裡搜尋資料在印出來)
    Tree tree;
    std::string verb;
    while(true) {
        PrintMenu();
        
        std::cin >> verb;
        verb = RemoveSpace(verb);
        
        if (verb == "0") break;

        else if (verb == "1") {
            tree.Cleer(); 
            std::cout << "\nInput a file number [0: quit]: \n";            
            std::string num;
            std::cin >> num;
            num = RemoveSpace(num);
            if (num == "0") continue;
            std::string filename = "input" + num + ".txt";
            while (!tree.LoadFromFile(filename , data)) {
                std::cout << "Input a file number [0: quit]: \n";  
                std::cin >> num;
                num = RemoveSpace(num);
                if (num == "0") continue;
                std::string filename = "input" + num + ".txt";
            }
            std::cout << "HP tree height = " << tree.GetHeight() << "\n\n"; 
        } 
        
        else if (verb == "2") {
            if (!tree.GetRoot()) {
                std::cout <<"----- Execute Mission 1 first! -----\n";
                continue;
            }
            int low = 0;
            while (!Getrange(low)) {}
            int high = 0;
            while (!Getrange(high)) {}
            if (low > high) {
                std::swap(low , high);
            }

            std::vector<std::pair<int,int>> result;
            int searched = 0;
            tree.RangeSearch(tree.GetRoot() , low , high , result , searched);
            if (result.size() == 0) {
                std::cout << "No record was found in the specified range.\n";
            } else {
                Sort(result);
                Print2(data, result);
            }
            std::cout << "Number of visited nodes = " << searched << std::endl;
        } 
        
        else if (verb == "3") {
            if (!tree.DeleteNode(data)) {
                std::cout << "----- Execute Mission 1 first! -----\n";
            } else {
                std::cout << "HP tree height = " << tree.GetHeight() << "\n";
            }
        } 
        
        else if (verb == "4") {
            
        } 
        
        else {
            std::cout << "\nCommand does not exist!\n\n";
        }
    }
    return 0;
}

void PrintMenu() {
    std::cout << "*** (^_^) Data Structure (^o^) ***" << std::endl;
    std::cout << "** Simulate FIFO Queues by SQF ***" << std::endl;
    std::cout << "* 0. Quit                        *" << std::endl;
    std::cout << "* 1. Read a file to build HP BST *" << std::endl;
    std::cout << "* 2. Range search on HP field    *" << std::endl;
    std::cout << "* 3. Delete the min on HP field  *" << std::endl;
    std::cout << "* 4. Rebuild the balanced HP BST *" << std::endl;
    std::cout << "**********************************" << std::endl;
    std::cout << "Input a command(0, 1, 2, 3, 4): ";
    return;
}

bool IsInt(std::string num) {
    if(num.size() == 0) {
        return false;
    }
    for (int i = 0; i < num.size(); i++) {
        if (i == 0 && (num[i] == '+' || num[i] == '-')) {
        continue;
    }
    if(num[i] > '9' || num[i] < '0') {
        return false;
    }
}
return true;
}

std::string RemoveSpace(std::string target) {
    std::string to_return;
    for (int i = 0; i < target.size() ;i++) {
        if (target[i] != ' ' && target[i] != '\t' && target[i] != '\n') {
      to_return = to_return + target[i];
    }
}
return to_return;
}

bool Getrange(int &range) {
    std::cout << "Input a non-negative integer: \n";
    std::string num;
    std::cin >> num;
    num = RemoveSpace(num);
    if (IsInt(num)) {
        range = stoi(num);

        if (range < 0) {
            std::cout << "### It is NOT a non-negative integer. ###\n";
            std::cout << "Try again: \n";
            return false;
        } else if (range > 160) {
            std::cout << "### It is NOT in [0,160]. ###\n";
            std::cout << "Try again: \n";
            return false;
        }

        return true;
    } else {
        std::cout << "### It is NOT a non-negative integer. ###\n";
        std::cout << "Try again: \n";
        return false;
    }
}

void Sort(std::vector<std::pair<int,int>> &result) {
   int size = result.size();
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (result[j].first < result[j + 1].first) {
                int temp = result[j].first;
                int temp2 = result[j].second;
                result[j].first = result[j + 1].first;
                result[j].second = result[j + 1].second;
                result[j + 1].first = temp;
                result[j + 1].second = temp2;
            }
        }
    }
}

Pokemon GetPokemon(std::vector<Pokemon> data, int id) {
    int size = data.size();
    for (int i = 0; i < size; i++) {
        if (data[i].id == id ) {
            return data[i];
        }
    }
}

void Print2(std::vector<Pokemon> data, std::vector<std::pair<int,int>> result) {
    for (int i = 0; i < result.size(); i++) {
        if (i == 0) {
            std::cout << "\t#\tName\tType 1\tTotal\tHP\tAttack\tDefense\n";
        }
        Pokemon now_pokemon =  GetPokemon(data, result[i].second);
        std::cout << "[" << std::setw(3) << i + 1 <<"]\t";
        std::cout << now_pokemon.id << "\t" << now_pokemon.name << "\t" << now_pokemon.type1 << "\t" << now_pokemon.total <<"\t";
        std::cout << now_pokemon.hp <<"\t" << now_pokemon.attack << "\t" << now_pokemon.defense << "\n";
    }
}

//------------------------------Tree-----------------------------//

void Tree::Cleer(Node *node) {
    if (!node) {
        return;
    }
    Cleer(node->left);
    Cleer(node->right);
    delete node;
    return;
}

void Tree::Insert(Data data) {
    if (root == nullptr) {
        root = new Node();
        root->data = data;
        root->left = nullptr;
        root->right = nullptr;
        return;
    }
    
    Node* cur = root;
    while (true) {
        if (data.hp < cur->data.hp) {
            if (cur->left == nullptr) {
                cur->left = new Node;
                cur = cur->left;
                cur->data = data;
                cur->left = nullptr;
                cur->right = nullptr;
                return;
            } else {
                cur = cur->left;
            }
        } else if(data.hp == cur->data.hp) {
            cur->data.id.push_back(data.id[0]);
            return;
        } else {
            if (cur->right == nullptr) {
                cur->right = new Node;
                cur = cur->right;
                cur->data = data;
                cur->left = nullptr;
                cur->right = nullptr;
                return;
            } else {
                cur = cur->right;
            }
        }
    }
    return;
}

bool Tree::LoadFromFile(std::string &filename , std::vector<Pokemon> &data) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cout << "### " << filename << " does not exist! ###\n\n";
        return false;
    }
    
    std::string header;
    if (!getline(fin, header)) {
        fin.close();
        std::cout << "\n### Get nothing from " << filename<<" ! ###\n\n"; //不知道這次有沒有，我複製上次的
        return false;
    }
    
    Pokemon pokemon;
    
    int id;
    std::string name;
    std::string type1, type2;
    int total, hp, attack, defense;
    int sp_atk, sp_def, speed;
    int generation;
    bool legendary = true;
    std::string temp;
    int number = 1;
    while (fin >> id) {
        getline(fin , temp , '\t');

        getline(fin , name , '\t');
        getline(fin , type1 , '\t');
        getline(fin , type2 , '\t');

        fin >> total;
        getline(fin , temp , '\t');
        fin >> hp;
        getline(fin , temp , '\t');
        fin >> attack;
        getline(fin , temp , '\t');
        fin >> defense;
        getline(fin , temp , '\t');
        fin >> sp_atk;
        getline(fin , temp , '\t');
        fin >> sp_def;
        getline(fin , temp , '\t');
        fin >> speed;
        getline(fin , temp , '\t');
        fin >> generation;
        getline(fin , temp , '\t');

        getline(fin , temp);
        if(temp == "FALSE") legendary = false;
        else legendary = true;

        Pokemon p(id, name, type1, type2, total, hp, attack, defense, sp_atk, sp_def, speed, generation, legendary);
        data.push_back(p);
        if (number == 1) {
            std::cout << "\t#\tName\tType 1\tHP\n";
        }
        std::cout << "[" << std::setw(3) << number <<"]\t";
        std::cout << id << "\t" << name << "\t" << type1 << "\t" << hp << "\n";
        number++;
        Data d(hp, id);
        Insert(d);
    }
    
    fin.close();
    return true;
}

int Tree::CountHeight(Node *node) {
    if (node == nullptr) {
        return 0;
    }

    int left = CountHeight(node->left);
    int right = CountHeight(node->right);
    if (left > right) {
        return left + 1;
    } else {
        return right + 1;
    }
}

bool Tree::deleteMin(std::vector<Pokemon> data) {
    if (!root) return false;
    Node *cur = root , *pre = nullptr;
    while (cur->left) {
        pre = cur;
        cur = cur->left;
    }
    for (int i = 0 ; i < cur->data.id.size() ; i++) {
        if (i == 0) {
            std::cout << "\t#\tName\tType 1\tTotal\tHP\tAttack\tDefense\tSp. Atk\tSp. Def\n";
        }
        Pokemon now_pokemon =  GetPokemon(data, cur->data.id[i]);
        std::cout << "[" << std::setw(3) << i + 1 <<"]\t";
        std::cout << now_pokemon.id << "\t" << now_pokemon.name << "\t" << now_pokemon.type1 << "\t" << now_pokemon.total <<"\t";
        std::cout << now_pokemon.hp <<"\t" << now_pokemon.attack << "\t" << now_pokemon.defense << "\t";
        std::cout << now_pokemon.sp_atk <<"\t" << now_pokemon.sp_def << "\n";
    }
    if (cur == pre) {
        root = root->right;
    } else {
        pre->left = cur->right;
    }
    delete cur;
    return true;
}

bool Tree::deleteMax(std::vector<Pokemon> data) {
    if (!root) return false;
    Node *cur = root , *pre = root;
    while (cur->right) {
        pre = cur;
        cur = cur->right;
    }
    for (int i = 0 ; i < cur->data.id.size() ; i++) {
        if (i == 0) {
            std::cout << "\t#\tName\tType 1\tTotal\tHP\tAttack\tDefense\tSp. Atk\tSp. Def\n";
        }
        Pokemon now_pokemon =  GetPokemon(data, cur->data.id[i]);
        std::cout << "[" << std::setw(3) << i + 1 <<"]\t";
        std::cout << now_pokemon.id << "\t" << now_pokemon.name << "\t" << now_pokemon.type1 << "\t" << now_pokemon.total <<"\t";
        std::cout << now_pokemon.hp <<"\t" << now_pokemon.attack << "\t" << now_pokemon.defense << "\t";
        std::cout << now_pokemon.sp_atk <<"\t" << now_pokemon.sp_def << "\n";
    }
    if (cur == pre) {
        root = root->left;
    } else {
        pre->right = cur->left;
    }
    delete cur;
    return true;
}

bool Tree::DeleteNode(std::vector<Pokemon> data) {
    delete_time++;

    if (delete_time % 2 == 0) {
        return deleteMax(data);
    } else {
        return deleteMin(data);
    }
}

void Tree::RangeSearch(Node* node , int low , int high , std::vector<std::pair<int,int>>& result , int& visited) {
    if (!node) return;
    visited++;

    if (node->data.hp >= low && node->data.hp <= high) {
        for (int i = 0 ; i < node->data.id.size() ; i++) {
            int id = node->data.id[i];
            result.push_back({node->data.hp, id});
        }
    }

    if (node->data.hp >= low) {
        RangeSearch(node->left, low, high, result, visited);
    }

    if (node->data.hp <= high) {
        RangeSearch(node->right, low, high, result, visited);
    }
    return;
}
