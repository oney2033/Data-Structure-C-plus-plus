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
	int heapSize;	//队列中元素的大小
	int arrayLength;//队列的容量+1
	T* heap;		//元素数组
};

//初始化小根堆
template<class T>
void minHeap<T>::initial(T* theheap, int theSize)
{//在数组theHeap[1:theSize]中建小根堆
	delete[]heap;
	heap = new T[theSize + 1];
	std::copy(theheap + 1, theheap + theSize + 1, heap + 1);
	heapSize = theSize;
	//堆化,从最后一个具有孩子节点开始到根节点进行扫描
	for (int root = heapSize / 2; root >= 1; root--)
	{
		// 为元素rootElement寻找位置
		T rootElement = heap[root];

		int child = 2 * root;//孩子child的双亲是元素rootElement的位置

		while (child <= heapSize)
		{
			//heap[child]应该是兄弟中较小者
			if (child < heapSize && heap[child] > heap[child + 1])
				child++;
			//可以把元素rootElement放在heap[child/2]吗
			if (rootElement <= heap[child])
				break;//可以
			//不可以
			heap[child / 2] = heap[child];//把孩子向上移
			child *= 2;					  //移到下一层
		}
		heap[child / 2] = rootElement;	//更新值
	}
}

//构造函数
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

//push函数
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

//pop函数
template<class T>
void minHeap<T>::pop()
{
	if (heapSize == 0)throw queueEmpty();
	//删除最小的元素
	heap[1].~T();
	//删除最后一个元素，然后重新建堆
	T lastElement = heap[heapSize--];

	//从根开始，为最后一个元素寻找位置
	int currentNode = 1,
		child = 2;	//currentNode的孩子
	while (child <= heapSize)
	{
		//heap[child]应该是currentNode的更小的孩子
		if (child < heapSize && heap[child] > heap[child + 1])
			child++;
		//可以把lastElement放在heap[cureentNode]吗?
		if (lastElement <= heap[child])
			break;		//可以
		//不可以
		heap[currentNode] = heap[child];	//把孩子child向上移动
		currentNode = child;				//向下移动一层寻找位置
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