#pragma once
#include<iostream>
#include"linkedBinaryTree.h"
//设置信号放大器的结构
int tolerance = 3;

struct booster
{
	int degradeToleaf,	//到达叶子时的衰减量
		degradeFromParent;//从父节点出发的衰减量
	bool boosterHere;	  //当设置了放大器时，值为真

	void output(std::ostream& out)const
	{
		out << boosterHere << ' ' << degradeToleaf << ' ' << degradeFromParent << ' ';
	}
};
//重载操作符号<<
std::ostream& operator<<(std::ostream& out, booster x)
{
	x.output(out);
	return out;
}

//在二叉树中放置放大器并计算degradeToLeaf值
void placeBoosters(binaryTreeNode<booster>* x)
{
	//计算 *x 的衰减量，若小于容忍值，则在x的子节点放置一个放大器
	x->element.degradeToleaf = 0;//初始化x处的衰减

	//计算x的左子树的衰减量,若大于容忍值，则在x的左孩子处放置一个放大器
	binaryTreeNode<booster>* y = x->leftChild;
	if (y != NULL)
	{//x有一颗非空左子树
		int degradation = y->element.degradeToleaf + y->element.degradeFromParent;
		if (degradation > tolerance)
		{//在y处放置一个放大器
			y->element.boosterHere = true;
			x->element.degradeToleaf = y->element.degradeFromParent;
		}
		else
		{//不需要在y处放置放大器
			x->element.degradeToleaf = degradation;
		}
	}

	//计算x的右子树的衰减量,若大于容忍值,则在x的右孩子处放置一个放大器
	y = x->rightChild;
	if (y != NULL)
	{
		int degradation = y->element.degradeToleaf + y->element.degradeFromParent;
		if (degradation > tolerance)
		{//在y处放置一个放大器
			y->element.boosterHere = true;
			degradation = y->element.degradeFromParent;
		}
		if (x->element.degradeToleaf < degradation)
			x->element.degradeToleaf = degradation;
	}
}
