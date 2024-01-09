#include <cstring>
#include "Graph.h"
using namespace std;

int main(int argc, char* argv[]) {
  
  if(argc != 2) {
    cerr << "Usage error: expected <executable> <input>" << endl;
    exit(1);
  }
  ifstream ifs(argv[1]);
  if(!ifs) {
    cerr << "Input file not found." << endl;
    exit(1);
  }
  cout << "0 ";
  Graph g(ifs);
  cout << "1" << " ";
  ifs.close();
  cout << "2" << " ";
  g.bfs();
  cout << "3" << " ";
  string filename = strcat(argv[1] , ".dot");
  cout << "4" << " ";
  g.output_graph(filename);
  cout << "5" << endl;
  cout << "The End." << endl;
  
  return 0;
}
