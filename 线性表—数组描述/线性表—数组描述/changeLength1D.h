#pragma once
#include"myExceptions.h"
#include<algorithm>

template<class T>
void changeLength1D(T*& a, int oldlength, int newlength)
{
	if (newlength < 1)
		throw illegalPamerterValue("new length must be > 0");

	T* temp = new T[newlength];		//创建新的数组
	int number = std::min(oldlength, newlength); //要复制的数量
	std::copy(a, a + number, temp);
	delete[] a;   //删除旧的数组
	a = temp;    
}