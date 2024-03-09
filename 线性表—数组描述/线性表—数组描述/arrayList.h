#pragma once
#include<iostream>
#include<sstream>
#include<string>
#include<algorithm>
#include "LinearLish.h"
#include "myExceptions.h"
#include "changeLength1D.h"

//using namespace std;
template<class T>
class arrayList :public LinearLish<T>  //arrayList是从LinearListh派生的
{
public:
	//构造函数，复制构造函数，析构函数
	arrayList(int initialCapacity = 10);
	arrayList(const arrayList<T>&);
	~arrayList() { delete[] element; }

	//LinearList内的抽象数据类型的方法
	bool empty()const { return listSize == 0; }
	int size()const { return listSize; }
	T& get(int theIndex)const;
	int indexOf(const T& theElement)const;
	void erase(int theIndex);
	void insert(int theIndex, const T& theElement);
	void output(std::ostream& out)const;

	//新增的方法
	int capacity()const { return arrayLength; }

protected:
	void checkIndex(int theIndex)const;//如果索引无效则抛出非法索引
	T* element;		 //用来存储列表元素的1维数组
	int arrayLength; //1维数组的容量
	int listSize;    //列表中的元素数量
};


//构造函数
template<class T>
arrayList<T>::arrayList(int initialCapacity)
{
	if (initialCapacity < 1)
	{
		//std::ostringstream s;
		std::ostringstream s;
		s << "initial capacity = " << initialCapacity << "must be > 0";
		throw illegalPamerterValue(s.str());
	}

	arrayLength = initialCapacity;
	element = new T[arrayLength];
	listSize = 0;
}

//复制构造函数
template<class T>
arrayList<T>::arrayList(const arrayList<T>& thelist)
{
	arrayLength = thelist.arrayLength;
	listSize = thelist.listSize;
	element = new T[arrayLength];
	std::copy(thelist.element, thelist.element + thelist.listSize, element);
}

//检查索引是否在0-listsize-1之间
template<class T>
void arrayList<T>::checkIndex(int theIndex)const
{
	if (theIndex < 0 || theIndex >= listSize)
	{
		std::ostringstream s;
		s << "index = " << theIndex << "size = " << listSize;
		throw illegalIndex(s.str());
	}
}

//返回索引为theIndex的元素，如果索引下标不对就抛出非法索引异常
template<class T>
T& arrayList<T>::get(int theIndex)const
{
	checkIndex(theIndex);
	return element[theIndex];
}

//返回theElment第一次出现的索引，如果没找到就返回-1
template<class T>
int arrayList<T>::indexOf(const T& theElement)const
{
	int index = (int)(std::find(element, element + listSize, theElement) - element);

	if (index == listSize)
		return -1;
	else return index;
}

//删除索引为theIndex的元素
template<class T>
void arrayList<T>::erase(int theIndex)
{
	checkIndex(theIndex);
	std::copy(element + theIndex + 1, element + listSize, element + theIndex);
	element[--listSize].~T();
}

//插入元素theElment，使其索引为theIndex
template<class T>
void arrayList<T>::insert(int theIndex, const T& theElement)
{
	if (theIndex < 0 || theIndex > listSize)
	{
		std::ostringstream s;
		s << "index = " << theIndex << "size = " << listSize;
		throw illegalIndex(s.str());
	}

	//有效的索引，当空间不足时，空间翻倍
	if (listSize == arrayLength)
	{
		changeLength1D(element, arrayLength, arrayLength * 2);
		arrayLength *= 2;
	}

	std::copy_backward(element + theIndex, element + listSize, element + listSize + 1);
	element[theIndex] = theElement;
	listSize++;
}

//将列表放入流中输出
template<class T>
void arrayList<T>::output(std::ostream& out)const
{
	std::copy(element, element + listSize, std::ostream_iterator<T>(std::cout, " "));
}

template<class T>
std::ostream& operator<<(std::ostream& out, const arrayList<T>& x)
{
	x.output(out);
	return out;
}


