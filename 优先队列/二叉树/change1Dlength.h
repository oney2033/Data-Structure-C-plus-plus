#pragma once
#include<algorithm>
#include"myExceptions.h"
template<class T>
void change1Dlength(T*& a, int oldlength, int newlength)
{
	if (newlength < 0)throw illegalParameterValue("new length must be >= 0");

	T* temp = new T[newlength];
	int number = std::min(oldlength, newlength);
	std::copy(a, a + number, temp);
	delete[]a;
	a = temp;
}