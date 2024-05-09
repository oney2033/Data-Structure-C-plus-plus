#pragma once
#include<algorithm>
#include"myExceptions.h"
template<class T>
void change1Dlength(T*& element, int oldlength, int newlength)
{
	if (newlength < 0)throw illegalParameterValue("new length must be >= 0");

	T* temp = new T[newlength];
	int number = std::min(oldlength, newlength);
	std::copy(element, element + number, temp);
	delete[]element;
	element = temp;
}