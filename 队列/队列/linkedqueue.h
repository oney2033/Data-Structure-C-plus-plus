#pragma once
#include"chainNode.h"
#include"queue.h"
#include"myExceptions.h"
template<class T>
class linkedqueue :public queue<T>
{
public:
	linkedqueue(int initialCapacity = 10)
	{
		queueFront = NULL; queueSize = 0;
	}
	~linkedqueue();
	bool empty()const { return queueSize == 0; }
	int size()const { return queueSize; }
	T& front()
	{
		if (queueSize == 0)
			throw queueempty();
		return queueFront->element;
	}
	T& back()
	{
		if (queueSize == 0)
			throw queueempty();
		return queueBack->element;
	}
	void pop();
	void push(const T&);

private:
	chainNode<T>* queueFront; //队列的头指针
	chainNode<T>* queueBack;  //队列的尾指针
	int queueSize;			 //队列中元素的数量
};

template<class T>
linkedqueue<T>::~linkedqueue()
{
	//删除头指针
	while (queueFront != NULL)
	{
	chainNode<T>* nextNode = queueFront->next;
	delete queueFront;
	queueFront = nextNode;
	}
}

template<class T>
void linkedqueue<T>::pop()
{
	if (queueSize == 0)
		throw queueempty();
	chainNode<T>* nextNode = queueFront->next;
	delete queueFront;
	queueFront = nextNode;
	queueSize--;
}

template<class T>
void linkedqueue<T>::push(const T& element)
{
	//创建新的节点
	chainNode<T>* newNode = new chainNode<T>(element, NULL);
	//添加新的节点在队列后面
	if (queueSize == 0)
		queueFront = newNode;
	else
		queueBack->next = newNode;
	queueBack = newNode;
	queueSize++;
}