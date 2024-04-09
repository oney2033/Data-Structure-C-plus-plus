#pragma once
#include"myExceptions.h"
//三对角矩阵 ：非 0 元素在这三条对角线上 ,当|i-j|>1时，M(i,j)=0；
// 主对角线 ： i = j
// 主对角线之上的对角线（高对角线） i = j-1
// 主对角线之下的对角线（低对角线） i = j+1
// 一共有 3 * rows - 2 条非 0 对角线
template<class T>
class tridiagonalMatrix
{
public:
	tridiagonalMatrix(int theN = 10);
	~tridiagonalMatrix() { delete[]element; }
	T get(int, int)const;
	void set(int, int, const T&);
private:
	T* element; //存储对角矩阵的一维数组
	int n; //对角矩阵的维数
};

//逐条对角线映射，从下对角线到上对角线
template<class T>
void tridiagonalMatrix<T>::set(int i, int j, const T& newValue)
{
	if (i<1 || j<1 || i>n || j>n)
		throw matrixIndexOutofBounds();

	//确定要返回的元素
	switch (i-j)
	{
	case 1:		//下对角线
		element[i - 2] = newValue; break;
	case 0:		//主对角线
		element[n + i - 2] = newValue; break;
	case -1:	//上对角线
		element[2 * n + i - 2] = newValue; break;
	default:
		if (newValue != 0)
			throw illeagParameterVaule("non-tridiagonal elements must be zero");
	}
}

//逐条对角线映射，从下对角线到上对角线
template<class T>
T tridiagonalMatrix<T>::get(int i, int j)const
{
	if (i<1 || j<1 || i>n || j>n)
		throw matrixIndexOutofBounds();

	//确定要返回的元素
	switch (i - j)
	{
	case 1:  //下对角线
		return element[i - 2];
	case 0:  //主对角线
		return element[n + i - 2];
	case -1: //上对角线
		return element[2 * n + i - 2];
	default:
		return 0;
	}
}

template<class T>
tridiagonalMatrix<T>::tridiagonalMatrix(int theN)
{
	if (theN < 1)
		throw illeagParameterVaule();
	n = theN;
	element = new T[3 * n - 2];
}