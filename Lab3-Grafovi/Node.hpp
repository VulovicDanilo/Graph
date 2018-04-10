#pragma once

#include "Edge.hpp"

class Node
{
public:
	// attributes
	int info;
	Edge* adj;
	Node* nextNode;

	Status status;
	int distance;
	int index;
	// constructors
	Node() { adj = nullptr; nextNode = nullptr; status = (Status)0; distance = 0; }
	Node(int info):Node() { this->info = info; }
	Node(int info, Edge* adj, Node* down)
	{
		this->info = info;
		this->adj = adj;
		this->nextNode = down;
		status = (Status)0;
		distance = 0;
	}
	void printNode()
	{
		cout << "Info: " << info;
		cout << " Neighbours: ";
		Edge* ptr = adj;
		while (ptr)
		{
			cout << ptr->dest->info << " ";
			ptr = ptr->next;
		}
		cout << endl;
	}
};