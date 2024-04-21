#pragma once
#include<utility>
template<class K,class E>
struct skipNode
{
	using pairType = std::pair<const K, E>;
	pairType element;
	skipNode<K, E>** next;//next[i]表示i级链表指针
	skipNode(const pairType& thePair, int size)
		:element(thePair)
	{
		next = new skipNode<K, E>*[size];
	}
};