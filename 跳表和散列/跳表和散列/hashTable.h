#pragma once
#include"Hash.h"
#include<utility>
#include<sstream>

//散列表，线性探测表示
template<class K,class E>
class hashTable
{
public:
	hashTable(int theDivisor = 11);
	~hashTable() { delete[]table; }

	bool empty()const { return dSize == 0; }
	int size()const { return dSize; }
	std::pair<const K, E>* find(const K&)const;
	void insert(const std::pair<const K, E>&);
	void output(std::ostream& out)const;

private:
	//散列表的数据成员
	int search(const K&)const;
	std::pair<const K, E>** table;   //散列表
	hash<K> hash;		//把类型K映射到一个非整数
	int dSize;          //字典中数对个数
	int divisor;        //散列函数除数
};

//构造函数
template<class K,class E>
hashTable<K, E>::hashTable(int theDivisor)
{
	divisor = theDivisor;
	dSize = 0;
	//分配和初始化散列数组
	table = new std::pair<const K, E>*[divisor];
	for (int i = 0; i < divisor; i++)
		table[i] = NULL;
}

//搜索函数,有匹配的数对则返回它的位置，否则，如果散列表不满，则返回关键字为theKey的数对可以插入的位置
template<class K,class E>
int hashTable<K, E>::search(const K& theKey)const
{
	int i = hash(theKey) % divisor;//起始桶
	int j = i;
	do
	{
		if (table[j] == NULL || table[j]->first == theKey)
		{
			return j;
		}
		j = (i + 1) % divisor;		//下一个桶
	} while (j != i);

	return j;		//表满
}

//查找函数,返回匹配数对的指针，不存在则返回NULL
template<class K,class E>
std::pair<const K, E>* hashTable<K, E>::find(const K& theKey)const
{
	//搜索散列表
	int b = search(theKey);
	
	//判断table[b]是否是匹配数对
	if (table[b] == NULL || table[b]->first != theKey)
		return NULL;	//没有找到
	return table[b];//找到
	
}

//插入函数
template<class K,class E>
void hashTable<K, E>::insert(const std::pair<const K, E>& thePair)
{
	int b = search(thePair.first);

	//查找匹配的数对是否存在
	if (table[b] == NULL)
	{
		//没有匹配的数对，而且表不满
		table[b] = new std::pair<const K, E>(thePair);
		dSize++;
	}
	else
	{
		//检查是否有重复的关键字数对或表已满
		if (table[b]->first == thePair.first)
		{
			table[b]->second = thePair.second;
		}
		else
		{
			//表满
			__debugbreak;
		}
	}
}

template<class K,class E>
void hashTable<K, E>::output(std::ostream& out)const
{
	for (int i = 0; i < divisor; i++)
	{
		if (table[i] == NULL)
		{
			out << "NULL" << std::endl;
		}
		else
		{
			out << table[i]->first << " " << table[i]->second << std::endl;
		}
	}
}

template<class K,class E>
std::ostream& operator<<(std::ostream& out, const  hashTable<K, E>& x)
{
	x.output(out);
	return out;
}
