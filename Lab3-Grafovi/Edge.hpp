#pragma once

#include "iostream"
class Node;

using namespace std;

class Edge
{
public:
	// attributes
	Node * dest;
	Edge* next;
	int weight;
	// constructors
	Edge() { next = nullptr; dest = nullptr; }
	Edge(Node* dest, Edge* next, int weight)
	{
		this->dest = dest; 
		this->next = next; 
		this->weight = weight;
	}
};

enum class Status
{
	Unvisited = 0,
	Visited
};