#pragma once
#include<iostream>
#include"linkedBinaryTree.h"
//�����źŷŴ����Ľṹ
int tolerance = 3;

struct booster
{
	int degradeToleaf,	//����Ҷ��ʱ��˥����
		degradeFromParent;//�Ӹ��ڵ������˥����
	bool boosterHere;	  //�������˷Ŵ���ʱ��ֵΪ��

	void output(std::ostream& out)const
	{
		out << boosterHere << ' ' << degradeToleaf << ' ' << degradeFromParent << ' ';
	}
};
//���ز�������<<
std::ostream& operator<<(std::ostream& out, booster x)
{
	x.output(out);
	return out;
}

//�ڶ������з��÷Ŵ���������degradeToLeafֵ
void placeBoosters(binaryTreeNode<booster>* x)
{
	//���� *x ��˥��������С������ֵ������x���ӽڵ����һ���Ŵ���
	x->element.degradeToleaf = 0;//��ʼ��x����˥��

	//����x����������˥����,����������ֵ������x�����Ӵ�����һ���Ŵ���
	binaryTreeNode<booster>* y = x->leftChild;
	if (y != NULL)
	{//x��һ�ŷǿ�������
		int degradation = y->element.degradeToleaf + y->element.degradeFromParent;
		if (degradation > tolerance)
		{//��y������һ���Ŵ���
			y->element.boosterHere = true;
			x->element.degradeToleaf = y->element.degradeFromParent;
		}
		else
		{//����Ҫ��y�����÷Ŵ���
			x->element.degradeToleaf = degradation;
		}
	}

	//����x����������˥����,����������ֵ,����x���Һ��Ӵ�����һ���Ŵ���
	y = x->rightChild;
	if (y != NULL)
	{
		int degradation = y->element.degradeToleaf + y->element.degradeFromParent;
		if (degradation > tolerance)
		{//��y������һ���Ŵ���
			y->element.boosterHere = true;
			degradation = y->element.degradeFromParent;
		}
		if (x->element.degradeToleaf < degradation)
			x->element.degradeToleaf = degradation;
	}
}
