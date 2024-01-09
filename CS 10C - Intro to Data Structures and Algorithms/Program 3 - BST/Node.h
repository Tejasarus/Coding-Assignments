#include <string>
#include <iostream>
using namespace std;

class Node {
public:
    Node* parent;
    Node* right;
    Node* left;
    string key;
    int count;
    Node()
    {
        parent = 0;
        right = 0;
        left = 0;
        key = "";
        count = 0;
    };
    Node(string str)
    {
        parent = 0;
        right = 0;
        left = 0;
        key = str;
        count = 0;
    };
};
