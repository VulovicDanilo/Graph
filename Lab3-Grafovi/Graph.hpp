#pragma once

#include "Node.hpp"

class Graph
{
private:
	// attributes
	Node * start;
	int numOfNodes;
public:
	// constructors
	Graph() { start = nullptr; numOfNodes = 0; }
	~Graph() {}

	// getters
	inline Node* getStart() { return start; } 
	inline int getNumOfNodes() { return numOfNodes; }

	// methodes
	Node* findNode(int value);
	Edge* findEdge(int srcNode, int dstNode);
	void deleteNode(int value);
	void deleteEdge(int srcNode, int dstNode);
	bool containsNode(int value);
	bool containsEdge(int src, int dst);
	void insertNode(int info);
	void insertEdge(int srcNode, int dstNode, int weight);
	void bfs();
	void dfs();
	void printGraph();
	void printAdjMatrix();


};

class AdjMatrix
{
private:
	int dim;
	int **mat;
public:
	AdjMatrix(Graph* G);
	void print(Node* start);
};