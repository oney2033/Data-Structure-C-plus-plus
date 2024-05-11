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
	E* rootElement()const;//���ظ��ڵ��Ԫ��
	linkedBinaryTree<E>& removeLeftSubtree();//ɾ��������������
	linkedBinaryTree<E>& removeRightSubtree();//ɾ��������������	
	void erase()//ɾ������
	{
		postOrder(dispose);
		root = NULL;
		treeSize = 0;
	}
	void preOrder(void(*theVisit)(binaryTreeNode<E>* ))//ǰ�����
	{
		visit = theVisit;preOrder(root);
	}
	void inOrder(void(*theVist)(binaryTreeNode<E>*))//�������
	{
		visit = theVist; inOrder(root);
	}
	void postOrder(void(*theVist)(binaryTreeNode<E>*))//�������
	{
		visit = theVist; postOrder(root);
	}
	void levelOrder(void(*)(binaryTreeNode<E>*));//�������



	void preOrderOutput() { preOrder(output); std::cout <<std::endl; }//���ǰ��������
	void inOrderOutput() { inOrder(output); std::cout << std::endl; }//�������������
	void postOrderOutput() { postOrder(output); std::cout << std::endl; }//�������������
	void levelOrderOutput() { levelOrder(output), std::cout << std::endl; }//�������������

protected:
	binaryTreeNode<E>* root; //���ڵ�
	int treeSize;			//���Ľڵ����
	static void(*visit)(binaryTreeNode<E>*);//visit����ָ��
	static int count;           //���ڶ������еĽڵ���м���
	static void preOrder(binaryTreeNode<E>* t);//ǰ�����
	static void inOrder(binaryTreeNode<E>* t);//�������
	static void postOrder(binaryTreeNode<E>* t);//�������
	static int height(binaryTreeNode<E>* t);//ȷ���������ĸ߶�
	static void countNoder(binaryTreeNode<E>* t)
	{
		visit = addTcount;
		count = 0;
		preOrder(t);
	}
	static void addTcount(binaryTreeNode<E>* t) { count++; }//���㺯��
	static void output(binaryTreeNode<E>* t) { std::cout << t->element << ' '; }//�������
	static void dispose(binaryTreeNode<E>* t) { delete t; }//ɾ������

};

//�������޷��Զ��Ƶ������ͣ��ֶ�����һ��
void (*linkedBinaryTree<int>::visit)(binaryTreeNode<int>*);
void (*linkedBinaryTree<booster>::visit)(binaryTreeNode<booster>*);
void (*linkedBinaryTree<std::pair<int, int> >::visit)(binaryTreeNode<std::pair<int, int> >*);
void (*linkedBinaryTree<std::pair< const int, char> >::visit)(binaryTreeNode<std::pair< const int, char> >*);
void (*linkedBinaryTree<std::pair< const int, int> >::visit)(binaryTreeNode<std::pair< const int, int> >*);

//ɾ��������������
template<class E>
linkedBinaryTree<E>& linkedBinaryTree<E>::removeLeftSubtree()
{
	if (treeSize == 0)
	{
		std::cout << "Tree is empty" << std::endl;
		return NULL;
	}
	//������������������leftSubtree��
	linkedBinaryTree<E>	leftSubtree;
	leftSubtree.root = root->leftChild;
	count = 0;
	leftSubtree.treeSize = countNoder(leftSubtree.root);
	root->leftChild = NULL;
	treeSize -= leftSubtree.treeSize;
	return leftSubtree;
}

//ɾ��������������
template<class E>
linkedBinaryTree<E>& linkedBinaryTree<E>::removeRightSubtree()
{
	if (!root)
	{
		std::cout << "Tree is empty" << std::endl;
		return NULL;
	}
	//����������,����������������rightSubtree��
	linkedBinaryTree<E> rightSubtree;
	rightSubtree.root = root->rightChild;
	count = 0;
	rightSubtree.treeSize = countNoder(rightSubtree.root);
	root->rightChild = NULL;
	treeSize -= rightSubtree.treeSize;
	return rightSubtree;
	
}
//���ظ��ڵ��Ԫ��
template<class E>
E* linkedBinaryTree<E>::rootElement()const
{
	if (!root)
		return NULL;
	else
		return &root->element;
}

//ȷ���������ĸ߶�
template<class E>
int linkedBinaryTree<E>::height(binaryTreeNode<E>* t)
{//���ظ�Ϊt�����ĸ߶�
	if (t == NULL)
		return 0;				  //����
	int hl = height(t->leftChild);//������
	int hr = height(t->rightChild);//������
	if (hl > hr)
		return ++hl;
	else
		return ++hr;
}

//������
template<class E>
void linkedBinaryTree<E>::makeTree(const E& element, linkedBinaryTree<E>& left, linkedBinaryTree<E>& right)
{
	root = new binaryTreeNode<E>(element, left.root, right.root);
	treeSize = left.treeSize + right.treeSize + 1;
	//�ܾ��������������ķ���
	left.root = right.root = nullptr;
	left.treeSize = right.treeSize = 0;
}

//ǰ�����
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

//�������
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

//�������
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

//�������
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
		//�õ���һ��Ҫ���ʵĽڵ�
		if (!q.empty())
		{
			t = q.front();
			q.pop();
		}
		else
			break;
	}
}
