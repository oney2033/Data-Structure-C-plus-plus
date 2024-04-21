#pragma once
#include<utility>
template<class K,class E>
struct skipNode
{
	using pairType = std::pair<const K, E>;
	pairType element;
	skipNode<K, E>** next;//next[i]��ʾi������ָ��
	skipNode(const pairType& thePair, int size)
		:element(thePair)
	{
		next = new skipNode<K, E>*[size];
	}
};