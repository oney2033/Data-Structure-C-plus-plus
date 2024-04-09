#pragma once
template<class T>
struct matrixTerm
{
	int row,
		col;
	T value;
	operator T()const { return value; }//从 matrixTerm 到 T 的类型转换
};