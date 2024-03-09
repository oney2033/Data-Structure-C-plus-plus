#pragma once
#include<iostream>
//抽象类LinearLisht
//所有方法都是虚函数

template<class T>
class LinearLish
{
public:
	virtual ~LinearLish() {};
	virtual bool empty()const = 0;	//当列表为空时返回true
	virtual int size()const = 0;	//返回列表中元素的数量
	virtual T& get(int theIndex)const = 0;	//返回列表中索引为theIndex的元素
	virtual int indexOf(const T& theElement)const = 0; //返回元素在列表中第一次出现的位置
	virtual void erase(int theIndex) = 0;  //删除索引为theIndex的元素
	virtual void insert(int theIndex, const T& theElement) = 0;//插入元素，使其索引为theIndex
	virtual void output(std::ostream& out)const = 0;//将列表插入流输入
};