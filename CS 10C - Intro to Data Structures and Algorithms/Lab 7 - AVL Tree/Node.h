#ifndef NODE_H
#define NODE_H

#include <iostream>
using namespace std;

class Node{
    public:
    Node();
    Node(string);

    string data; //will hold the string the user inputs
    Node* parent; //holds the parent
    Node* left; //left child
    Node* right; //right child
};

#endif