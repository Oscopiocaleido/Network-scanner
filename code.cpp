#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h> // It contains the main functions: socket() and connect()
#include <arpa/inet.h>  // It contains the IP and port “mappers” and the “form”
#include <unistd.h>     // It includes the close() function to free up memory

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
    void print(Node *&i, string ip){
        if(i == nullptr) return;
        if(checkPort(ip, i -> p) == true){
            cout<< "[+] Port " << i -> p << " OPEN" <<endl;
        }else{
            cout<< "[-] Port " << i -> p << " CLOSE" <<endl;
        }
        print(i -> l_child, ip);
        print(i -> r_child, ip);
    }
    bool check(string ip, int port){
        int messenger = socket(AF_INET, SOCK_STREAM, 0);

        struct sockaddr_in form;

        form.sin_family = AF_INET;

        form.sin_port = htons(port);

        inet_pton(AF_INET, ip.c_str(), &form.sin_addr);

        int result = connect(messenger, (struct sockaddr*)&form, sizeof(form));

        close(messenger);

        if(result == 0){
            return true;
        }else{
            return false;
        }
    }
    public:
    BST(){root = nullptr;}
    ~BST(){}
    void insert(int v){insert(root, v);}
    bool find(int v){return find(root, v);}
    Node *getRoot(){
        return root;
    }
    void printPort(string ip){print(root, ip);}
    bool checkPort(string ip, int port){return check(ip, port);}
};

void menu(){
    unsigned int n;
    n = 0;

    BST bst;

    while(n != 3){
        int port = 0;

        cout<< "#################################" <<endl;
        cout<< "###      Network scanner      ###" <<endl;
        cout<< "#################################" <<endl;
        cout<< "[1] Enter the Port" <<endl;
        cout<< "[2] Print IP addresses" <<endl;
        cout<< "[3] Exit" <<endl;
        cout<< "Option: ";
        cin >> n;

        if(n == 1){
            cout<< "Enter the port number" <<endl;
            cin >> port;
            bst.insert(port);
            cout<< "Added port!" <<endl;
        }
        if(n == 2){
            string ip;
            cout<< "Enter the IP address to scan: ";
            cin >> ip;
            cout<< endl;
            cout<< "#################################" <<endl;
            cout<< "###    Scanner scan order     ###" <<endl;
            cout<< "#################################" <<endl;
            bst.printPort(ip);
        }
    }
}

int main(){
    menu();
    return 0;
}
