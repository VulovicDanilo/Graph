#pragma once

#include "Node.hpp"

class Queue
{
private:
	int capacity;
	int front;
	int rear;
	int size;
	Node** array;
public:
	Queue(int N)
	{
		if (N > 0)
		{
			capacity = N;
			array = new Node*[capacity];
			rear = front = size = 0;
			for (int i = 0; i < capacity; i++)
				array[i] = nullptr;
		}
	}
	~Queue()
	{
		for (int i = 0; i < capacity; i++)
			array[i] = nullptr;
		delete[] array;
		array = nullptr;
	}
	inline int getSize() { return size; }
	inline bool isEmpty() { size == 0; }
	inline bool isFull() { size = capacity; }
	void enqueue(Node* node)
	{
		if (!isFull())
		{
			array[rear] = node;
			size++;
			rear = (rear + 1) % capacity;
		}
	}
	Node* dequeue()
	{
		if (!isEmpty())
		{
			Node* toReturn = array[front];
			front = (front + 1) % capacity;
			size--;
			return toReturn;
		}
		else
		{
			return NULL;
		}
	}
};