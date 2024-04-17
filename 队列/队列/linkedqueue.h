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
	chainNode<T>* queueFront; //���е�ͷָ��
	chainNode<T>* queueBack;  //���е�βָ��
	int queueSize;			 //������Ԫ�ص�����
};

template<class T>
linkedqueue<T>::~linkedqueue()
{
	//ɾ��ͷָ��
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
	//�����µĽڵ�
	chainNode<T>* newNode = new chainNode<T>(element, NULL);
	//����µĽڵ��ڶ��к���
	if (queueSize == 0)
		queueFront = newNode;
	else
		queueBack->next = newNode;
	queueBack = newNode;
	queueSize++;
}