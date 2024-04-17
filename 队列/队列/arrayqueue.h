#pragma once
#include"myExceptions.h"
#include"queue.h"
#include<sstream>
//ѭ������
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
	T* queue;		//�������
	int arrgylength;//���е�����
	int thefront;//�Ӷ�ͷ��ʱ��+1
	int theback;//��βԪ�ص�λ��
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
	//���ӳ���
	if ((theback + 1) % arrgylength == thefront)
	{
		//����˫���ĳ���
		T* newQueue = new T[2 * arrgylength];
		//��Ԫ�ظ��ƽ��µ�����
		int start = (thefront + 1) % arrgylength;
		if (start < 2)
		{//����û�гɻ�
			std::copy(queue + start, queue + start + arrgylength - 1, newQueue);
		}
		else
		{//���гɻ�
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
