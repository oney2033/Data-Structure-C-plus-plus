#pragma once
#include"myExceptions.h"
template<class T>
void changeLength1D(T*& a, int oldlength, int newlength)
{
	if (newlength < 1)
		throw illeagParameterVaule("new length must be > 0");
	T* temp = new T[newlength];
	int number = std::min(oldlength, newlength);
	std::copy(a, a + number, temp);
	delete[] a;
	a = temp;
}