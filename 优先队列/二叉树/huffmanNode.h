#pragma once
#include"linkedBinaryTree.h"

//���������Ľṹ��
template<class T>
struct huffmanNode
{
	linkedBinaryTree<int>* tree;
	T weight;
	operator T()const { return weight; }

};