#ifndef AVLTREE_H
#define AVLTREE_H
#include "Node.h"
#include <iostream>
#include <fstream>

class AVLTree
{
    public:
    AVLTree();

    void insert(const string &); //: Insert an item to the binary search tree and perform rotation if necessary.
    int balanceFactor(Node*); //: Return the balance factor of a given node.
    void printBalanceFactors(); //: Traverse and print the tree in inorder notation. Print the string followed by its balance factor in parentheses followed by a , and one space.
    void visualizeTree(const string &); //: Generate dotty file and visualize the tree using dotty program. Call this function before and after rotation.

    private:
    Node* root;
    Node* findUnbalancedNode(Node*); // Find and return the closest unbalanced node (with balance factor of 2 or -2) to the inserted node.
    void rotate(Node*); //rotate: Implement four possible imbalance cases and update the parent of the given node.
    Node* rotateLeft(Node*); //rotateLeft: Rotate the subtree to left at the given node and returns the new subroot.
    Node* rotateRight(Node*); //rotateRight: Rotate the subtree to right at the given node and returns the new subroot.
    void printBalanceFactors(Node *);
    void visualizeTree(ofstream &, Node *);

    Node* findpar(string,Node*); //will find the node thats being inserted
    int getHeight(Node*)const; //will find the height of the node
    bool isDupe(string, Node*); //will return true if string is in the tree
};

#endif