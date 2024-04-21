#pragma once
#include<iostream>
#include"dictionary.h"
#include"PairNode.h"

//按照关键字次序递增排列的数对,用链表描述
template<class K,class E>
class sortedChain :public dictionary<K, E>
{
public:
	sortedChain() { firstNode = NULL; dSize = 0; }
	~sortedChain();
	bool empty()const { return dSize == 0; }
	int size()const { return dSize; }
	std::pair<const K, E>* find(const K&)const;
	void erase(const K&);
	void insert(const std::pair<const K, E>&);
	void output(std::ostream& out)const;

protected:
	pairNode<K, E>* firstNode;//第一个节点的指针
	int dSize;//字典中元素的大小
};

//析构函数
template<class K,class E>
sortedChain<K, E>::~sortedChain()
{
	while (firstNode != NULL)
	{
		pairNode<K, E>* nextNode = firstNode->next;
		delete firstNode;
		firstNode = nextNode;
	}
}

//返回匹配的数对的指针
template<class K,class E>
std::pair<const K, E>* sortedChain<K, E>::find(const K& theKey)const
{
	//如果不存在匹配的数对，返回NULL
	pairNode<K, E>* cur = firstNode;
	while (cur != NULL && cur->element.first != theKey)
		cur = cur->next;
	//判断是否匹配
	if (cur != NULL && cur->element.first == theKey)
		return &cur->element;
	return NULL;
}

//往字典中插入thepair，覆盖已经存在的匹配的数对
template<class K,class E>
void sortedChain<K, E>::insert(const std::pair<const K, E>& thepair)
{
	pairNode<K, E>* p = firstNode, * tp = NULL; //tp = trails p
	//移动指针p，使thepair可以插在tp的后面,也就是p的前面
	while (p != NULL && p->element.first < thepair.first)
	{
		tp = p;
		p = p->next;
	}
	//检查是否有匹配的数对
	if (p != NULL && p->element.first == thepair.first)
	{
		//替换旧值
		p->element.second = thepair.second;
		return;
	}
	//无匹配的数对，为thepair建立新节点
	pairNode<K, E>* newNode = new pairNode<K, E>(thepair, p);
	//在tp之后插入新节点
	if (tp == NULL)firstNode = newNode;
	else tp->next = newNode;
	dSize++;
	return;
}

//删除关键字为thekey的数对
template<class K,class E>
void sortedChain<K, E>::erase(const K& theKey)
{
	pairNode<K, E>* p = firstNode, *tp = NULL;
	//搜索关键字为thekey的数对
	while (p != NULL && p->element.first < theKey)
	{
		tp = p;
		p = p->next;
	}
	//确定是否匹配
	if (p != NULL && p->element.first == theKey)
	{
		//找到一个匹配的数对
		if (tp == NULL)firstNode = p->next;//p是第一个节点
		else tp->next = p->next;
		delete p;
		dSize--;
	}
}

//输出函数
template<class K,class E>
void sortedChain<K, E>::output(std::ostream& out)const
{
	for (pairNode<K, E>* cur = firstNode; cur != NULL; cur = cur->next)
	{
		out << cur->element.first << " " << cur->element.second << " ";
	}
}

//重载<<运算符
template<class K,class E>
std::ostream& operator<<(std::ostream& out, const sortedChain<K, E>& x)
{
	x.output(out);
	return out;
}