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
	float cutOff;	//����ȷ������
	int level()const; //��������ļ���
	int levels;		//��ǰ���ķǿ�����
	int dSize;		//�ֵ�����Ը���
	int maxLevel;	//��������������
	K tailKey;		//���ؼ���

	skipNode<K, E>* search(const K&) const;//����������󿴵��Ľڵ�
	skipNode<K, E>* headerNode;		//ͷ�ڵ�ָ��
	skipNode<K, E>* tailNode;		//β�ڵ�
	skipNode<K, E>** last;			//last[i]��ʾi������ڵ�
};

template<class K,class E>
skipList<K, E>::skipList(K largeKey, int maxPairs, float prob)
{
	//���캯�����ؼ���С��largeKey�������Ը������ΪmaxPairs��0 < prob < 1
	cutOff = prob * RAND_MAX;
	maxLevel = (int)std::ceil(logf((float)maxPairs) / logf(1 / prob)) - 1;
	levels = 0;//��ʼ������
	dSize = 0;
	tailKey = largeKey;
	//����ͷ�ڵ㡢β�ڵ������last
	std::pair<K, E>tailPair;
	tailPair.first = tailKey;
	headerNode = new skipNode<K, E>(tailPair, maxLevel + 1);//ͷ�ڵ���n+1��ָ��β�ڵ��ָ��
	tailNode = new skipNode<K, E>(tailPair, 0);
	last = new skipNode<K, E>*[maxLevel + 1];
	//����Ϊ�գ����⼶�����е�ͷ�ڵ�ָ��β�ڵ�
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

//����ƥ������Ե�ָ��,���û�ҵ�����NULL
template<class K,class E>
std::pair<const K, E>* skipList<K, E>::find(const K& theKey)const
{
	if (theKey >= tailKey)
		return NULL;
	//λ��beforeNode�ǹؼ���ΪtheKey�Ľڵ�֮ǰ���ұߵ�λ��
	skipNode<K, E>* beforeNode = headerNode;
	for (int i = levels; i >= 0; i--)//���ϼ������¼�����
	{//׷��i������ָ��
		while (beforeNode->next[i]->element.first < theKey)
			beforeNode = beforeNode->next[i];
	}
	//�����һ���ڵ��Ƿ�ΪtheKey
	if (beforeNode->next[0]->element.first == theKey)
		return &beforeNode->next[0]->element;
	return NULL;
}

//����һ����ʾ��������������������������maxLevel
template<class K,class E>
int skipList<K, E>::level()const
{
	int	lev = 0;
	while (std::rand() <= cutOff)
		lev++;
	return (lev == maxLevel) ? lev : maxLevel;
}

//����������ÿһ����������ʱ�����������һ���ڵ�ָ��洢����
template<class K,class E>
skipNode<K, E>* skipList<K, E>::search(const K& theKey)const
{//�����ؼ���theKey����ÿһ����Ҫ�鿴�����һ���ڵ�洢��last��
//���عؼ���theKey�Ľڵ�
	//λ��beforeNode�ǹؼ���ΪtheKey�Ľڵ�֮ǰ���ұߵ�λ��
	skipNode<K, E>* beforeNode = headerNode;
	for (int i = levels; i >= 0; i--)
	{
		while (beforeNode->next[i]->element.first < theKey)
			beforeNode = beforeNode->next[i];
		last[i] = beforeNode;//���һ������i�Ľڵ�
	}
	return beforeNode->next[0];
}

//����,�����Ĺؼ���largeKey������������thepair�Ĺؼ���thepair.firstʱ����ִ�в���
template<class K,class E>
void skipList<K, E>::insert(const std::pair<const K, E>& thePair)
{
	if (thePair.first >= tailKey)
		__debugbreak;
	//�鿴�ؼ���ΪtheKey�������Ƿ��Ѿ�����
	skipNode<K, E>* thenode = search(thePair.first);
	if (thenode->element.first == thePair.first)
	{
		//������,����¸����Ե�ֵ
		thenode->element.second = thePair.second;
		return;
	}
	//�������ڣ���ȷ���½ڵ����ڵļ�����
	int theLevel = level();//�½ڵ�ļ�
	//ʹ��theLevel Ϊ <=levels +1
	if (theLevel > levels)
	{
		theLevel = ++levels;
		last[theLevel] = headerNode;
	}
	//�ڽڵ�thenode֮������½ڵ�
	skipNode<K, E>* newNode = new skipNode<K, E>(thePair, theLevel + 1);
	for (int i = 0; i <= theLevel; i++)
	{
		//����i������
		newNode->next[i] = last[i]->next[i];
		last[i]->next[i] = newNode;
	}
	dSize++;
	return;
}

//ɾ��
template<class K,class E>
void skipList<K, E>::erase(const K& theKey)
{
	//ɾ���ؼ��ֵ���theKey������
	if (theKey >= tailKey)
		return;

	//�鿴�Ƿ���ƥ�������
	skipNode<K, E>* theNode = search(theKey);
	if (theNode->element.first != theKey)
		return;
	//��������ɾ��
	for (int i = 0; i <= levels && last[i]->next[i] == theNode; i++)
		last[i]->next[i] = theNode->next[i];
	//��������
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