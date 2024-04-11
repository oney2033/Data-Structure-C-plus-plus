#pragma once
#include<iostream>
#include<sstream>
#include"changeLength1D.h"
#include"stack.h"

template<class T>
class arraystack :public stack<T>
{
public:
	arraystack(int initialCapacity = 10);
	~arraystack() { delete[]stack; }
	bool empty()const { return stacktop == -1; }
	int size()const { return stacktop + 1; }
	void push(const T& theElment);
	T& top()
	{
		if (stacktop == -1)
			throw stackEmpty();
		return stack[stacktop];
	}
	void pop()
	{
		if (stacktop == -1)
			throw stackEmpty();
		stack[stacktop--].~T();
	}
private:
	T* stack;     //元素数组
	int stacktop; //栈顶
	int arrayLength;//栈的容量
};

template<class T>
arraystack<T>::arraystack(int initialCapacity)
{
	if (initialCapacity < 1)
	{
		std::ostringstream s;
		s << "Initial capacity = " << initialCapacity << "Must be > 0";
		throw illegalParameterValue(s.str());
	}
	arrayLength = initialCapacity;
	stack = new T[arrayLength];
	stacktop = -1;
}
template<class T>
void arraystack<T>::push(const T& theElment)
{
	if (stacktop == arrayLength - 1)
	{
		changeLength1D(stack, arrayLength, 2 * arrayLength);
		arrayLength *= 2;
	}
	stack[++stacktop] = theElment;
}