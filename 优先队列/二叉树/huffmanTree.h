#pragma once
#include"minHeap.h"
#include"linkedBinaryTree.h"
#include"huffmanNode.h"
#include<iostream>

//构造一棵霍夫曼树
template<class T>
linkedBinaryTree<int>* huffmanTree(T weight[], int n)
{//用权weight[1:n]生成霍夫曼树，n >= 1
	//创建一组单节点树
	huffmanNode<T>* hNode = new huffmanNode<T>[n + 1];
	linkedBinaryTree<int>emptyTree;
	for (int i = 1; i <= n; i++)
	{
		hNode[i].weight = weight[i];
		hNode[i].tree = new linkedBinaryTree<int>;
		hNode[i].tree->makeTree(i, emptyTree, emptyTree);
	}
	//使一组单节点构成小根堆
	minHeap<huffmanNode<T>>heap(1);
	heap.initial(hNode, n);

	//不断从小根堆提取两个树合并，直到剩下一颗树
	huffmanNode<T>w, x, y;
	linkedBinaryTree<int>* z;
	for (int i = 1; i < n; i++)
	{
		//从小根堆取出两颗最轻的树
		x = heap.top(); heap.pop();
		y = heap.top(); heap.pop();
		
		//合并成一棵树
		z = new linkedBinaryTree<int>;
		z->makeTree(0, *x.tree, *y.tree);
		w.weight = x.weight + y.weight;
		w.tree = z;
		heap.push(w);
		delete x.tree;
		delete y.tree;
	}
	return heap.top().tree;
}