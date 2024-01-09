#include "WordLadder.h"
#include <iostream>
using namespace std;
#include <string>

int main()
{
    string start, end, dictionary, output;
    start = "reads";
    end = "winds";
    dictionary = "dictionary.txt";
    output = "out.txt";

    WordLadder woop(dictionary);
    woop.outputLadder(start, end, output);
    return 0;
}