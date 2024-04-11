#pragma once
#include"stack.h"
#include"chainNode.h"
#include"myExceptions.h"
template<class T>
class linkedstack :public stack<T>
{
public:
	linkedstack(int initialCapacity = 10) { stackTop = NULL; stackSize = 0; }
	~linkedstack();
	bool empty()const { return stackSize == 0; }
	int size()const { return stackSize; }
	void pop();
	T& top()
	{
		if (stackSize == 0)
			throw stackEmpty();
		return stackTop->element;
	}
	void push(const T& theElment)
	{
		stackTop = new chainNode<T>(theElment, stackTop);
		stackSize++;
	}
	
private:
	chainNode<T>* stackTop;//栈顶指针
	int stackSize;//栈中的元素的个数
};

template<class T>
linkedstack<T>::~linkedstack()
{
	while (stackTop != NULL)
	{
		chainNode<T>* next = stackTop->next;
		delete stackTop;
		stackTop = next;
	}
}

template<class T>
void linkedstack<T>::pop()
{
	if (stackSize == 0)
		throw stackEmpty();
	chainNode<T>* next = stackTop->next;
	delete[]stackTop;
	stackTop = next;
	stackSize--;
}