#pragma once
#include<utility>
template<class K,class E>
struct pairNode
{
	using pairType = std::pair<const K, E>;
	pairType element;
	pairNode<K, E>* next;
	pairNode(const pairType& thePair):element(thePair){}
	pairNode(const pairType& thePair,pairNode<K,E>*thenext)
		:element(thePair),next(thenext){}
	
}; 