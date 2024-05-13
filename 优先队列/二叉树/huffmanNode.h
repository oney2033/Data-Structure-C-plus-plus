#pragma once
#include"linkedBinaryTree.h"

//霍夫曼树的结构体
template<class T>
struct huffmanNode
{
	linkedBinaryTree<int>* tree;
	T weight;
	operator T()const { return weight; }

};