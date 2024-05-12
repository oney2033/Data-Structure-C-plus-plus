#pragma once
#include"myExceptions.h"
#include"change1Dlength.h"
#include<sstream>
#include<algorithm>


template<class T>
class maxHeap 
{
public:
	maxHeap(int initialCapacity = 10);
	~maxHeap()
	{
	//	std::cout << "deststruct" << std::endl;
		delete[] heap;
	}
	bool empty()const { return heapSize == 0; }
	int size()const { return heapSize; }
	const T& top()
	{//��������Ԫ��
		if (heapSize == 0)throw queueEmpty();
		return heap[1];
	}
	void pop();
	void push(const T&);
	void initialize(T*, int);
	void deactivateArray()
	{
		heap = NULL; heapSize = arrayLength = 0;
	}
	void output(std::ostream& out)const;

private:
	T* heap;	//��Ա����
	int heapSize; //�����г�Ա������
	int arrayLength;//���е����� + 1
};

//���캯��
template<class T>
maxHeap<T>::maxHeap(int initialCapacity)
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

//���뺯��
template<class T>
void maxHeap<T>::push(const T& theElement)
{//��Ԫ��theElement �����
	//��Ҫʱ�������鳤��
	if (heapSize == arrayLength - 1)
	{//����ӱ�
		change1Dlength(heap, arrayLength, 2 * arrayLength);
		arrayLength *= 2;
	}
	//ΪԪ��theElementѰ�Ҳ���λ��
	//currentNode ����Ҷ�������ƶ�
	int currentNode = ++heapSize;
	while (currentNode != 1 && heap[currentNode / 2] < theElement)
	{
		//���ܰ�Ԫ��theElement������heap[currentNode]
		heap[currentNode] = heap[currentNode / 2];//��Ԫ�������ƶ�
		currentNode /= 2;	//����˫��
	}
	heap[currentNode] = theElement;
}

//ɾ������
template<class T>
void maxHeap<T>::pop()
{//ɾ�����Ԫ��
	if (heapSize == 0)throw queueEmpty();
	heap[1].~T();

	//ɾ�����һ��Ԫ�أ�Ȼ�����½���
	T lastElement = heap[heapSize--];

	//�Ӹ���ʼ��Ϊ���һ��Ԫ��Ѱ��λ��
	int currentNode = 1,
		child = 2;	//currentNode�ĺ���
	while (child <= heapSize)
	{
		//heap[child]Ӧ����currtNode�ĸ���ĺ���
		if (child < heapSize && heap[child] < heap[child + 1])
			child++;

		//���԰�lastElement����heap[currentNode]��
		if (lastElement >= heap[child])
			break;		//����

		//������
		heap[currentNode] = heap[child];	//�Ѻ���child�����ƶ�
		currentNode = child;				//�����ƶ�һ��Ѱ��λ��
		child *= 2;
	}
	heap[currentNode] = lastElement;
}

//��ʼ��һ���ǿմ����
template<class T>
void maxHeap<T>::initialize(T* theheap, int theSize)
{//������theHeap[1:theSize]�н������
	delete[] heap;
	heap = new T[theSize + 1];
	std::copy(theheap + 1, theheap + theSize + 1, heap + 1);
	heapSize = theSize;

	//�ѻ�
	for (int root = heapSize / 2; root >= 1; root--)
	{
		T rootElement = heap[root];

		//ΪԪ��rootElementѰ��λ��
		int child = 2 * root;	//����child��˫����Ԫ��rootElement��λ��
		while (child <= heapSize)
		{
			//heap[child]Ӧ�����ֵ��нϴ���
			if (child < heapSize && heap[child] < heap[child + 1])
			{
				child++;
			}
			//���԰�Ԫ��rootElement����heap[child/2]��
			if (rootElement >= heap[child])
				break;	//����
			//������
			heap[child / 2] = heap[child];	//�Ѻ���������
			child *= 2;					//�Ƶ���һ��
		}
		heap[child / 2] = rootElement;
	}
}

template<class T>
void maxHeap<T>::output(std::ostream& out)const
{
	std::copy(heap + 1, heap + heapSize + 1, std::ostream_iterator<T>(std::cout, " "));
}

template<class T>
std::ostream& operator<<(std::ostream& out, const maxHeap<T>& x)
{
	x.output(out); return out;
}