#pragma once
#include"binaryTreeNode.h"
#include"binaryTree.h"
#include<iostream>
#include<queue>
#include"booster.h"
#include"binaryTree.h"

template<class E>
class linkedBinaryTree : public binaryTree<binaryTreeNode<E>>
{
public:
	linkedBinaryTree() { root = NULL; treeSize = 0; }
	~linkedBinaryTree() { erase(); }
	bool empty()const { return treeSize == 0; }
	int size()const { return treeSize; }
	int height()const { return height(root); }
	void makeTree(const E& element, linkedBinaryTree<E>&, linkedBinaryTree<E>&);
	E* rootElement()const;//返回根节点的元素
	linkedBinaryTree<E>& removeLeftSubtree();//删除并返回左子树
	linkedBinaryTree<E>& removeRightSubtree();//删除并返回右子树	
	void erase()//删除函数
	{
		postOrder(dispose);
		root = NULL;
		treeSize = 0;
	}
	void preOrder(void(*theVisit)(binaryTreeNode<E>* ))//前序遍历
	{
		visit = theVisit;preOrder(root);
	}
	void inOrder(void(*theVist)(binaryTreeNode<E>*))//中序遍历
	{
		visit = theVist; inOrder(root);
	}
	void postOrder(void(*theVist)(binaryTreeNode<E>*))//后序遍历
	{
		visit = theVist; postOrder(root);
	}
	void levelOrder(void(*)(binaryTreeNode<E>*));//层序遍历



	void preOrderOutput() { preOrder(output); std::cout <<std::endl; }//输出前序遍历结果
	void inOrderOutput() { inOrder(output); std::cout << std::endl; }//输出中序遍历结果
	void postOrderOutput() { postOrder(output); std::cout << std::endl; }//输出后序遍历结果
	void levelOrderOutput() { levelOrder(output), std::cout << std::endl; }//输出层序遍历结果

protected:
	binaryTreeNode<E>* root; //根节点
	int treeSize;			//树的节点个数
	static void(*visit)(binaryTreeNode<E>*);//visit函数指针
	static int count;           //用于对子树中的节点进行计数
	static void preOrder(binaryTreeNode<E>* t);//前序遍历
	static void inOrder(binaryTreeNode<E>* t);//中序遍历
	static void postOrder(binaryTreeNode<E>* t);//后序遍历
	static int height(binaryTreeNode<E>* t);//确定二叉树的高度
	static void countNoder(binaryTreeNode<E>* t)
	{
		visit = addTcount;
		count = 0;
		preOrder(t);
	}
	static void addTcount(binaryTreeNode<E>* t) { count++; }//计算函数
	static void output(binaryTreeNode<E>* t) { std::cout << t->element << ' '; }//输出函数
	static void dispose(binaryTreeNode<E>* t) { delete t; }//删除函数

};

//编译器无法自动推导出类型，手动定义一下
void (*linkedBinaryTree<int>::visit)(binaryTreeNode<int>*);
void (*linkedBinaryTree<booster>::visit)(binaryTreeNode<booster>*);
void (*linkedBinaryTree<std::pair<int, int> >::visit)(binaryTreeNode<std::pair<int, int> >*);
void (*linkedBinaryTree<std::pair< const int, char> >::visit)(binaryTreeNode<std::pair< const int, char> >*);
void (*linkedBinaryTree<std::pair< const int, int> >::visit)(binaryTreeNode<std::pair< const int, int> >*);

//删除并返回左子树
template<class E>
linkedBinaryTree<E>& linkedBinaryTree<E>::removeLeftSubtree()
{
	if (treeSize == 0)
	{
		std::cout << "Tree is empty" << std::endl;
		return NULL;
	}
	//分离左子树并保存在leftSubtree中
	linkedBinaryTree<E>	leftSubtree;
	leftSubtree.root = root->leftChild;
	count = 0;
	leftSubtree.treeSize = countNoder(leftSubtree.root);
	root->leftChild = NULL;
	treeSize -= leftSubtree.treeSize;
	return leftSubtree;
}

//删除并返回右子树
template<class E>
linkedBinaryTree<E>& linkedBinaryTree<E>::removeRightSubtree()
{
	if (!root)
	{
		std::cout << "Tree is empty" << std::endl;
		return NULL;
	}
	//分离右子树,并将右子树保存在rightSubtree中
	linkedBinaryTree<E> rightSubtree;
	rightSubtree.root = root->rightChild;
	count = 0;
	rightSubtree.treeSize = countNoder(rightSubtree.root);
	root->rightChild = NULL;
	treeSize -= rightSubtree.treeSize;
	return rightSubtree;
	
}
//返回根节点的元素
template<class E>
E* linkedBinaryTree<E>::rootElement()const
{
	if (!root)
		return NULL;
	else
		return &root->element;
}

//确定二叉树的高度
template<class E>
int linkedBinaryTree<E>::height(binaryTreeNode<E>* t)
{//返回根为t的树的高度
	if (t == NULL)
		return 0;				  //空树
	int hl = height(t->leftChild);//左树高
	int hr = height(t->rightChild);//右树高
	if (hl > hr)
		return ++hl;
	else
		return ++hr;
}

//创建树
template<class E>
void linkedBinaryTree<E>::makeTree(const E& element, linkedBinaryTree<E>& left, linkedBinaryTree<E>& right)
{
	root = new binaryTreeNode<E>(element, left.root, right.root);
	treeSize = left.treeSize + right.treeSize + 1;
	//拒绝来自左右子树的访问
	left.root = right.root = nullptr;
	left.treeSize = right.treeSize = 0;
}

//前序遍历
template<class E>
void linkedBinaryTree<E>::preOrder(binaryTreeNode<E>* t)
{
	if (t != NULL)
	{
		linkedBinaryTree<E>::visit(t);
		preOrder(t->leftChild);
		preOrder(t->rightChild);
	}
}

//中序遍历
template<class E>
void linkedBinaryTree<E>::inOrder(binaryTreeNode<E>* t)
{
	if (t != NULL)
	{
		inOrder(t->leftChild);
		linkedBinaryTree<E>::visit(t);
		inOrder(t->rightChild);
	}
}

//后序遍历
template<class E>
void linkedBinaryTree<E>::postOrder(binaryTreeNode<E>* t)
{
	if (t != NULL)
	{
		postOrder(t->leftChild);
		postOrder(t->rightChild);
		linkedBinaryTree<E>::visit(t);
	}
}

//层序遍历
template<class E>
void linkedBinaryTree<E>::levelOrder(void(*theVisit)(binaryTreeNode<E>*))
{
	std::queue<binaryTreeNode<E>*>q;
	binaryTreeNode<E>* t = root;
	while (t != NULL)
	{
		theVisit(t);
		if (t->leftChild != NULL)
			q.push(t->leftChild);
		if (t->rightChild != NULL)
			q.push(t->rightChild);
		//得到下一个要访问的节点
		if (!q.empty())
		{
			t = q.front();
			q.pop();
		}
		else
			break;
	}
}
