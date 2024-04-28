#pragma once
#include"Hash.h"
#include<utility>
#include<sstream>

//ɢ�б�����̽���ʾ
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
	//ɢ�б�����ݳ�Ա
	int search(const K&)const;
	std::pair<const K, E>** table;   //ɢ�б�
	hash<K> hash;		//������Kӳ�䵽һ��������
	int dSize;          //�ֵ������Ը���
	int divisor;        //ɢ�к�������
};

//���캯��
template<class K,class E>
hashTable<K, E>::hashTable(int theDivisor)
{
	divisor = theDivisor;
	dSize = 0;
	//����ͳ�ʼ��ɢ������
	table = new std::pair<const K, E>*[divisor];
	for (int i = 0; i < divisor; i++)
		table[i] = NULL;
}

//��������,��ƥ��������򷵻�����λ�ã��������ɢ�б������򷵻عؼ���ΪtheKey�����Կ��Բ����λ��
template<class K,class E>
int hashTable<K, E>::search(const K& theKey)const
{
	int i = hash(theKey) % divisor;//��ʼͰ
	int j = i;
	do
	{
		if (table[j] == NULL || table[j]->first == theKey)
		{
			return j;
		}
		j = (i + 1) % divisor;		//��һ��Ͱ
	} while (j != i);

	return j;		//����
}

//���Һ���,����ƥ�����Ե�ָ�룬�������򷵻�NULL
template<class K,class E>
std::pair<const K, E>* hashTable<K, E>::find(const K& theKey)const
{
	//����ɢ�б�
	int b = search(theKey);
	
	//�ж�table[b]�Ƿ���ƥ������
	if (table[b] == NULL || table[b]->first != theKey)
		return NULL;	//û���ҵ�
	return table[b];//�ҵ�
	
}

//���뺯��
template<class K,class E>
void hashTable<K, E>::insert(const std::pair<const K, E>& thePair)
{
	int b = search(thePair.first);

	//����ƥ��������Ƿ����
	if (table[b] == NULL)
	{
		//û��ƥ������ԣ����ұ���
		table[b] = new std::pair<const K, E>(thePair);
		dSize++;
	}
	else
	{
		//����Ƿ����ظ��Ĺؼ������Ի������
		if (table[b]->first == thePair.first)
		{
			table[b]->second = thePair.second;
		}
		else
		{
			//����
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
