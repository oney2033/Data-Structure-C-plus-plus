#pragma once
#include"maxPriorityQueue.h"
#include"linkedBinaryTree.h"
#include"binaryTreeNode.h"
#include"myExceptions.h"
#include<sstream>
#include<utility>
#include<queue>


//�߶����ȵ���������
template<class T>
class maxHblt : public maxPriorityQueue<T>, public linkedBinaryTree<std::pair<int, int>>
{
public:
	bool empty()const { return treeSize == 0; }
	int size()const { return treeSize; }
	const T& top()
	{//��������Ԫ��
		if (treeSize == 0)throw queempty();
		return root->element.second;
	}
	void pop();
	void push(const T&);
	void initialize(T*, int);
	void meld(maxHblt<T>& theHblt)
	{//�������*this �� theHblt�ϲ�
		meld(root, theHblt.root);
		treeSize += theHblt.treeSize;
		theHblt.root = NULL;
		theHblt.treeSize = 0;
	}
	void output() { postOrder(hbltOutput); std::cout << std::endl;}
private:
	void meld(binaryTreeNode<std::pair<int, T>>* &, binaryTreeNode<std::pair<int, T>>* &);
	static void hbltOutput(binaryTreeNode<std::pair<int, T> >* t)
	{
		std::cout << t->element.second << ' ';
	}
};

//���HBLT�ĳ�ʼ��
template<class T>
void maxHblt<T>::initialize(T* theElements, int theSize)
{
	//������theElments[1 : theSize]���������
	std::queue<binaryTreeNode<std::pair<int, T>>*>q;
	
	//��ʼ�����Ķ���
	for (int i = 1; i <= theSize; i++)
	{
		//����ֻ��һ���ڵ����
		q.push(new binaryTreeNode<std::pair<int, T>>(std::pair<int, T>(1, theElements[i])));
	}
	//�Ӷ������ظ�ȡ���������ϲ�
	for (int i = 1; i <= theSize - 1; i++)
	{
		binaryTreeNode<std::pair<int, T>>* b = q.front();
		q.pop();
		binaryTreeNode<std::pair<int, T>>* c = q.front();
		q.pop();
		meld(b, c);
		q.push(b);
	}
	if (theSize > 0)
		root = q.front();
	treeSize = theSize;
}


template<class T>
void maxHblt<T>::pop()
{
	//ɾ�����Ԫ��
	if (root == NULL)throw queempty();
	//������
	binaryTreeNode<std::pair<int, T>>* left = root->leftChild,* right = root->rightChild;
	delete root;
	root = left;
	meld(root, right);
	treeSize--;
}

template<class T>
void maxHblt<T>::push(const T& theElement)
{
	//��Ԫ��theElment���������
	//����ֻ��һ���ڵ�������
	binaryTreeNode<std::pair<int, T>>* q = new binaryTreeNode<std::pair<int, T>>(std::pair<int, T>(1, theElement));
	//�������q��ԭ���ϲ�
	meld(root, q);
	treeSize++;
}

template<class T>
void maxHblt<T>::meld(binaryTreeNode<std::pair<int, T>>*& x, binaryTreeNode<std::pair<int, T>>*& y)
{
	//�ϲ��ֱ��� *x �� *y Ϊ���������������
	//�ϲ����������� xΪ��������x��ָ��
	if (y == NULL)
		return; //yΪ��
	if (x == NULL)
	{
		x = y; return;	//xΪ��
	}

	// x �� y �����գ���Ҫʱ���� x �� y
	if (x->element.second < y->element.second)
		std::swap(x, y);

	meld(x->rightChild, y);
	//�����Ҫ������ x ��������Ȼ������x->element.first��ֵ
	if (x->leftChild == NULL)
	{
		//������Ϊ�գ���������
		x->leftChild = x->rightChild;
		x->rightChild = NULL;
		x->element.first = 1;
	}
	else
	{
		//ֻ����������sֵ��Сʱ�Ž���
		if (x->leftChild->element.first < x->rightChild->element.first)
			std::swap(x->leftChild, x->rightChild);
		//���� x ��sֵ
		x->element.first = x->rightChild->element.first + 1;
	}
}
