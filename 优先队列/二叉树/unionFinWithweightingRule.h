#pragma once
#include"unionFindNode.h"
class unionFinWithWeightingRule
{
public:
	void initialize(int numberOfElements)
	{//初始化numberOfElments棵树，每棵树包含一个元素
		node = new unionFinNode[numberOfElements];
	}

	int find(int theElement)
	{//返回元素theElement所在树的树根
	 //紧缩从元素theElement到根的树径
	 
		//theRoot最终是树的根
		int theRoot = theElement;
		while (!node[theRoot].root)
			theRoot = node[theRoot].parent;

		//紧缩从theElement到theRoot的路径
		int currentNode = theElement;
		while (currentNode != theRoot)
		{
			int parentNode = node[currentNode].parent;
			node[currentNode].parent = theRoot;//移动到二层
			currentNode = parentNode;
		}
		return theRoot;
	}

	void unite(int rootA, int rootB)
	{//利用重量规则，合并根不同的树(rootA和rootB)
		if (node[rootA].parent < node[rootB].parent)
		{//树rootA成为树rootB的子树
			node[rootB].parent += node[rootA].parent;
			node[rootA].root = false;
			node[rootA].parent = rootB;
		}
		else
		{//树rootB成为树rootA的子树
			node[rootA].parent += node[rootB].parent;
			node[rootB].root = false;
			node[rootB].parent = rootA;
		}
	}
private:
	unionFinNode* node;
};