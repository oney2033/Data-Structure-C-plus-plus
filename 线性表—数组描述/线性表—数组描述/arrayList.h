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


	//�б�ʼ�ͽ����ĵ�����
	class iterator;
	iterator begin() { return iterator(element); }
	iterator end() { return iterator(element + listSize); }

	//arrayList�ĵ�����
	class iterator
	{
	public:
		// C++ ˫������������ typedef
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef T value_type;
		typedef std::ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T& reference;

		//���캯��
		iterator(T* thePosition = 0) { position = thePosition; }

		// �����������
		T& operator*()const { return *position; }
		T* operator->()const { return &*position; }

		// ����
		iterator& operator++() { ++position; return *this; }
		iterator operator++(int) { iterator old = *this; ++position; return old; }

		//�Լ�
		iterator& operator--() { --position; return *this; }
		iterator operator--(int) { iterator old = *this; --position; return old; }

		//�ж��Ƿ񲻵�
		bool operator!=(const iterator right) const
		{
			return position != right.position;
		}

		//�ж��Ƿ����
		bool operator==(const iterator right) const
		{
			return position == right.position;
		}
	protected:
		T* position;
	};//����������Ľ�β


	//����һЩ��ϰ�Ĵ���

	//�����ҷǵݼ�����ϲ���������
	void merge(const arrayList<T>& a, const arrayList<T>& b);

	//���б��ڵ�Ԫ�ظ�һ��ɾ��һ��
	void half();

	//���б��ڵ�Ԫ������ theAmountλ
	void leftShift(int theAmount);

	//����ָ��Ԫ�������ֵ�λ��
	void lastIndexOf(const T& theElment)const;

	//ɾ����Χ�ڵ�Ԫ��
	void removeRange(int start, int end);

	//����б�
	void clear();

	//����ָ��������ֵ
	void set(int theIndex, const T& theElment);

	//���������б�
	void myswap(arrayList<T>& thelist);

	//��������Ԫ��
	void pop_back();

	//�Ӻ����Ԫ��
	void push_back(const T& theElment);

	//����Ĵ�С����������е������Խ�ʡ�ռ�
	void trimToSize();

	//���� != ��������
	bool operator !=(const arrayList<T>& thelist)const;

	//���� [] ��������
	T& operator[](int);

	//�������������
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

//�����ҷǵݼ��ϲ���������
template<class T>
void arrayList<T>::merge(const arrayList<T>& a, const arrayList<T>& b)
{
	int ca, cb, ct = 0;//�α꣬����������������
	//��֤���㹻�Ŀռ�
	delete[]element;
	arrayLength = a.listSize + b.listSize;
	element = new T[arrayLength];
	//��ʼ�ϲ�
	while ((ca < a.listSize) && cb < b.listSize)
	{
		if (a.element[ca] <= b.element[cb])
			element[ct++] = a.element[ca++];
		else
			element[ct++] = b.element[cb++];
	}
	//�ϲ�ʣ�µ�
	std::copy(a.element + ca, a.element + a.listSize, element + ct);
	ct += a.listSize - ca;
	std::copy(b.element + cb, b.element + b.listSize, element + ct);
	ct += b.listSize - cb;
	listSize = ct;
}

//���б��ڵ�Ԫ�ظ�һ��ɾ��һ��
template<class T>
void arrayList<T>::half()
{
	//��Ԫ���ƶ����µ�λ��
	for (int i = 2; i < listSize; i += 2)
		element[i / 2] = element[i];

	//���ٲ���Ҫ��Ԫ��
	int newsize = (listSize + 1) / 2;
	for (int i = newsize; i < listSize; i++)
		element[i].~T();
	listSize = newsize;
}

//���б��ڵ�Ԫ������theAmountλ
template<class T>
void arrayList<T>::leftShift(int theAmount)
{
	//���ƶ�ֵС��0ʱ����ִ�з���
	if (theAmount < 0)
		return;

	int newsize = 0;
	if (theAmount < listSize)
	{
		//�б��ƶ��󲻻�Ϊ��
		newsize = listSize - theAmount;
		std::copy(element + theAmount, element + listSize, element);
	}

	//ɾ������Ҫ��Ԫ��
	for (int i = newsize; i < listSize; i++)
		element[i].~T();

	listSize = newsize;
}
//����ָ��Ԫ�������ֵ�λ��
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
//ɾ����Χ�ڵ�Ԫ��
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
//����б�
template<class T>
void arrayList<T>::clear()
{
	int initialCapacity;
	delete[] element;
	arrayLength = initialCapacity;
	element = new T[arrayLength];
	listSize = 0;
}

//����ָ��������ֵ
template<class T>
void arrayList<T>::set(int theIndex, const T& theElment)
{
	checkIndex(theIndex);
	element[theIndex] = theElment;
}

//���������б�
template<class T>
void arrayList<T>::myswap(arrayList<T>& thelist)
{
	std::swap(arrayLength, thelist.arrayLength);
	std::swap(listSize, thelist.listSize);
	std::swap(element, thelist.element);
}
//����������Ԫ��
template<class T>
void arrayList<T>::pop_back()
{
	if (listSize == 0)
	{
		std::ostringstream s;
		s << "����Ϊ��";
		throw illegalPamerterValue(s.str());
	}
	element[--listSize].~T();
}
//�Ӻ����Ԫ��
template<class T>
void arrayList<T>::push_back(const T& theElment)
{
	//ȷ���пռ�
	if (listSize == arrayLength)
	{
		changeLength1D(element, arrayLength, arrayLength * 2);
		arrayLength *= 2;
	}
	element[listSize] = theElment;
	listSize++;
}
//���� [] ��������
template<class T>
T& arrayList<T>::operator[](int theIndex)
{
	checkIndex(theIndex);
	return element[theIndex];
}

//����!= ��������
template<class T>
bool arrayList<T>::operator!=(const arrayList<T>& thelist)const
{
	if (listSize != thelist.listSize)
		return true;
	//���Ԫ��
	for (int i = 0; i < listSize; i++)
	{
		if (element[i] != thelist.element[i])
			return true;

		return false;
	}
}

//���ݵ���������������С
template<class T>
void arrayList<T>::trimToSize()
{
	//������պ���ʱ��������
	if (arrayLength == listSize)
		return;

	//������Ϊ��ʱ���������С��Ϊ1
	if (listSize == 0)
	{
		delete[] element;
		element = new T[1];
		arrayLength = 1;
		return;
	}

	//�������С��Ϊ��Ҫ�Ĵ�С
	changeLength1D(element, listSize, listSize);
	arrayLength = listSize;
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


