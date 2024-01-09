#ifndef WORDLADDER
#define WORDLADDER

#include "WordLadder.h"
#include <iostream>
#include <stack>
#include <list>
#include <queue>
#include <string>
#include <fstream>
using namespace std;

WordLadder::WordLadder(const string &str)
{
    ifstream file;
    file.open(str); //open the file with all of the words
    string word;

    if(!file.is_open()) //if it couldnt open the file, give an error
    {
        cout << "Error couldnt open file" << endl;
        return;
    }

    while(!file.eof())
    {
        file >> word;
        if(word.size() != 5) //if the word is not five letters long, give an error statement
        {
            cout << "Error: The word is not 5 letters long" << endl;
            return;
        }
        dict.push_back(word); //add the word to the list dictionary
    }

    file.close(); //close the file
}
 void WordLadder::outputLadder(const string &start, const string &end, const string &outputFile)
 {
    int c = 0;
    list<string>::iterator i; //for the for loop
    for(i = dict.begin(); i != dict.end(); ++i) //cycle through the loop to see if the two inputed words exist
    {
        if(*i == start)
        {
            ++c; //if they do exist, c should count up (should do this twice)
        }
        if(*i == end)
        {
            ++c; //if they do exist, c should count up 
        }

    }
    
    if(c != 2) //if it doesn't find both words in the dictionary list, give an error
    {
        cout << "Error: these words don't exist in the dictionary" << endl;
        return;
    }

    ofstream file;

    file.open(outputFile);
    if(!file.is_open()) //if it couldnt open the file, give an error
    {
        cout << "Error couldnt open file" << endl;
        return;
    }

    if(start == end) //if start and end are the same
    {
        file << start << endl;
        return;
    }

    stack<string> first_word;
    first_word.push(start);
    queue<stack<string>> q;
    q.push(first_word);

    stack<string> ladder;

    while(!q.empty())
    {
        string fword = q.front().top(); //get the word on tio of the front Stack of this Queue
        for(auto t = dict.begin(); t!=dict.end();)
        {
            string dictword = *t;
            c = 0;
            int size = dictword.size();
            for(int j = 0; j < size; ++j)
            {
                if(fword.at(j) != dictword.at(j))
                {
                    ++c;
                }
            }
            if(c <= 1)
            {
                stack<string> main = q.front();
                main.push(dictword);
                //cout << dictword << endl;
                if(dictword == end)
                {
                    
                    while(!main.empty())
                    {
                        ladder.push(main.top());
                        main.pop();
                    }
                    list<string> output;
                    while(!ladder.empty())
                    {
                        output.push_back(ladder.top());
                        ladder.pop();
                    }
                    for(auto o = output.begin(); o != output.end(); ++o)
                    {
                        file << *o << " ";
                    }
                    file.close();
                    return;
                }
                else
                {
                    q.push(main);
                    t = dict.erase(t);
                }
            }
            else
            {
                ++t;
            }
        }
        q.pop();
    }
    file << "No Word Ladder Found.";
    file.close();
}
#endif