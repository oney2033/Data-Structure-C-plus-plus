#pragma once
#include<iostream>
#include<string>

template<class K>class hash;

template<>
class hash<std::string>
{
public:
	size_t operator()(const std::string theKey)const
	{//将关键字转换成非负整数
		unsigned long hashValue = 0;
		int length = theKey.length();
		for (int i = 0; i < length; i++)
		{
			hashValue = 5 * hashValue + theKey.at(i);
		}
		return size_t(hashValue);
	}
};

template<>
class hash<int>
{
public:
	size_t operator()(const int theKey)const
	{
		return size_t(theKey);
	}
};

template<>
class hash<long>
{
public:
	size_t operator()(const long theKey)const
	{
		return size_t(theKey);
	}
};

