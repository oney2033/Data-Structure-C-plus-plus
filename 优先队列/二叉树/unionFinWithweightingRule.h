#pragma once
#include"unionFindNode.h"
class unionFinWithWeightingRule
{
public:
	void initialize(int numberOfElements)
	{//��ʼ��numberOfElments������ÿ��������һ��Ԫ��
		node = new unionFinNode[numberOfElements];
	}

	int find(int theElement)
	{//����Ԫ��theElement������������
	 //������Ԫ��theElement����������
	 
		//theRoot���������ĸ�
		int theRoot = theElement;
		while (!node[theRoot].root)
			theRoot = node[theRoot].parent;

		//������theElement��theRoot��·��
		int currentNode = theElement;
		while (currentNode != theRoot)
		{
			int parentNode = node[currentNode].parent;
			node[currentNode].parent = theRoot;//�ƶ�������
			currentNode = parentNode;
		}
		return theRoot;
	}

	void unite(int rootA, int rootB)
	{//�����������򣬺ϲ�����ͬ����(rootA��rootB)
		if (node[rootA].parent < node[rootB].parent)
		{//��rootA��Ϊ��rootB������
			node[rootB].parent += node[rootA].parent;
			node[rootA].root = false;
			node[rootA].parent = rootB;
		}
		else
		{//��rootB��Ϊ��rootA������
			node[rootA].parent += node[rootB].parent;
			node[rootB].root = false;
			node[rootB].parent = rootA;
		}
	}
private:
	unionFinNode* node;
};