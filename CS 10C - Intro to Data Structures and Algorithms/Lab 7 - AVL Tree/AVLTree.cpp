#include "AVLTree.h"
#include <fstream>
#include <iostream>
using namespace std;


AVLTree::AVLTree()
{
    root = 0;
}
void AVLTree::insert(const string &str)
{
    //if the tree is empty
    if(root == 0)
    {
        root = new Node(str); //make a new node and make that node the root
    }
    else if(isDupe(str, root)) //if its already in the tree, skip
    {
        return;
    }
    else //if its not empty
    {
        Node* new_node = new Node(str); //make a new node
        //find the node that will become the parent of the new node
        //cout << "hi" << endl; 
        Node* par = findpar(str, root);
        //cout << "hi" << endl; 
        new_node->parent = par;
        if(str < par->data) //if the child is less than the parent
        {
            par->left = new_node;
        }
        else //if the child is greater than the parent
        {
            par->right = new_node;
        }

        //if adding the child makes the tree unbalanced, rotate the tree
        //cout << "hi" << endl; 
        Node* t = findUnbalancedNode(new_node);
        //cout << "hi" << endl;
        if(t)
        {
            //cout << "hello" << endl;
            rotate(t); //rotate so its not unbalanced anymore
        }
        //cout << "hi" << endl; 

    }
}
int AVLTree::balanceFactor(Node* n)
{
    if(n == 0) //if empty return 0
    {
        return 0;
    }
    else
    {
        //cout << "before get height" << endl;
        int l = getHeight(n->left); //get the height of the left
        int r = getHeight(n->right); //get the height of the right
        //cout << "after gh" << endl;
        int b = l- r; //gets the balance factor
        return b;
    }
}
void AVLTree::printBalanceFactors() {
    printBalanceFactors(root); //calls the private helper function
    cout << endl; //for zybooks whitespace :0
}
void AVLTree::printBalanceFactors(Node* n)
{
    if(n) //if its not an empty node
    {
        //follow inorder traversal (left, root, right)
        printBalanceFactors(n->left);
        cout << n->data << "(" << balanceFactor(n) << "), ";
        printBalanceFactors(n->right);
    }
}
void AVLTree::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error"<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}
void AVLTree::visualizeTree(ofstream & outFS, Node *n){
    if(n){
        if(n->left){
            visualizeTree(outFS,n->left);
            outFS<<n->data <<" -> " <<n->left->data<<";"<<endl;    
        }

        if(n->right){
            visualizeTree(outFS,n->right);
            outFS<<n->data <<" -> " <<n->right->data<<";"<<endl;    
        }
    }
}
Node* AVLTree::findpar(string str, Node* n)
{
    if(n->data == str) //if the data equals the string (base case)
    { 
        return n;
    }
    else if(str > n->data) //search the right
    {
        if(n->right) //if a right child even exists
        {
            return findpar(str, n->right);
        }
        else
        {
            return n;
        }
        
    }
    else if(str < n->data)//search the left
    {
        if(n->left) //if a left child exists
        {
           return findpar(str, n->left); 
        }
        else
        {
            return n;
        }
    }
    return n;
}
int AVLTree::getHeight(Node* n) const
{
    if(n == 0)
    {
        return -1;
    }
    int l = getHeight(n->left); //checks the # of childs in the left
    int r = getHeight(n->right); //checks the # of childs in the right
    if(l > r) //depending on which one is bigger, it will return that (because thats the height)
    {
        return ++l; //to make up the difference from starting at the child not the parent
    }
    else
    {
        return ++r; //to make up the difference from starting at the child not the parent
    }
}
Node* AVLTree::findUnbalancedNode(Node* n)
{
    if(n == 0) //if empty
    {
        return 0;
    }
    else
    {
        int b = balanceFactor(n); //get the balance factor of the node
        if(b == 2 || b == -2) //if unbalanced return the node
        {
            return n;
        }
        else //otherwise go up the tree
        {
            return findUnbalancedNode(n->parent);
        }
    }
}
void AVLTree::rotate(Node* n)
{
    string str = "a"; 
    visualizeTree(str); //draw tree before rotation

    int b = balanceFactor(n); //get the balance factor of the node
    int l = balanceFactor(n->left); //get the balance factor of the right node
    int r = balanceFactor(n->right); //get the balance factor of the left node

    if (b == 2) 
    {
        if (l == 1 || r == 1) 
        {
            rotateRight(n);
        }
        else 
        {
            rotateLeft(n->left);
            rotateRight(n);
        }
    }
    else 
    {
        if (l == -1 || r == -1) 
        {
            rotateLeft(n);
        }
        else 
        {
            rotateRight(n->right);
            rotateLeft(n);
        }
    }

    str = str + "b"; 
  visualizeTree(str); //draw tree after rotation
}
Node* AVLTree::rotateLeft(Node* n)
{
    Node* rl = n->right->left; //get the left child of the right child of the node

    if (n->parent != 0) //if the node has a parent
    {
        if (n->parent->right == n) //if the node is the right child of the parent
        {
            n->parent->right = n->right;

            if (n->right != 0) 
            {
                n->right->parent = n->parent;
            }
        }
        else if (n->parent->left == n) //if the node is the left child of the parent
        {
            n->parent->left = n->right;

            if (n->right != 0) 
            {
                n->right->parent = n->parent;
            }
        }
    }
    else 
    {
        root = n->right;
        root->parent = 0;
    }
   
    n->right->left = n;

    if (n != 0) 
    {
        n->parent = n->right;
    }

    n->right = rl;

    if (rl) 
    {
        rl->parent = n;
    }
    return n->parent;
}
Node* AVLTree::rotateRight(Node* n)
{
     Node* lr = n->left->right;
    if(n->parent != 0) 
    {
        if(n->parent->left == n) 
        {
            n->parent->left = n->left;

            if(n->left != 0) 
            {
                n->left->parent = n->parent;
            }
        }
        else if(n->parent->right == n) 
        {
            n->parent->right = n->left;

            if(n->left != 0) 
            {
                n->left->parent = n->parent;
            }
        }
    }
    else 
    {
        root = n->left;
        root->parent = 0;
    }
    n->left->right = n;
    if(n != 0) 
    {
        n->parent = n->left;
    }
    n->left = lr;
    if(lr != 0) 
    {
        lr->parent = n;
    }
    return n->parent;
}
bool AVLTree::isDupe(string str, Node* n)
{
    if (n == 0)
    {
        return false;
    }
        
    if (n->data == str)
    {
        return true;
    }
        
    /* then recur on left sutree */
    bool left = isDupe(str,n->left);
    // node found, no need to look further
    if(left)
    {
        return true;
    } 
 
    /* node is not found in left,
    so recur on right subtree */
    bool right = isDupe(str,n->right);
 
    return right;
}