#pragma once
#include<iostream>
#include<sstream>
#include<string>
#include<algorithm>
#include "LinearLish.h"
#include "myExceptions.h"
#include "changeLength1D.h"

using namespace std;
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


	//列表开始和结束的迭代器
	class iterator;
	iterator begin() { return iterator(element); }
	iterator end() { return iterator(element + listSize); }

	//arrayList的迭代器
	class iterator
	{
	public:
		// C++ 双向迭代器所需的 typedef
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef T value_type;
		typedef std::ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T& reference;

		//构造函数
		iterator(T* thePosition = 0) { position = thePosition; }

		// 解引用运算符
		T& operator*()const { return *position; }
		T* operator->()const { return &*position; }

		// 自增
		iterator& operator++() { ++position; return *this; }
		iterator operator++(int) { iterator old = *this; ++position; return old; }

		//自减
		iterator& operator--() { --position; return *this; }
		iterator operator--(int) { iterator old = *this; --position; return old; }

		//判断是否不等
		bool operator!=(const iterator right) const
		{
			return position != right.position;
		}

		//判断是否相等
		bool operator==(const iterator right) const
		{
			return position == right.position;
		}
	protected:
		T* position;
	};//定义迭代器的结尾


	//其它一些练习的代码

	//从左到右非递减有序合并两个数组
	void merge(const arrayList<T>& a, const arrayList<T>& b);

	//将列表内的元素隔一个删除一个
	void half();

	//将列表内的元素左移 theAmount位
	void leftShift(int theAmount);

	//返回指定元素最后出现的位置
	void lastIndexOf(const T& theElment)const;

	//删除范围内的元素
	void removeRange(int start, int end);

	//清空列表
	void clear();

	//设置指定索引的值
	void set(int theIndex, const T& theElment);

	//交换两个列表
	void myswap(arrayList<T>& thelist);

	//弹出最后的元素
	void pop_back();

	//从后插入元素
	void push_back(const T& theElment);

	//数组的大小根据需求进行调整，以节省空间
	void trimToSize();

	//重载 != 操作符号
	bool operator !=(const arrayList<T>& thelist)const;

	//重载 [] 操作符号
	T& operator[](int);

	//返回数组的容量
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

//从左到右非递减合并两个数组
template<class T>
void arrayList<T>::merge(const arrayList<T>& a, const arrayList<T>& b)
{
	int ca, cb, ct = 0;//游标，用来访问两个数组
	//保证有足够的空间
	delete[]element;
	arrayLength = a.listSize + b.listSize;
	element = new T[arrayLength];
	//开始合并
	while ((ca < a.listSize) && cb < b.listSize)
	{
		if (a.element[ca] <= b.element[cb])
			element[ct++] = a.element[ca++];
		else
			element[ct++] = b.element[cb++];
	}
	//合并剩下的
	std::copy(a.element + ca, a.element + a.listSize, element + ct);
	ct += a.listSize - ca;
	std::copy(b.element + cb, b.element + b.listSize, element + ct);
	ct += b.listSize - cb;
	listSize = ct;
}

//将列表内的元素隔一个删除一个
template<class T>
void arrayList<T>::half()
{
	//将元素移动到新的位置
	for (int i = 2; i < listSize; i += 2)
		element[i / 2] = element[i];

	//销毁不需要的元素
	int newsize = (listSize + 1) / 2;
	for (int i = newsize; i < listSize; i++)
		element[i].~T();
	listSize = newsize;
}

//将列表内的元素左移theAmount位
template<class T>
void arrayList<T>::leftShift(int theAmount)
{
	//当移动值小于0时，不执行返回
	if (theAmount < 0)
		return;

	int newsize = 0;
	if (theAmount < listSize)
	{
		//列表移动后不会为空
		newsize = listSize - theAmount;
		std::copy(element + theAmount, element + listSize, element);
	}

	//删除不需要的元素
	for (int i = newsize; i < listSize; i++)
		element[i].~T();

	listSize = newsize;
}
//返回指定元素最后出现的位置
template<class T>
void arrayList<T>::lastIndexOf(const T& theElment)const
{
	for (int i = listSize - 1; i >= 0; i--)
	{
		if (element[i] == theElment)
			return i;
	}
	return -1;
}
//删除范围内的元素
template<class T>
void arrayList<T>::removeRange(int start, int end)
{
	if (start <0 || end >listSize)
		throw illegalIndex();
	if (start >= end)
		return;
	std::copy(element + end, element + listSize, element + start);
	int newsize = listSize - end + start;
	for (int i = newsize; i < listSize; i++)
		element[i].~T();
	listSize = newsize;
}
//清空列表
template<class T>
void arrayList<T>::clear()
{
	int initialCapacity;
	delete[] element;
	arrayLength = initialCapacity;
	element = new T[arrayLength];
	listSize = 0;
}

//设置指定索引的值
template<class T>
void arrayList<T>::set(int theIndex, const T& theElment)
{
	checkIndex(theIndex);
	element[theIndex] = theElment;
}

//交换两个列表
template<class T>
void arrayList<T>::myswap(arrayList<T>& thelist)
{
	std::swap(arrayLength, thelist.arrayLength);
	std::swap(listSize, thelist.listSize);
	std::swap(element, thelist.element);
}
//弹出最后面的元素
template<class T>
void arrayList<T>::pop_back()
{
	if (listSize == 0)
	{
		std::ostringstream s;
		s << "数组为空";
		throw illegalPamerterValue(s.str());
	}
	element[--listSize].~T();
}
//从后插入元素
template<class T>
void arrayList<T>::push_back(const T& theElment)
{
	//确保有空间
	if (listSize == arrayLength)
	{
		changeLength1D(element, arrayLength, arrayLength * 2);
		arrayLength *= 2;
	}
	element[listSize] = theElment;
	listSize++;
}
//重载 [] 操作符号
template<class T>
T& arrayList<T>::operator[](int theIndex)
{
	checkIndex(theIndex);
	return element[theIndex];
}

//重载!= 操作符号
template<class T>
bool arrayList<T>::operator!=(const arrayList<T>& thelist)const
{
	if (listSize != thelist.listSize)
		return true;
	//检查元素
	for (int i = 0; i < listSize; i++)
	{
		if (element[i] != thelist.element[i])
			return true;

		return false;
	}
}

//根据调整需求调整数组大小
template<class T>
void arrayList<T>::trimToSize()
{
	//当数组刚好满时不做处理
	if (arrayLength == listSize)
		return;

	//当数组为空时，将数组大小改为1
	if (listSize == 0)
	{
		delete[] element;
		element = new T[1];
		arrayLength = 1;
		return;
	}

	//将数组大小改为需要的大小
	changeLength1D(element, listSize, listSize);
	arrayLength = listSize;
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


