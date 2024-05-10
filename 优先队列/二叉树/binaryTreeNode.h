#pragma once
//����������Ľڵ�ṹ

template<class T>
struct binaryTreeNode
{
	T element;
	binaryTreeNode<T>* leftChild, //������
					 * rightChild;//������
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

