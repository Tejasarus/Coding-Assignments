#include "Graph.h"

#include <vector>
#include <list>
#include <queue>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <climits>
#include <string>
#include <map>

using namespace std;

Graph::Graph(){}

Graph::Graph(ifstream& ifs)
{
    map<string,int> Graph;
    string temp, temp1, temp2;
    int Edges, Nodes, weight, index;

    ifs >> Nodes >> Edges; //get the # of nodes and edges from the file

    //cycle "# of nodes" times and add those strings to the verticies vector
    for(int i = 0; i < Nodes; ++i) 
    {
        ifs >> temp;
        Vertex t; //create a temp vertex
        t.label = temp; //make the vertex label the string
        vertices.push_back(t); //push back the vertex onto the vector
        Graph[temp] = i; //give it an index
    }
    //now cycle "# of edges" times and pair the second string with the first
   for(int i = 0; i < Edges; ++i)
   {
       ifs >> temp1 >> temp2 >> weight; //get the three values (string, string, int)
       index = Graph[temp1]; //get the index of the first string from the graph
       pair<int,int> pear(Graph[temp2], weight); //make a pair with the index of the second graph, and the weight
       vertices.at(index).neighbors.push_back(pear); //make the pair the neighbor to the first string
   }

}

Graph::~Graph()
{
    //pop all verticies until the vector is empty
    while(vertices.size()!=0)
    {
        vertices.pop_back();
    }
}

void Graph::output_graph(const string &file)
{
    //open the file and check to see if it is open
    ofstream out;
    out.open(file);
    if (!out.is_open())
    {
        return;
    }

    //syntax
    out << "digraph G {" << endl;
    
    //cycle through each vertex
    for (unsigned i = 0; i < vertices.size(); i++)  
    {
    	if (vertices.at(i).distance != INT_MAX) //if the vertex actually has a distance, draw it in the graph
        {
            out << vertices.at(i).label << "[label = \"" << vertices.at(i).label << ", " << vertices.at(i).distance << "\"]" << endl;
    	}
     	if (!vertices.at(i).neighbors.empty()) //if the node has adjacent nodes (neighbors)
        {
            //cycle through all of the neighbors and link the "parent" to them
     	    list<pair<int, int> >::iterator t = vertices.at(i).neighbors.begin(); 

     		while (t != vertices.at(i).neighbors.end()) 
            {
     			if (vertices.at(i).distance!= INT_MAX) 
                {
     		        out << vertices.at(i).label << " -> " << vertices.at(t->first).label << endl;
     			}

     		    t++;
     		}
     	}
     	    
    }
    //syntax to close it off and close
    out<<"}";
    out.close();

    //turn it into a jpg
    string jpgFilename = file.substr(0,file.size()-4)+".jpg"; // -4 is so the " dot" is not in the file name of the jpg
    string command = "dot -Tpng " + file + " -o " + jpgFilename;
    system(command.c_str());

}

void Graph::bfs() 
{

	map<string, unsigned> graph;

	for (unsigned i = 0; i < vertices.size(); i++) //set all of the verticies to "unread" (white means unread, green means read)
    {
		vertices.at(i).distance = INT_MAX;
        vertices.at(i).color = "WHITE";
		vertices.at(i).prev = 0;
		graph[vertices.at(i).label] = i;
	}
	
    //set the "root" to "read" and its distance to 0
	vertices.at(0).color = "GREEN"; 
	vertices.at(0).distance = 0;

    //push root onto queue
	queue<Vertex> q;
	q.push(vertices.at(0));
	Vertex tempV;
	
    //follow bfs algorithm
	while (!q.empty()) 
    {
        //copy the front queue and then pop it
		tempV = q.front();
		q.pop();

		list<pair<int, int> >::iterator t = tempV.neighbors.begin(); //get the neighbor (pair) of the front queue that was just popped

		while (t != tempV.neighbors.end()) //while we havent reached the end of neighbors (run out of adjacent nodes)
        {
			if (vertices.at(t->first).color == "WHITE") //if its unread, update its preferences
            {
				vertices.at(t->first).color = "GREEN"; //make it read
				vertices.at(t->first).distance = tempV.distance + t->second; //give it its distance (front node distance + pair distance)
				vertices.at(t->first).prev = &vertices.at(graph[tempV.label]); //make the prev pointer its parent node
				q.push(vertices.at(t->first)); //push the first point onto the queue
			}
			
			++t; //move onto the next item in the list of neighbors
		}
	}
}