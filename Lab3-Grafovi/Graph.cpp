#include "Graph.hpp"
#include "Stack.h"
#include "Queue.hpp";

Node* Graph::findNode(int value)
{
	Node* ptr = start;
	while (ptr && ptr->info != value)
	{
		ptr = ptr->nextNode;
	}
	return ptr;
}

Edge* Graph::findEdge(int srcValue, int dstValue)
{
	Node* src = findNode(srcValue);
	Node* dst = findNode(dstValue);
	if (!src || !dst) return NULL;
	Edge* edge = src->adj;
	while (edge && edge->dest != dst)
		edge = edge->next;
	return edge;
}

bool Graph::containsNode(int value)
{
	return findNode(value) ? true : false;
}

bool Graph::containsEdge(int srcValue, int dstValue)
{
	return findEdge(srcValue, dstValue) ? true : false;
}

void Graph::insertNode(int value)
{
	if (!containsNode(value))
	{
		start = new Node(value, 0, start);
		numOfNodes++;
	}
}

void Graph::insertEdge(int srcValue, int dstValue, int weight)
{
	Node* src = findNode(srcValue);
	Node* dst = findNode(dstValue);
	if (src && dst)
	{
		src->adj = new Edge(dst, src->adj, weight);
		dst->adj = new Edge(src, dst->adj, weight);
	}
}

void Graph::deleteNode(int value)
{
	Node* ptr = findNode(value);
	if (ptr)
	{
		Stack stack(numOfNodes);
		Edge* edge = ptr->adj;
		while (edge)
		{
			stack.push(edge->dest);
			Edge* next = edge->next;
			delete edge;
			edge = next;
		}
		while (!stack.isEmpty())
		{
			Node* node = stack.pop();
			Edge* prev = NULL;
			Edge* toDel = node->adj;
			while (toDel)
			{
				if (toDel->dest == ptr)
				{
					if (!prev)
					{
						node->adj = toDel->next;
						delete toDel;
						toDel = node->adj;
					}
					else
					{
						prev->next = toDel->next;
						delete toDel;
						toDel = prev->next;
					}
				}
				else
				{
					prev = toDel;
					toDel = toDel->next;
				}
			}
		}
		if (start == ptr)
		{
			start = start->nextNode;
			delete ptr;
		}
		else
		{
			Node* current = start;
			while (current && current->nextNode != ptr)
			{
				current = current->nextNode;
			}
			current->nextNode = ptr->nextNode;
		}
		delete ptr;
		numOfNodes--;
	}
}

void Graph::deleteEdge(int srcValue, int dstValue)
{
	Node* src = findNode(srcValue);
	Node* dst = findNode(dstValue);
	if (src && dst)
	{
		// delete src->dst
		Edge* prev = NULL;
		Edge* toDel = src->adj;
		while (toDel && toDel->dest != dst)
		{
			prev = toDel;
			toDel = toDel->next;
		}
		if (!prev && toDel)
		{
			src->adj = toDel->next;
			delete toDel;
		}
		else if (prev && toDel)
		{
			prev->next = toDel->next;
			delete toDel;
		}
		// delete dst->src
		prev = NULL;
		toDel = dst->adj;
		while (toDel && toDel->dest != src)
		{
			prev = toDel;
			toDel = toDel->next;
		}
		if (!prev && toDel)
		{
			dst->adj = toDel->next;
			delete toDel;
		}
		else if (prev && toDel)
		{
			prev->next = toDel->next;
			delete toDel;
		}
	}
}

void Graph::bfs()
{
	if (!start)
	{
		cout << "Graph is empty!" << endl;
		return;
	}
	cout << "BFS: ";
	Node* node = start;
	while (node)
	{
		node->status = Status::Unvisited;
		node = node->nextNode;
	}
	Queue queue(numOfNodes);
	queue.enqueue(start);
	start->status = Status::Visited;
	while (!queue.isEmpty())
	{
		Node* ptr = queue.dequeue();
		cout << ptr->info << " ";
		Edge* edge = ptr->adj;
		while (edge)
		{
			if (edge->dest->status == Status::Unvisited)
			{
				queue.enqueue(edge->dest);
				edge->dest->status = Status::Visited;
			}
			edge = edge->next;
		}
	}
	cout << endl;
}

void Graph::dfs()
{
	if (!start)
	{
		cout << "Graph is empty!" << endl;
		return;
	}
	cout << "DFS: ";
	Node* node = start;
	while (node)
	{
		node->status = Status::Unvisited;
		node = node->nextNode;
	}
	Stack stack(numOfNodes);
	stack.push(start);
	start->status = Status::Visited;
	while (!stack.isEmpty())
	{
		Node* ptr = stack.pop();
		cout << ptr->info << " ";
		Edge* edge = ptr->adj;
		while (edge)
		{
			if (edge->dest->status == Status::Unvisited)
			{
				stack.push(edge->dest);
				edge->dest->status = Status::Visited;
			}
			edge = edge->next;
		}
	}
	cout << endl;
}

void Graph::printGraph()
{
	Node* ptr = start;
	while (ptr)
	{
		ptr->printNode();
		ptr = ptr->nextNode;
	}
}

void Graph::printAdjMatrix()
{
	AdjMatrix adj(this);
	adj.print(start);
}

AdjMatrix::AdjMatrix(Graph* g)
{
	dim = g->getNumOfNodes();
	mat = new int*[dim];
	for (int i = 0; i < dim; i++)
		mat[i] = new int[dim];
	for (int i = 0; i < dim; i++)
		for (int j = 0; j < dim; j++)
			mat[i][j] = 0;
	int i = 0;
	Node* ptr = g->getStart();
	while (ptr)
	{
		ptr->index = i++;
		ptr = ptr->nextNode;
	}
	Node* ptrNode = g->getStart();
	while (ptrNode)
	{
		Edge* ptrEdge = ptrNode->adj;
		while (ptrEdge)
		{
			mat[ptrNode->index][ptrEdge->dest->index] = 1;
			mat[ptrEdge->dest->index][ptrNode->index] = 1; // za bidirekcione;
			ptrEdge = ptrEdge->next;
		}
		ptrNode = ptrNode->nextNode;
	}
}

void AdjMatrix::print(Node* start)
{
	int i = 0;
	cout << "Index -> Node" << endl;
	Node* ptr = start;
	while (ptr)
	{
		cout << i++ << " -> " << ptr->info << endl;
		ptr = ptr->nextNode;
	}
	cout << "Adjacency matrix:" << endl;
	cout << "  ";
	for (int i = 0; i < dim; i++)
	{
		cout << i << " ";
	}
	cout << endl;
	for (int i = 0; i < dim; i++)
	{
		cout << i << " ";
		for (int j = 0; j < dim; j++)
		{
			cout << mat[i][j] << " ";
		}
		cout << endl;
	}
}