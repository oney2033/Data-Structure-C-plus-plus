#pragma once
#include<iostream>
//�������ṹ�Ĳ��鼯����������
class unionFinWithTrees
{
public:
	void initialize(int numberOfElements)
	{//��ʼ��numberOfElements������ÿ����һ��Ԫ��
		parent = new int[numberOfElements + 1];
		for (int e = 1; e <= numberOfElements; e++)
		{
			parent[e] = 0;
		}
	}

	int find(int theElment)
	{//����Ԫ��theElment���ڵ�����
		while (parent[theElment] != 0)
		{
			theElment = parent[theElment];//�����ƶ�һ��
		}
		return theElment;
	}

	void unite(int rootA, int rootB)
	{//�ϲ����ø��ڵ㲻ͬ����(rootA��rootB)	
		parent[rootB] = rootA;
	}

private:
	int* parent;
};