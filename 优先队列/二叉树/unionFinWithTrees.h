#pragma once
#include<iostream>
//基于树结构的并查集问题解决方案
class unionFinWithTrees
{
public:
	void initialize(int numberOfElements)
	{//初始化numberOfElements棵树，每颗树一个元素
		parent = new int[numberOfElements + 1];
		for (int e = 1; e <= numberOfElements; e++)
		{
			parent[e] = 0;
		}
	}

	int find(int theElment)
	{//返回元素theElment所在的树根
		while (parent[theElment] != 0)
		{
			theElment = parent[theElment];//向上移动一层
		}
		return theElment;
	}

	void unite(int rootA, int rootB)
	{//合并两棵根节点不同的树(rootA和rootB)	
		parent[rootB] = rootA;
	}

private:
	int* parent;
};