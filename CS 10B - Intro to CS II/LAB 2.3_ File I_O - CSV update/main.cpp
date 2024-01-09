#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

int main(int argc, char *argv[]) {
   
   string inputFile;
   string outputFile;
   
   // Assign to inputFile value of 2nd command line argument
   // Assign to outputFile value of 3rd command line argument
   inputFile = argv[1];
   outputFile = argv[2];
    
    
   // Create input stream and open input csv file.
   ifstream file; 
    file.open(inputFile);
   // Verify file opened correctly.
   // Output error message and return 1 if file stream did not open correctly.
    if(!file.is_open())
    {
        cout << "Error opening " << inputFile;
        exit(1);
    }
    string str;
    vector<int> data;
    
   while(getline(file, str, ','))
   {
       data.push_back(stoi(str));
      // cout << str << endl;
   }
   // Read in integers from input file to vector.
   int size = data.size();
   // Close input stream.
   file.close();
   // Get integer average of all values read in.
   int sum = 0, average;
    for(int i = 0; i < size; ++i)
    {
        sum = sum + data.at(i);
    }
    average = sum / data.size();
   // Convert each value within vector to be the difference between the original value and the average.
   for(int i = 0; i <size; ++i)
   {
       data.at(i) = data.at(i) - average;
   }
   // Create output stream and open/create output csv file.
    ofstream ofile;
    ofile.open(outputFile);
   // Verify file opened or was created correctly.
   // Output error message and return 1 if file stream did not open correctly.
   
    if(!ofile.is_open())
    {
        cout << "Error opening " << outputFile;
        exit(1);
    }
   // Write converted values into ouptut csv file, each integer separated by a comma.
    string str_out;
   for(int i = 0; i < size; ++i)
   {
       str_out = to_string(data.at(i));
       ofile << str_out;
       if( i + 1 < size)
       {
           ofile << ",";
       }
   }
    
   // Close output stream.
   
   ofile.close();
   return 0;
}