#pragma once
#include"myExceptions.h"
#include"change1Dlength.h"
#include<sstream>

template<class T>
class minHeap
{
public:
	minHeap(int initialCapacity = 10);
	~minHeap() { delete[] heap; }
	bool empty()const { return heapSize == 0; }
	int size()const { return heapSize; }
	const T& top()
	{
		if (heapSize == 0)throw queueEmpty();
		return heap[1];
	}
	void pop();
	void push(const T&);
	void initial(T*, int);
	void output(std::ostream& out)const;
private:
	int heapSize;	//������Ԫ�صĴ�С
	int arrayLength;//���е�����+1
	T* heap;		//Ԫ������
};

//��ʼ��С����
template<class T>
void minHeap<T>::initial(T* theheap, int theSize)
{//������theHeap[1:theSize]�н�С����
	delete[]heap;
	heap = new T[theSize + 1];
	std::copy(theheap + 1, theheap + theSize + 1, heap + 1);
	heapSize = theSize;
	//�ѻ�,�����һ�����к��ӽڵ㿪ʼ�����ڵ����ɨ��
	for (int root = heapSize / 2; root >= 1; root--)
	{
		// ΪԪ��rootElementѰ��λ��
		T rootElement = heap[root];

		int child = 2 * root;//����child��˫����Ԫ��rootElement��λ��

		while (child <= heapSize)
		{
			//heap[child]Ӧ�����ֵ��н�С��
			if (child < heapSize && heap[child] > heap[child + 1])
				child++;
			//���԰�Ԫ��rootElement����heap[child/2]��
			if (rootElement <= heap[child])
				break;//����
			//������
			heap[child / 2] = heap[child];//�Ѻ���������
			child *= 2;					  //�Ƶ���һ��
		}
		heap[child / 2] = rootElement;	//����ֵ
	}
}

//���캯��
template<class T>
minHeap<T>::minHeap(int initialCapacity)
{
	if (initialCapacity < 1)
	{
		std::ostringstream s;
		s << "Initial capacity = " << initialCapacity << " Must be > 0";
		throw illeagalParameterValue(s.str());
	}
	arrayLength = initialCapacity + 1;
	heap = new T[arrayLength];
	heapSize = 0;
}

//push����
template<class T>
void minHeap<T>::push(const T& theElement)
{
	if (heapSize == arrayLength - 1)
	{
		change1Dlength(heap, arrayLength, 2 * arrayLength);
		arrayLength *= 2;
	}

	int currentNode = ++heapSize;
	while (currentNode != 1 && heap[currentNode / 2] > theElement)
	{
		heap[currentNode] = heap[currentNode / 2];
		currentNode /= 2;
	}
	heap[currentNode] = theElement;
}

//pop����
template<class T>
void minHeap<T>::pop()
{
	if (heapSize == 0)throw queueEmpty();
	//ɾ����С��Ԫ��
	heap[1].~T();
	//ɾ�����һ��Ԫ�أ�Ȼ�����½���
	T lastElement = heap[heapSize--];

	//�Ӹ���ʼ��Ϊ���һ��Ԫ��Ѱ��λ��
	int currentNode = 1,
		child = 2;	//currentNode�ĺ���
	while (child <= heapSize)
	{
		//heap[child]Ӧ����currentNode�ĸ�С�ĺ���
		if (child < heapSize && heap[child] > heap[child + 1])
			child++;
		//���԰�lastElement����heap[cureentNode]��?
		if (lastElement <= heap[child])
			break;		//����
		//������
		heap[currentNode] = heap[child];	//�Ѻ���child�����ƶ�
		currentNode = child;				//�����ƶ�һ��Ѱ��λ��
		child *= 2;
	}
	heap[currentNode] = lastElement;
}

template<class T>
void minHeap<T>::output(std::ostream& out)const
{
	std::copy(heap + 1, heap + heapSize + 1, std::ostream_iterator<T>(std::cout, " "));
}

template<class T>
std::ostream& operator<<(std::ostream& out, const minHeap<T>& x)
{
	x.output(out); return out;
}