#pragma once
template<class T>
struct matrixTerm
{
	int row,
		col;
	T value;
	operator T()const { return value; }//�� matrixTerm �� T ������ת��
};