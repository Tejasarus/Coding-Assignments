#ifndef WORDLADDER_H
#define WORDLADDER_H

#include <iostream>
using namespace std;

#include <list>

class WordLadder
{
    private:
    list<string> dict;        //list of possible words in ladder

    public:
        /* Passes in the name of a file that contains a dictionary of 5-letter words.
        Fills the list (dict) with the words within this file. 
        If the file does not open for any reason or if any word within the file
        does not have exactly 5 characters, this function should output an
        error message and return.
        */
        WordLadder(const string &);

        /* Passes in two 5-letter words and the name of an output file.
        Outputs to this file a word ladder that starts from the first word passed in
        and ends with the second word passed in.
        If either word passed in does not exist in the dictionary (dict),
        this function should output an error message and return.
        Otherwise, this function outputs to the file the word ladder it finds or outputs
        to the file, the message, "No Word Ladder Found."
        
        */
        void outputLadder(const string &start, const string &end, const string &outputFile);


};

#endif
/*
  
    stack<string> temp;
    queue<stack<string>> stack_that_queues;
    stack<string> firstword;
    bool word_ladder_done = false;

    firstword.push(start); //the stack will contain the first word in the ladder
    stack_that_queues.push(firstword); //enqueue that stack onto the queue of stacks

    string word;
    while(!stack_that_queues.empty()) //while the stack is not empty
    {
        temp = stack_that_queues.front();
        word = temp.top();
        
        for(i = dict.begin(); i!=dict.end();++i)
        {
            c = 0;
            string dictword = *i;
            for(int j = 0; j < 5; ++j)
            {
                if(word.at(j) != dictword.at(j))
                {
                    ++c;
                }
            }
            if(c <= 1)
            {
                file << dictword << endl;
                stack<string> newword = temp;
                newword.push(dictword);
                if(dictword == end)
                {
                    file.close();
                    word_ladder_done = true;
                    return;
                }
                else
                {
                    stack_that_queues.push(newword);
                    dict.remove(dictword);
                }
                
            }
            
        }
        stack_that_queues.pop();
    }
    file.close();
     if(!word_ladder_done)
    {
        cout << "No Word Ladder Found." << endl;
        return;
    }

*/