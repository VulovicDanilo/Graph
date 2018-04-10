#pragma once

#include "Node.hpp"

class Stack
{
private:
	int top;
	int capacity;
	Node** array;
public:
	Stack(int N)
	{
		if (N > 0)
		{
			capacity = N;
			top = 0;
			array = new Node*[capacity];
			for (int i = 0; i < capacity; i++)
				array[i] = nullptr;
		}
	}
	~Stack()
	{
		for (int i = 0; i < top; i++)
			array[i] = nullptr;
		delete[] array;
		array = nullptr;
	}
	inline bool isEmpty() { return top == 0; }
	inline bool isFull() { return top == capacity; }
	void push(Node* node)
	{
		if (!isFull())
		{
			array[top++] = node;
		}
	}
	Node* pop()
	{
		if (!isEmpty())
		{
			return array[--top];
		}
		else
		{
			return NULL;
		}
	}
};