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
	{//返回最大的元素
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
	T* heap;	//成员数组
	int heapSize; //队列中成员的数量
	int arrayLength;//队列的容量 + 1
};

//构造函数
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

//插入函数
template<class T>
void maxHeap<T>::push(const T& theElement)
{//把元素theElement 加入堆
	//必要时增加数组长度
	if (heapSize == arrayLength - 1)
	{//数组加倍
		change1Dlength(heap, arrayLength, 2 * arrayLength);
		arrayLength *= 2;
	}
	//为元素theElement寻找插入位置
	//currentNode 从新叶子向上移动
	int currentNode = ++heapSize;
	while (currentNode != 1 && heap[currentNode / 2] < theElement)
	{
		//不能把元素theElement插入在heap[currentNode]
		heap[currentNode] = heap[currentNode / 2];//把元素向下移动
		currentNode /= 2;	//移向双亲
	}
	heap[currentNode] = theElement;
}

//删除函数
template<class T>
void maxHeap<T>::pop()
{//删除最大元素
	if (heapSize == 0)throw queueEmpty();
	heap[1].~T();

	//删除最后一个元素，然后重新建堆
	T lastElement = heap[heapSize--];

	//从根开始，为最后一个元素寻找位置
	int currentNode = 1,
		child = 2;	//currentNode的孩子
	while (child <= heapSize)
	{
		//heap[child]应该是currtNode的更大的孩子
		if (child < heapSize && heap[child] < heap[child + 1])
			child++;

		//可以把lastElement放在heap[currentNode]吗？
		if (lastElement >= heap[child])
			break;		//可以

		//不可以
		heap[currentNode] = heap[child];	//把孩子child向上移动
		currentNode = child;				//向下移动一层寻找位置
		child *= 2;
	}
	heap[currentNode] = lastElement;
}

//初始化一个非空大根堆
template<class T>
void maxHeap<T>::initialize(T* theheap, int theSize)
{//在数组theHeap[1:theSize]中建大根堆
	delete[] heap;
	heap = new T[theSize + 1];
	std::copy(theheap + 1, theheap + theSize + 1, heap + 1);
	heapSize = theSize;

	//堆化
	for (int root = heapSize / 2; root >= 1; root--)
	{
		T rootElement = heap[root];

		//为元素rootElement寻找位置
		int child = 2 * root;	//孩子child的双亲是元素rootElement的位置
		while (child <= heapSize)
		{
			//heap[child]应该是兄弟中较大者
			if (child < heapSize && heap[child] < heap[child + 1])
			{
				child++;
			}
			//可以把元素rootElement放在heap[child/2]吗
			if (rootElement >= heap[child])
				break;	//可以
			//不可以
			heap[child / 2] = heap[child];	//把孩子向上移
			child *= 2;					//移到下一层
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