/* Adjacency List representations of a un-directed graph */
 
/* Graph representation 
	(0)--------(1)
	 | |        |
	 |   |      |
	 |     |    |
	 |        | |
	(3)--------(2)
*/	

#include <iostream>
#include <list>

using namespace std;

class Graph {
	private:
		int V; // Number of vertex
		list<int> *adjList;
	public:
		Graph(int V);
		/* Add the Edges of graph */
		void addEdge(int src, int dest);
		/* Print the Graph Adjacency List view */
		void printGraph();			
};

Graph::Graph(int V) {
	this->V = V;
	adjList = new list<int>[V];
}

void Graph::addEdge(int src, int dest)
{
    // Add edge from src to dest vertex
	adjList[src].push_front(dest);
    // Add edge from dest to src vertex
    adjList[dest].push_front(src);
}

void Graph::printGraph() {	
	
	for(int i = 0; i < 4; i++) {
		std::cout<<"Vertex: "<<i;
		for(list<int>::iterator it = adjList[i].begin(); it!=adjList[i].end(); it++)
		{
			std::cout<<"->"<<*it;
		}
		std::cout<<"\n";
	}
	std::cout<<"\n";
}

int main(int argc, char **argv) {
	Graph graph(4);
	graph.addEdge(0, 1);
	graph.addEdge(0, 2);
	graph.addEdge(0, 3);
	graph.addEdge(1, 2);
	graph.addEdge(2, 3);
    
	graph.printGraph();
	return 0; 
}