#pragma once
#include"myExceptions.h"
#include"queue.h"
#include<sstream>
//循环队列
template<class T>
class arrayqueue :public queue<T>
{
public:
	arrayqueue(int initialCapacity = 10);
	~arrayqueue() { delete[]queue; }
	bool empty()const { return thefront == theback; }
	int size()const { return (theback - thefront + arrgylength)%arrgylength; }
	T& front()
	{
		if (thefront == theback)
			throw queueempty();
		return queue[(thefront + 1) % arrgylength];
	}
	T& back()
	{
		if (thefront == theback)
			throw queueempty();
		return queue[theback];
	}
	void pop()
	{
		if (thefront == theback)
			throw queueempty();
		thefront = (thefront + 1) % arrgylength;
		queue[thefront].~T();
	}
	void push(const T& theelement);
private:
	T* queue;		//数组队列
	int arrgylength;//队列的容量
	int thefront;//从队头逆时针+1
	int theback;//队尾元素的位置
};

template<class T>
arrayqueue<T>::arrayqueue(int initialCapacity)
{
	if (initialCapacity < 1)
	{
		std::ostringstream s;
		s << "Initial capacity = " << initialCapacity << " Must be > 0";
		throw illegalParameterVaule(s.str());
	}
	arrgylength = initialCapacity;
	queue = new T[arrgylength];
	thefront = 0;
	theback = 0;
}

template<class T>
void arrayqueue<T>::push(const T& thelement)
{
	//增加长度
	if ((theback + 1) % arrgylength == thefront)
	{
		//增加双倍的长度
		T* newQueue = new T[2 * arrgylength];
		//将元素复制进新的数组
		int start = (thefront + 1) % arrgylength;
		if (start < 2)
		{//队列没有成环
			std::copy(queue + start, queue + start + arrgylength - 1, newQueue);
		}
		else
		{//队列成环
			std::copy(queue + start, queue + arrgylength, newQueue);
			std::copy(queue, queue + theback + 1, newQueue + arrgylength - start);
		}
		thefront = 2 * arrgylength - 1;
		theback = arrgylength - 2;
		arrgylength *= 2;
		queue = newQueue;
	}
	theback = (theback + 1) % arrgylength;
	queue[theback] = thelement;
}
