#pragma once
#include<iostream>
#include"dictionary.h"
#include"PairNode.h"

//���չؼ��ִ���������е�����,����������
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
	pairNode<K, E>* firstNode;//��һ���ڵ��ָ��
	int dSize;//�ֵ���Ԫ�صĴ�С
};

//��������
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

//����ƥ������Ե�ָ��
template<class K,class E>
std::pair<const K, E>* sortedChain<K, E>::find(const K& theKey)const
{
	//���������ƥ������ԣ�����NULL
	pairNode<K, E>* cur = firstNode;
	while (cur != NULL && cur->element.first != theKey)
		cur = cur->next;
	//�ж��Ƿ�ƥ��
	if (cur != NULL && cur->element.first == theKey)
		return &cur->element;
	return NULL;
}

//���ֵ��в���thepair�������Ѿ����ڵ�ƥ�������
template<class K,class E>
void sortedChain<K, E>::insert(const std::pair<const K, E>& thepair)
{
	pairNode<K, E>* p = firstNode, * tp = NULL; //tp = trails p
	//�ƶ�ָ��p��ʹthepair���Բ���tp�ĺ���,Ҳ����p��ǰ��
	while (p != NULL && p->element.first < thepair.first)
	{
		tp = p;
		p = p->next;
	}
	//����Ƿ���ƥ�������
	if (p != NULL && p->element.first == thepair.first)
	{
		//�滻��ֵ
		p->element.second = thepair.second;
		return;
	}
	//��ƥ������ԣ�Ϊthepair�����½ڵ�
	pairNode<K, E>* newNode = new pairNode<K, E>(thepair, p);
	//��tp֮������½ڵ�
	if (tp == NULL)firstNode = newNode;
	else tp->next = newNode;
	dSize++;
	return;
}

//ɾ���ؼ���Ϊthekey������
template<class K,class E>
void sortedChain<K, E>::erase(const K& theKey)
{
	pairNode<K, E>* p = firstNode, *tp = NULL;
	//�����ؼ���Ϊthekey������
	while (p != NULL && p->element.first < theKey)
	{
		tp = p;
		p = p->next;
	}
	//ȷ���Ƿ�ƥ��
	if (p != NULL && p->element.first == theKey)
	{
		//�ҵ�һ��ƥ�������
		if (tp == NULL)firstNode = p->next;//p�ǵ�һ���ڵ�
		else tp->next = p->next;
		delete p;
		dSize--;
	}
}

//�������
template<class K,class E>
void sortedChain<K, E>::output(std::ostream& out)const
{
	for (pairNode<K, E>* cur = firstNode; cur != NULL; cur = cur->next)
	{
		out << cur->element.first << " " << cur->element.second << " ";
	}
}

//����<<�����
template<class K,class E>
std::ostream& operator<<(std::ostream& out, const sortedChain<K, E>& x)
{
	x.output(out);
	return out;
}