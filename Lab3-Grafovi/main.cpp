#include "Graph.hpp"

int main()
{
	Graph g;
	int nodes = 10000;
	for (int i = 0; i < nodes; i++)
		g.insertNode(i);
	for (int i = 0; i < nodes; i++)
		g.insertEdge(i, (i + 1) % nodes, 1);
	g.printGraph();



	//for (int i = 1; i < 5; i++)
	//	g.deleteNode(i);
	//g.printAdjMatrix();
	return 0;
}