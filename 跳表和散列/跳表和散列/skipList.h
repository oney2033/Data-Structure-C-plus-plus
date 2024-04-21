#pragma once
#include"dictionary.h"
#include"skipNode.h"
#include<sstream>
#include<math.h>
#include<string>
#include<iostream>

template<class K, class E>
class skipList :public dictionary<K, E>
{
public:
	skipList(K, int maxPairs = 10000, float prob = 0.5);
	~skipList();
	bool empty()const { return dSize == 0; }
	int size()const { return dSize; }
	std::pair<const K, E>* find(const K&)const;
	void erase(const K&);
	void insert(const std::pair<const K, E>&);
	void output(std::ostream& out)const;

protected:
	float cutOff;	//用来确定层数
	int level()const; //生成随机的级数
	int levels;		//当前最大的非空链表
	int dSize;		//字典的数对个数
	int maxLevel;	//允许的最大链层数
	K tailKey;		//最大关键字

	skipNode<K, E>* search(const K&) const;//搜索保存最后看到的节点
	skipNode<K, E>* headerNode;		//头节点指针
	skipNode<K, E>* tailNode;		//尾节点
	skipNode<K, E>** last;			//last[i]表示i层的最后节点
};

template<class K,class E>
skipList<K, E>::skipList(K largeKey, int maxPairs, float prob)
{
	//构造函数，关键字小于largeKey，且数对个数最多为maxPairs，0 < prob < 1
	cutOff = prob * RAND_MAX;
	maxLevel = (int)std::ceil(logf((float)maxPairs) / logf(1 / prob)) - 1;
	levels = 0;//初始化级数
	dSize = 0;
	tailKey = largeKey;
	//生成头节点、尾节点和数组last
	std::pair<K, E>tailPair;
	tailPair.first = tailKey;
	headerNode = new skipNode<K, E>(tailPair, maxLevel + 1);//头节点有n+1个指向尾节点的指针
	tailNode = new skipNode<K, E>(tailPair, 0);
	last = new skipNode<K, E>*[maxLevel + 1];
	//链表为空，任意级链表中的头节点指向尾节点
	for (int i = 0; i <= maxLevel; i++)
		headerNode->next[i] = tailNode;
}

template<class K,class E>
skipList<K, E>::~skipList()
{
	skipNode<K, E>* nextNode;
	while (headerNode != tailNode)
	{
		nextNode = headerNode->next[0];
		delete headerNode;
		headerNode = nextNode;
	}
	delete tailNode;
	delete[] last;
}

//返回匹配的数对的指针,如果没找到返回NULL
template<class K,class E>
std::pair<const K, E>* skipList<K, E>::find(const K& theKey)const
{
	if (theKey >= tailKey)
		return NULL;
	//位置beforeNode是关键字为theKey的节点之前最右边的位置
	skipNode<K, E>* beforeNode = headerNode;
	for (int i = levels; i >= 0; i--)//从上级链表到下级链表
	{//追踪i级链表指针
		while (beforeNode->next[i]->element.first < theKey)
			beforeNode = beforeNode->next[i];
	}
	//检查下一个节点是否为theKey
	if (beforeNode->next[0]->element.first == theKey)
		return &beforeNode->next[0]->element;
	return NULL;
}

//返回一个表示链表级数的随机数，这个数不大于maxLevel
template<class K,class E>
int skipList<K, E>::level()const
{
	int	lev = 0;
	while (std::rand() <= cutOff)
		lev++;
	return (lev == maxLevel) ? lev : maxLevel;
}

//搜索并把在每一级链表搜索时所遇到的最后一个节点指针存储起来
template<class K,class E>
skipNode<K, E>* skipList<K, E>::search(const K& theKey)const
{//搜索关键字theKey，把每一级中要查看的最后一个节点存储在last中
//返回关键字theKey的节点
	//位置beforeNode是关键字为theKey的节点之前最右边的位置
	skipNode<K, E>* beforeNode = headerNode;
	for (int i = levels; i >= 0; i--)
	{
		while (beforeNode->next[i]->element.first < theKey)
			beforeNode = beforeNode->next[i];
		last[i] = beforeNode;//最后一级链表i的节点
	}
	return beforeNode->next[0];
}

//插入,当最大的关键字largeKey不大于新数对thepair的关键字thepair.first时，不执行插入
template<class K,class E>
void skipList<K, E>::insert(const std::pair<const K, E>& thePair)
{
	if (thePair.first >= tailKey)
		__debugbreak;
	//查看关键字为theKey的数对是否已经存在
	skipNode<K, E>* thenode = search(thePair.first);
	if (thenode->element.first == thePair.first)
	{
		//若存在,则更新该数对的值
		thenode->element.second = thePair.second;
		return;
	}
	//若不存在，则确定新节点所在的级链表
	int theLevel = level();//新节点的级
	//使级theLevel 为 <=levels +1
	if (theLevel > levels)
	{
		theLevel = ++levels;
		last[theLevel] = headerNode;
	}
	//在节点thenode之后插入新节点
	skipNode<K, E>* newNode = new skipNode<K, E>(thePair, theLevel + 1);
	for (int i = 0; i <= theLevel; i++)
	{
		//插入i级链表
		newNode->next[i] = last[i]->next[i];
		last[i]->next[i] = newNode;
	}
	dSize++;
	return;
}

//删除
template<class K,class E>
void skipList<K, E>::erase(const K& theKey)
{
	//删除关键字等于theKey的数对
	if (theKey >= tailKey)
		return;

	//查看是否有匹配的数对
	skipNode<K, E>* theNode = search(theKey);
	if (theNode->element.first != theKey)
		return;
	//从跳表中删除
	for (int i = 0; i <= levels && last[i]->next[i] == theNode; i++)
		last[i]->next[i] = theNode->next[i];
	//更新跳表
	while (levels > 0 && headerNode->next[levels] == tailNode)
		levels--;
	delete theNode;
	dSize--;
}

template<class K,class E>
void skipList<K, E>::output(std::ostream& out)const
{
	for (skipNode<K, E>*cur = headerNode->next[0]; cur != tailNode; cur = cur->next[0])
		out << cur->element.first << " " << cur->element.second << " ";
}

template<class K,class E>
std::ostream& operator<<(std::ostream& out, const skipList<K, E>& x)
{
	x.output(out);
	return out;
}