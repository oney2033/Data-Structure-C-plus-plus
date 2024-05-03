#pragma once
//链表二叉树的节点结构

template<class T>
struct binaryTreeNode
{
	T element;
	binaryTreeNode<T>* leftChild, //左子树
					 * rightChild;//右子树
	binaryTreeNode() { leftChild = rightChild = nullptr; }
	binaryTreeNode(const T& theElment)
	{
		element = theElment;
		leftChild = rightChild = nullptr;
	}
	binaryTreeNode(const T& theElment, binaryTreeNode* theleftChile, binaryTreeNode* therightChile)
	{
		element = theElment;
		leftChild = theleftChile;
		rightChild = therightChile;
	}
};

