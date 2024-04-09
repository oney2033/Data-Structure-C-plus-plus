#pragma once
#include<iostream>
#include"myExceptions.h"
#include"changeLength1D.h"
#include<sstream>
#include<iterator>
template<class T>
class arrayLish
{
public:
	arrayLish(int initialCapacity = 10);
	arrayLish(const arrayLish<T>&);
	~arrayLish() { delete[] element; }
	bool empty() { return listsize == 0; }
	int size() { return listsize; }
	int indexOf(const T& theElement)const;
	T& get(int index)const;
	void erase(int index);
	void insert(int index, const T& theElement);
	void output(std::ostream& out)const;
	int capacity()const { return arraylength; }
	void reSet(int);//�޸������ڵ�Ԫ�ظ�������Ҫ��������������
	void set(int, const T&);//����ָ��������Ԫ��ֵ
	void clear() { listsize = 0; }//���б����Ԫ�صĸ�������Ϊ0

	//���������
	class iterator;
	iterator begin() { return iterator(element); }
	iterator end() { return iterator(element + listsize); }

	class iterator
	{
	public:
		//using value_type = T;
		//using pointer = T*;
		//using reference = T&;

		typedef std::bidirectional_iterator_tag iterator_category;
		typedef T value_type;
		typedef std::ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T& reference;

		iterator(T* thePosition = 0) { position = thePosition; }

		//���ǽ����ò����������غ����������ص�������ǰλ�� position ��ָ���Ԫ�ص����á�
		//ͨ��������أ������ͨ����������������ָ���Ԫ�ء�
		T& operator*()const { return *position; }

		//��������غ����У�����ͨ�� *position �����õ������ĵ�ǰλ�ã�Ȼ��ͨ��ȡַ������ & ����ָ��ý�����Ԫ�ص�ָ�롣
		//��������Ŀ����������ͨ��������ʹ�ü�ͷ���������������һ��ָ������ָ��һ��
		T* operator->()const { return &*position; }

		//����,��ָ��position�ƶ�����һ��λ�ã�thisָ��ָ����һ��iterator�Ķ���Ȼ����*�Ž����õĵ������󷵻�
		iterator& operator++() { ++position; return *this; }
		iterator operator++(int) { iterator old = *this; ++position; return old; }

		//�Լ�����ָ��position�ƶ�����һ��λ�ã�thisָ��ָ����һ��iterator�Ķ���Ȼ����*�Ž����õĵ������󷵻�
		iterator& operator--() { --position; return *this; }
		iterator operator--(int) { iterator old = *this; --position; return old; }

		bool operator!=(const iterator right)const
		{
			return position != right.position;
		}

		bool operator==(const iterator right) const
		{
			return position == right.position;
		}

	protected:
		T* position;
	};
	//�������Ľ�β
private:
	void checkIndex(int Index)const;
	T* element;
	int arraylength;
	int listsize;
};

template<class T>
T& arrayLish<T>::get(int index)const
{
	checkIndex(index);
	return element[index];
}

template<class T>
void arrayLish<T>::set(int index, const T& newValue)
{
	checkIndex(index);
	element[index] = newValue;
}

template<class T>
void arrayLish<T>::reSet(int thesize)
{
	if (thesize < 0)
	{
		std::ostringstream s;
		s << "Requested size = " << thesize << " Must be >= 0";
		throw illeagParameterVaule(s.str());
	}
	if (thesize > arraylength)
	{
		delete element;
		element = new T[thesize];
		arraylength = listsize;
	}
	listsize = thesize;
}

template<class T>
std::ostream& operator<<(std::ostream& out, const arrayLish<T>& x)
{
	x.output(out);
	return out;
}

template<class T>
void arrayLish<T>::output(std::ostream& out)const
{
	std::copy(element, element + listsize, std::ostream_iterator<T>(std::cout, " "));
}

template<class T>
void arrayLish<T>::insert(int index, const T& theElement)
{
	if (index <0 || index>listsize)
	{
		std::ostringstream s;
		s << "index = " << index << "size = " << listsize;
		throw illeaglIndex(s.str());
	}
	if (listsize == arraylength)
	{
		changeLength1D(element, arraylength, 2 * arraylength);
		arraylength *= 2;
	}
	std::copy_backward(element + index, element + listsize, element + listsize + 1);
	element[index] = theElement;
	listsize++;
}

template<class T>
void arrayLish<T>::erase(int index)
{
	checkIndex(index);
	std::copy(element + index + 1, element + listsize, element + index);
	element[--listsize].~T();
}

template<class T>
int arrayLish<T>::indexOf(const T& theElement)const
{
	int index = (int)(std::find(element, element + listsize, theElement) - element);
	if (index == listsize)
		return -1;
	else
		return index;
}

template<class T>
arrayLish<T>::arrayLish(int initialCapacity)
{
	if (initialCapacity < 1)
	{
		std::ostringstream s;
		s << "initial capacity = " << initialCapacity << "must be > 0";
		throw illeagParameterVaule(s.str());
	}
	arraylength = initialCapacity;
	element = new T[arraylength];
	listsize = 0;
}

template<class T>
arrayLish<T>::arrayLish(const arrayLish<T>& thelist)
{
	arraylength = thelist.arraylength();
	listsize = thelist.listsize;
	element = new T[arraylength];
	std::copy(thelist, thelist + thelist.arraylength, element);
}

template<class T>
void arrayLish<T>::checkIndex(int Index)const
{
	if (Index < 0 || Index >=listsize)
	{
		std::ostringstream s;
		s << "index = " << Index << "size = " << listsize;
		throw illeaglIndex(s.str());
	}
}