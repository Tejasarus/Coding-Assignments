#include "BSTree.h"
#include <iostream>

using namespace std;


BSTree::BSTree() {
    root = nullptr;
}
BSTree::~BSTree()
{
    
}
void BSTree::insert(const string &str) 
{
    if(str == "")//if the string is empty
    {
        return;
    }
    Node *n = new Node(str);

    if(root == 0) //if root is empty
    {
        //cout << "hi!" << endl;
        root = n;
        root->right = 0;
        root->left = 0;
        ++root->count;
    }
    else //if the tree is not empty
    {
        Node* temp = root;
        while(temp != 0)
        {
            if(n->key == temp->key) //if duplicate, just incriment up
            {
                ++temp->count;
                return;
            }
            else if(n->key < temp->key) //go to the left if smaller
            {
                if(temp->left == 0) //if we reached the end of the left tree, add the node
                {
                    temp->left = n;
                    ++n->count;
                    temp = 0;
                }
                else //if we didnt reach the end, keep moving down
                {
                    temp = temp->left;
                }
            }
            else
            {
                if(n->key > temp->key) //go to the right if larger
                {
                   if(temp->right == 0) //if we reached the end of the right tree, add the node
                    {
                        temp->right = n;
                        ++n->count;
                        temp = 0;
                    }
                    else //if we didnt reach the end, keep moving down
                    {
                        temp = temp->right;
                    } 
                }
            }
        }
    }
}
void BSTree::remove(const string &key) 
{
    Node* par = nullptr;
    Node* curr = root;
    Node* succ = nullptr;
    
    while(curr != nullptr) {
        if(curr->key == key) {
            
            if(curr->count > 1) {
                --curr->count;
                return;
            }
            else 
            {
                //Leaf node removal
                if(curr->left == nullptr && curr->right == nullptr) {
                    if(par == nullptr) {
                        root = nullptr;
                    }
                    else if(par->left == curr) {
                        par->left = nullptr;
                    }
                    else {
                        par->right = nullptr;
                    }
                }
                //Internal node removal with left child only
                else if(curr->right == nullptr) {
                    if(par == nullptr) {
                        root = curr->left;
                    }
                    else if(par->left == curr) {
                        par->left = curr->left;
                    }
                    else {
                        par->right = curr->left;
                    }
                }
                //Internal node removal with right child only
                else if(curr->left == nullptr) {
                    if(par == nullptr) {
                        root = curr->right;
                    }
                    else if(par->left == curr) {
                        par->left = curr->right;
                    }
                    else {
                        par->right = curr->right;
                    }
                }
                else {
                    succ = curr->right;
                    
                    while(succ->left != nullptr) {
                        succ = succ->left;
                    }
                    
                    int oldCount = succ->count;
                    string oldKey = succ->key;
                    
                    remove(succ->key);
                    
                    curr->count = oldCount;
                    curr->key = oldKey;
                }
                
                return;
            }
        }
        //Search right
        else if(curr->key < key) {
            par = curr;
            curr = curr->right;
        }
        //Search left
        else {
            par = curr;
            curr = curr->left;
        }
    }
    
    return;
}

bool BSTree::search(const string &key) const {
    Node* curr = root;
    
    while(curr != nullptr) {
        if(curr->key == key) {
            return true;
        }
        else if(curr->key < key) {
            curr = curr->right;
        }
        else {
            curr = curr->left;
        }
    }
    
    return false;
}

string BSTree::largest() const {
    if(root == 0) //if root is empty
    {
        return "";
    }
    Node* n = root;
    while(n->right != 0)
    {
        n = n->right;
    }
    return n->key;
}

string BSTree::smallest() const {
    if(root == 0) //if root is empty
    {
        return "";
    }
    Node* n = root;
    while(n->left != 0)
    {
        n = n->left;
    }
    return n->key;
}


int BSTree::height(const string &key) const 
{
   if (root == 0) { //if tree is empty
		return -1;
	}

	Node *n = root;
	while (n != 0) //get the node which has the string
	{
		if (n->key == key)
        {
            break;
        }
		else
		{
			if (n->key > key)
			{
				n = n->left;
			}
			else
				n = n->right;
		}
	}

	int h = 0;

	if (n == 0) //if that node doesnt exist, return -1
    {
        return -1;
    }
	if (n->left == 0 && n->right == 0) //if its the root, return 0
    {
        return 0;
    }
	else //otherwise, look for the height in the helper function
    {
        h = getHeight(n); 
    }
	return h;
}

int BSTree::getHeight(Node* n) const
{
    if(n == nullptr)
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
void BSTree::preOrder() const
{
    pre(root);
    cout << endl;
}
void BSTree::postOrder() const
{
    pOrder(root);
    cout << endl;
}
void BSTree::inOrder() const
{
    iOrder(root);
    cout << endl;
}

void BSTree::iOrder(Node* n) const
{
    //cout << "hwwo" << endl;
    if(n) //if its not an empty node
    {
        //follow inorder traversal (left, root, right)
        iOrder(n->left);
        //cout << "hello";
        cout << n->key << "(" << n->count << "), ";
        iOrder(n->right);
    }
}
void BSTree::pre(Node* n) const
{
    if(n) //if its not an empty node
    {
        //follow inorder traversal (root, left, right)
        cout << n->key << "(" << n->count << "), ";
        pre(n->left);
        pre(n->right);
    }
}
void BSTree::pOrder(Node* n) const
{
     if(n) //if its not an empty node
    {
        //follow inorder traversal (left, right, root)
        pOrder(n->left);
        pOrder(n->right);
        cout << n->key << "(" << n->count << "), ";
    }
}
Node* BSTree::isDupe(string str, Node* n)
{
    if (n == 0)
    {
        return nullptr;
    }
        
    if (n->key == str)
    {
        return n;
    }
        
    /* then recur on left sutree */
    Node* left = isDupe(str,n->left);
    // node found, no need to look further
    if(left)
    {
        return left;
    } 
 
    /* node is not found in left,
    so recur on right subtree */
    Node* right = isDupe(str,n->right);
 
    return right;
}