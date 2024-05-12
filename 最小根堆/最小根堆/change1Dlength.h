#pragma once
#include<algorithm>
#include"myExceptions.h"
template<class T>
void change1Dlength(T*& a, int oldlength, int newlength)
{
	if (newlength < 1)throw illeagalParameterValue("newlength must be > 0");
	T* tmp = new T[newlength];
	int number = std::min(oldlength, newlength);
	std::copy(a, a + number, tmp);
	delete[]a;
	a = tmp;
}