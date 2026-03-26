#include <iostream>

using namespace std;

class Node{
    public:
    int p;
    Node *l_child;
    Node *r_child;
    Node(int v){
        p = v;
        l_child = r_child = nullptr;
    }
};

class BST{
    private:
    Node *root;
    void insert(Node *&i, int v){
        if(i == nullptr){
            i = new Node(v);
            return;
        }
        if(v < i -> p){
            insert(i -> l_child, v);
        }else{
            insert(i -> r_child, v);
        }
    }
    bool find(Node *&i, int v){
        if(i == nullptr) return false;
        if(i -> p == v) return true;
        if(v < i -> p){
            return find(i -> l_child, v);
        }
        return find(i -> r_child, v);
    }
    public:
    BST(){root = nullptr;}
    ~BST(){}
    void insert(int v){insert(root, v);}
    bool find(int v){return find(root, v);}
    Node *getRoot(){
        return root;
    }
};

void menu(){
    int n;
    n = 0;
    while(n != 3){
        cout<< "#################################" <<endl;
        cout<< "###      Network scanner      ###" <<endl;
        cout<< "#################################" <<endl;
        cout<< "[1] Create a tree" <<endl;
        cout<< "[2] Scan the network and enter the IP address" <<endl;
        cout<< "[3] Exit" <<endl;
        cin >> n;
        if(n == 1) BST bst;
    }
}

int main(){
    menu();
    return 0;
}
