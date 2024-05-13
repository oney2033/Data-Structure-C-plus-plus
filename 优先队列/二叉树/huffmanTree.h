#pragma once
#include"minHeap.h"
#include"linkedBinaryTree.h"
#include"huffmanNode.h"
#include<iostream>

//����һ�û�������
template<class T>
linkedBinaryTree<int>* huffmanTree(T weight[], int n)
{//��Ȩweight[1:n]���ɻ���������n >= 1
	//����һ�鵥�ڵ���
	huffmanNode<T>* hNode = new huffmanNode<T>[n + 1];
	linkedBinaryTree<int>emptyTree;
	for (int i = 1; i <= n; i++)
	{
		hNode[i].weight = weight[i];
		hNode[i].tree = new linkedBinaryTree<int>;
		hNode[i].tree->makeTree(i, emptyTree, emptyTree);
	}
	//ʹһ�鵥�ڵ㹹��С����
	minHeap<huffmanNode<T>>heap(1);
	heap.initial(hNode, n);

	//���ϴ�С������ȡ�������ϲ���ֱ��ʣ��һ����
	huffmanNode<T>w, x, y;
	linkedBinaryTree<int>* z;
	for (int i = 1; i < n; i++)
	{
		//��С����ȡ�������������
		x = heap.top(); heap.pop();
		y = heap.top(); heap.pop();
		
		//�ϲ���һ����
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