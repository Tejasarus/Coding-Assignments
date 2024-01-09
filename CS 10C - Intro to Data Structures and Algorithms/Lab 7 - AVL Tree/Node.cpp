#include "Node.h"

Node::Node() //initialize everything to nothing (blank)
{
    data = "";
    left = 0;
    right = 0;
    parent = 0;
}
Node::Node(string str) //initialize everything except the string to nothing
{
    data = str;
    left = 0;
    right = 0;
    parent = 0;
}