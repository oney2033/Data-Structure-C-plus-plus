#pragma once
#include"ChainNode.h"
#include"myexceptions.h"
#include"LinearLish.h"
#include<string>
#include<sstream>
template<class T>
class chain :public LinearLish<T>
{
public:
	//���캯���͸��ƹ��캯��
	chain(int initialCapacity = 10);
	chain(const chain<T>&);
	~chain();

	//ADT����
	bool empty()const { return listSize == 0; }
	int size()const { return listSize; }
	T& get(int theIndex)const;
	int indexOf(const T& theElment)const;
	void erase(int theIndex);
	void insert(int theIndex, const T& theElment);
	void output(std::ostream& out)const;
	void clear();
	void push_back(const T& theElment);

	//����ĵ�������ʼ����
	class iterator;
	iterator begin() { return iterator(firstNode); }
	iterator end() { return iterator(NULL); }

	class iterator
	{
	public:
		//typedef std::forward_iterator_tag  iterator_category;
		using  iterator_category = std::forward_iterator_tag;
	
		//typedef T value_type;
		using value_type = T;
	
		//typedef std::ptrdiff_t difference_type;
		using difference_type = std::ptrdiff_t;
	
		//typedef T* pointer;
		using pointer = T*;
	
		//typedef T& reference;
		using reference = T&;

		iterator(chainNode<T>* thenode = NULL)
		{
			node = thenode;
		}

		T& operator*()const { return node->element; }
		T* operator->()const { return &node->element; }

		iterator& operator++() { node = node->next; return *this; }
		iterator operator++(int)
		{
			iterator old = *this;
			node = node->next;
			return old;
		}

		bool operator!=(const iterator right)const
		{
			return node != right.node;
		}

		bool operator==(const iterator right)const
		{
			return node == right.node;
		}
	private:
		chainNode<T>* node;
	};
	//��������������

protected:
	//���������Ч���׳��쳣
	void checkIndex(int theIndex)const;

private:
	chainNode<T>* firstNode;
	int listSize;
};

//���캯����ʵ��
template<class T>
chain<T>::chain(int initialCapacity)
{
	if (initialCapacity < 1)
	{
		std::ostringstream s;
		s << "Initial capacity = " << initialCapacity << "must be > 0";
		throw illeagPamerterValue(s.str());
	}
	firstNode = NULL;
	listSize = 0;
}

//���ƹ��캯��
template<class T>
chain<T>::chain(const chain<T>& theList)
{
	listSize = theList.listSize;
	//����Ϊ��ֱ�ӷ���
	if (listSize == 0)
	{
		firstNode = NULL;
		return;
	}

	//����Ϊ�ս��и���
	chainNode<T>* sourceNode = theList.firstNode;

	firstNode = new chainNode<T>(sourceNode->element);
	sourceNode = sourceNode->next;

	chainNode<T>* targetNode = firstNode;
	while (sourceNode != NULL)
	{
		targetNode->next = new chainNode<T>(sourceNode->element);
		targetNode = targetNode->next;
		sourceNode = sourceNode->next;
	}
	targetNode->next = NULL;
}

//����������ɾ�������еĽ��
template<class T>
chain<T>::~chain()
{
	while (firstNode != NULL)
	{
		chainNode<T>* nextNode = firstNode->next;
		delete firstNode;
		firstNode = nextNode;
	}
}

//��������Ƿ���0��listsize-1֮��
template<class T>
void chain<T>::checkIndex(int theIndex)const
{
	if (theIndex < 0 || theIndex >= listSize)
	{
		std::stringstream s;
		s << "index = " << theIndex << "size = " << listSize;
		throw illegalIndex(s.str());
	}
}

//��ȡ�����и��±��Ԫ��
template<class T>
T& chain<T>::get(int theIndex)const
{
	checkIndex(theIndex);
	chainNode<T>* currentNode = firstNode;
	for (int i = 0; i < theIndex; i++)
	{
		currentNode = currentNode->next;
	}
	return currentNode->element;
}

//��ȡ�����е�һ�����ָ�Ԫ�ص��±�
template<class T>
int chain<T>::indexOf(const T& theElment)const
{
	chainNode<T>* currentNode = firstNode;
	int index = 0;
	while (currentNode != NULL && currentNode->element != theElment)
	{
		currentNode = currentNode->next;
		index++;
	}
	if (currentNode == NULL)
	{
		return -1;
	}
	else
		return index;
}

//�����ɾ������
template<class T>
void chain<T>::erase(int theIndex)
{
	checkIndex(theIndex);
	chainNode<T>* deleteNode;
	if (theIndex == 0)
	{
		deleteNode = firstNode;
		firstNode = firstNode->next;
	}
	else
	{
		chainNode<T>* p = firstNode;
		for (int i = 0; i < theIndex - 1; i++)
		{
			p = p->next;
		}

		deleteNode = p->next;
		p->next = p->next->next;
	}
	listSize--;
	delete deleteNode;
}

//������뺯��
template<class T>
void chain<T>::insert(int theIndex, const T& theElement)
{
	if (theIndex < 0 || theIndex > listSize)
	{
		std::ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw illegalIndex(s.str());
	}

	if (theIndex == 0)
	{
		firstNode = new chainNode<T>(theElement, firstNode);
	}
	else
	{
		chainNode<T>* p = firstNode;
		for (int i = 0; i < theIndex - 1; i++)
		{
			p = p->next;
		}
		p->next = new chainNode<T>(theElement, p->next);
	}
		listSize++;
}

template<class T>
void chain<T>::clear()
{
	while (firstNode != NULL)
	{
		chainNode<T>* nextNode = firstNode->next;
		delete firstNode;
		firstNode = nextNode;
	}
	listSize = 0;
}

template<class T>
void chain<T>::push_back(const T& theElment)
{
	chainNode<T>* newNode = new chainNode<T>(theElment, NULL);
	if (firstNode == NULL)
		firstNode = newNode;
	else
	{
		chainNode<T>* lastNode = firstNode;
		while (lastNode->next)
		{
			lastNode = lastNode->next;
		}
		lastNode->next = newNode;
	}
}

//������������
template<class T>
void chain<T>::output(std::ostream& out)const
{
	for (chainNode<T>* currentNode = firstNode; currentNode != NULL; currentNode = currentNode->next)
		out << currentNode->element << " ";
}
//����<<�������
template<class T>
std::ostream& operator<<(std::ostream& out, const chain<T>& x)
{
	x.output(out);
	return out;
}