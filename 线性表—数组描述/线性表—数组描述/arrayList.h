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
class arrayList :public LinearLish<T>  //arrayList�Ǵ�LinearListh������
{
public:
	//���캯�������ƹ��캯������������
	arrayList(int initialCapacity = 10);
	arrayList(const arrayList<T>&);
	~arrayList() { delete[] element; }

	//LinearList�ڵĳ����������͵ķ���
	bool empty()const { return listSize == 0; }
	int size()const { return listSize; }
	T& get(int theIndex)const;
	int indexOf(const T& theElement)const;
	void erase(int theIndex);
	void insert(int theIndex, const T& theElement);
	void output(std::ostream& out)const;

	//�����ķ���
	int capacity()const { return arrayLength; }

protected:
	void checkIndex(int theIndex)const;//���������Ч���׳��Ƿ�����
	T* element;		 //�����洢�б�Ԫ�ص�1ά����
	int arrayLength; //1ά���������
	int listSize;    //�б��е�Ԫ������
};


//���캯��
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

//���ƹ��캯��
template<class T>
arrayList<T>::arrayList(const arrayList<T>& thelist)
{
	arrayLength = thelist.arrayLength;
	listSize = thelist.listSize;
	element = new T[arrayLength];
	std::copy(thelist.element, thelist.element + thelist.listSize, element);
}

//��������Ƿ���0-listsize-1֮��
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

//��������ΪtheIndex��Ԫ�أ���������±겻�Ծ��׳��Ƿ������쳣
template<class T>
T& arrayList<T>::get(int theIndex)const
{
	checkIndex(theIndex);
	return element[theIndex];
}

//����theElment��һ�γ��ֵ����������û�ҵ��ͷ���-1
template<class T>
int arrayList<T>::indexOf(const T& theElement)const
{
	int index = (int)(std::find(element, element + listSize, theElement) - element);

	if (index == listSize)
		return -1;
	else return index;
}

//ɾ������ΪtheIndex��Ԫ��
template<class T>
void arrayList<T>::erase(int theIndex)
{
	checkIndex(theIndex);
	std::copy(element + theIndex + 1, element + listSize, element + theIndex);
	element[--listSize].~T();
}

//����Ԫ��theElment��ʹ������ΪtheIndex
template<class T>
void arrayList<T>::insert(int theIndex, const T& theElement)
{
	if (theIndex < 0 || theIndex > listSize)
	{
		std::ostringstream s;
		s << "index = " << theIndex << "size = " << listSize;
		throw illegalIndex(s.str());
	}

	//��Ч�����������ռ䲻��ʱ���ռ䷭��
	if (listSize == arrayLength)
	{
		changeLength1D(element, arrayLength, arrayLength * 2);
		arrayLength *= 2;
	}

	std::copy_backward(element + theIndex, element + listSize, element + listSize + 1);
	element[theIndex] = theElement;
	listSize++;
}

//���б�����������
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


