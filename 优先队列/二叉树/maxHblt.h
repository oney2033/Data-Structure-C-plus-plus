#pragma once
#include"maxPriorityQueue.h"
#include"linkedBinaryTree.h"
#include"binaryTreeNode.h"
#include"myExceptions.h"
#include<sstream>
#include<utility>
#include<queue>


//高度优先的最大左高树
template<class T>
class maxHblt : public maxPriorityQueue<T>, public linkedBinaryTree<std::pair<int, int>>
{
public:
	bool empty()const { return treeSize == 0; }
	int size()const { return treeSize; }
	const T& top()
	{//返回最大的元素
		if (treeSize == 0)throw queempty();
		return root->element.second;
	}
	void pop();
	void push(const T&);
	void initialize(T*, int);
	void meld(maxHblt<T>& theHblt)
	{//把左高树*this 和 theHblt合并
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

//最大HBLT的初始化
template<class T>
void maxHblt<T>::initialize(T* theElements, int theSize)
{
	//用数组theElments[1 : theSize]建立左高树
	std::queue<binaryTreeNode<std::pair<int, T>>*>q;
	
	//初始化树的队列
	for (int i = 1; i <= theSize; i++)
	{
		//建立只有一个节点的树
		q.push(new binaryTreeNode<std::pair<int, T>>(std::pair<int, T>(1, theElements[i])));
	}
	//从队列中重复取出两颗树合并
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
	//删除最大元素
	if (root == NULL)throw queempty();
	//树不空
	binaryTreeNode<std::pair<int, T>>* left = root->leftChild,* right = root->rightChild;
	delete root;
	root = left;
	meld(root, right);
	treeSize--;
}

template<class T>
void maxHblt<T>::push(const T& theElement)
{
	//把元素theElment插入左高树
	//建立只有一个节点的左高树
	binaryTreeNode<std::pair<int, T>>* q = new binaryTreeNode<std::pair<int, T>>(std::pair<int, T>(1, theElement));
	//将左高树q和原树合并
	meld(root, q);
	treeSize++;
}

template<class T>
void maxHblt<T>::meld(binaryTreeNode<std::pair<int, T>>*& x, binaryTreeNode<std::pair<int, T>>*& y)
{
	//合并分别以 *x 和 *y 为根的两个棵左高树
	//合并后的左高树以 x为根，返回x的指针
	if (y == NULL)
		return; //y为空
	if (x == NULL)
	{
		x = y; return;	//x为空
	}

	// x 和 y 都不空，必要时交换 x 和 y
	if (x->element.second < y->element.second)
		std::swap(x, y);

	meld(x->rightChild, y);
	//如果需要，交换 x 的子树，然后设置x->element.first的值
	if (x->leftChild == NULL)
	{
		//左子树为空，交换子树
		x->leftChild = x->rightChild;
		x->rightChild = NULL;
		x->element.first = 1;
	}
	else
	{
		//只有左子树的s值较小时才交换
		if (x->leftChild->element.first < x->rightChild->element.first)
			std::swap(x->leftChild, x->rightChild);
		//更新 x 的s值
		x->element.first = x->rightChild->element.first + 1;
	}
}
