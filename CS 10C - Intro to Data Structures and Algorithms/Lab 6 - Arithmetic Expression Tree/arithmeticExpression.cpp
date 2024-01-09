#ifndef ARITHMETICEXPRESSION
#define ARITHMETICEXPRESSION
#include <iostream>
#include <cstdlib>
#include <stack>
#include <fstream>
#include <sstream>
#include <string>
#include "arithmeticExpression.h"
using namespace std;

arithmeticExpression::arithmeticExpression(const string &str)
{
    infixExpression = str;
    root = 0;
}
void arithmeticExpression::buildTree()
{
    stack<TreeNode*> s;
    string pfix = infix_to_postfix(); //abc*+
    int size = pfix.size(); //get the size of the string
    
    for(int i = 0; i < size; ++i)
    {
        if(priority(pfix.at(i)) > 0) //if the char is a operator
        {
            TreeNode* r; //right child
            TreeNode* l; //left child
            
            r = s.top(); //make the right child the first of the stack
            s.pop(); //remove it from the stack (now left is on top)
            l = s.top(); //make l equal the top of the stack
            s.pop(); //remove the top of the stack

            TreeNode* temp = new TreeNode(pfix.at(i),pfix.at(i)); //make a new node
            temp->right = r; //set the right child to the stored r value
            temp->left = l; //set the left child to the stored l value

            s.push(temp);
        }
        else //if its an operand
        {
            TreeNode* temp = new TreeNode(pfix.at(i),pfix.at(i)); //make a new node
            s.push(temp); //push it to a stack
        }
    }
   // cout << s.top()->right->left->key << endl;
   root = s.top(); //make the root the tree that has been made above
}
void arithmeticExpression::infix()
{
    infix(root);
}
void arithmeticExpression::prefix()
{
    prefix(root);
}
void arithmeticExpression::postfix()
{
    postfix(root);
}

int arithmeticExpression::priority(char op){
    int priority = 0;
    if(op == '('){
        priority =  3;
    }
    else if(op == '*' || op == '/'){
        priority = 2;
    }
    else if(op == '+' || op == '-'){
        priority = 1;
    }
    return priority;
}

string arithmeticExpression::infix_to_postfix(){
    stack<char> s;
    ostringstream oss;
    char c;
    for(unsigned i = 0; i< infixExpression.size();++i){
        c = infixExpression.at(i);
        if(c == ' '){
            continue;
        }
        if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'){ //c is an operator
            if( c == '('){
                s.push(c);
            }
            else if(c == ')'){
                while(s.top() != '('){
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            }
            else{
                while(!s.empty() && priority(c) <= priority(s.top())){
                    if(s.top() == '('){
                        break;
                    }
                    oss << s.top();
                    s.pop();
                }
                s.push(c);
            }
        }
        else{ //c is an operand
            oss << c;
        }
    }
    while(!s.empty()){
        oss << s.top();
        s.pop();
    }
    return oss.str();
}

void arithmeticExpression::infix(TreeNode *t) //(a+(b*c))
{
    if(t == 0)
    {
        return;
    }
    else
    {
        if(priority(t->data) != 0)//if its an operator
        {
            cout << "(";
        }
        infix(t->left);
        cout << t->data;
        infix(t->right);
        if(priority(t->data) != 0)//if its an operator
        {
            cout << ")";
        }
    }          
    
}
void arithmeticExpression::prefix(TreeNode *t) //+a*bc
{
    
    if(t == 0)
    {
        return;
    }
    else
    {   
        cout << t->data;
        prefix(t->left); 
        prefix(t->right);

    }
    
}
void arithmeticExpression::postfix(TreeNode *t) //abc*+ using postorder
{
    //left, right, root
    if(t == 0)
    {
        return;
    }
    else
    {
        postfix(t->left);
        postfix(t->right);
        cout << t->data;
    }
    
}
void arithmeticExpression::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error opening "<< outputFilename<<endl;
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
void arithmeticExpression::visualizeTree(ofstream &out, TreeNode* t)
{
    if(t->left!=0)
    {
        out << "\"" << t->data << "\" -> \"" << t->left->data << "\";" << endl;
        visualizeTree(out, t->left);
    }
    if(t->right!=0)
    {
        out << "\"" << t->data << "\" -> \"" << t->right->data << "\";" << endl;
        visualizeTree(out, t->right);
    }
    
}
#endif
