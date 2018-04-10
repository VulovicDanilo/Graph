#include "Graph.hpp"

int main()
{
	Graph g;
	int nodes = 10;
	for (int i = 0; i < nodes; i++)
		g.insertNode(i);
	for (int i = 0; i < nodes; i++)
		g.insertEdge(i, (i + 1) % nodes, 1);
	g.printGraph();
	g.bfs();
	g.dfs();



	//for (int i = 1; i < 5; i++)
	//	g.deleteNode(i);
	//g.printAdjMatrix();
	return 0;
}