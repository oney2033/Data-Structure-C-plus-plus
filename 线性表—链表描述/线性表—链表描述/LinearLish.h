#pragma once
#include<iostream>
template<class T>
class LinearLish
{
public:
	virtual ~LinearLish() {};
	virtual bool empty()const = 0;
	virtual int size()const = 0;
	virtual T& get(int theIndex)const = 0;
	virtual int indexOf(const T& theElment)const = 0;
	virtual void erase(int theIndex) = 0;
	virtual void insert(int theIndex, const T& theElment) = 0;
	virtual void output(std::ostream& out)const = 0;
};