#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <map>
using namespace std;

typedef map<string, int> Mappy; //will hold a word with the amount of times it appears in a string

void CountWords(istream&, Mappy);


int main(int argc, char* argv[])
{
    /*
    So the steps of Huffman coding are relatively straightforward:
    1. Pass through the data once, collecting a list of token-frequency counts.
    2. Sort the token-frequency counts by frequency, in descending order.
    3. Assign codes to tokens using a simple counter, for example by incrementing over the
    integers; this is just to keep things simple.
    4. Store the new mapping (token -> code) in a hashtable called “encoder”.
    5. Store the reverse mapping (code -> token) in a hashtable called "decoder".
    6. Pass through the data a second time. This time, replace all tokens with their codes.
    Now, be amazed at how much you've shrunk your data!
    */   

    //Step 1: Pass through the data once, collect a list of token-frequency counts
    
    //open file and check to see if it opened properly
    ifstream ifs(argv[1]);
    if(!ifs) 
    {
        cout << "Input file not found." << endl;
        exit(1);
    }
    
    Mappy m;
    CountWords(ifs, m); //count everything in the file

    //Step 2: Sort the token-frequency counts by frequency, in descending order.

    return 0;
}

//helper function, counts all of the words
void CountWords(istream& in, Mappy words)
{
    string str;
    int c = 0;

    while(in >> str) //cycle through the entire list and count how many times the word is listed
    {
        ++c;
        ++words[str];
    }
    cout << c;
}