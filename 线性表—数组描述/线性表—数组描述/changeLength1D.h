#pragma once
#include"myExceptions.h"
#include<algorithm>

template<class T>
void changeLength1D(T*& a, int oldlength, int newlength)
{
	if (newlength < 1)
		throw illegalPamerterValue("new length must be > 0");

	T* temp = new T[newlength];		//�����µ�����
	int number = std::min(oldlength, newlength); //Ҫ���Ƶ�����
	std::copy(a, a + number, temp);
	delete[] a;   //ɾ���ɵ�����
	a = temp;    
}