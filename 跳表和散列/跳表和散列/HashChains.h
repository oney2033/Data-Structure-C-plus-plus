#pragma once
#include<iostream>
#include"Hash.h"
#include"dictionary.h"
#include"sortedChain.h"
#include"utility"

//ɢ�б���ʽ��ʾ
template<class K,class E>
class hashChains :public dictionary<K,E>
{
public:
	hashChains(int theDivisor = 11)
	{
		divisor = theDivisor;
		dSize = 0;
		table = new sortedChain<K, E>[divisor];
	}

	~hashChains() { delete[] table; }

	bool empty()const { return dSize == 0; }
	int size()const { return dSize; }
	
	std::pair<const K, E>* find(const K& theKey)const
	{
		return table[hash(theKey) % divisor].find(theKey);
	}
	
	void erase(const K& theKey)
	{
		table[hash(theKey) % divisor].erase(theKey);
	}

	void insert(const std::pair<const K, E>& thePair)
	{
		int homeBucket = (int)hash(thePair.first) % divisor;
		int homeSize = table[homeBucket].size();
		table[homeBucket].insert(thePair);
		if (table[homeBucket].size() > homeSize)
			dSize++;
	}

	void output(std::ostream& out)const
	{
		for (int i = 0; i < divisor; i++)
		{
			if (table[i].size() == 0)
				std::cout << "NULL" << std::endl;
			else
				std::cout << table[i] << std::endl;
		}
	}

protected:
	sortedChain<K, E>* table; // ɢ�б�
	hash<K> hash;        //������Kӳ�䵽�Ǹ�����
	int dSize;          //�б��е�Ԫ������
	int divisor;       //ɢ�к�������
};

template<class K,class E>
std::ostream& operator<<(std::ostream& out, const hashChains<K, E>& x)
{
	x.output(out);
	return out;
}