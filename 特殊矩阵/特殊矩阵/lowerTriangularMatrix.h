#pragma once
#include"myExceptions.h"
//下三角矩阵,共有 n*(n + 1) /2
template<class T>
class lowerTriangularMatrix
{
public:
	lowerTriangularMatrix(int theN = 10);
	~lowerTriangularMatrix() { delete[]element; }
	T get(int, int)const;
	void set(int, int, const T&);
private:
	T* element; //存储对角矩阵的一维数组
	int n; //对角矩阵的维数
};

template<class T>
lowerTriangularMatrix<T>::lowerTriangularMatrix(int theN)
{
	if (theN < 1)
		throw illeagParameterVaule("Matrix size must be > 0");
	n = theN;
	element = new T[n * (n + 1) / 2];
}

template<class T>
T lowerTriangularMatrix<T>::get(int i, int j)const
{
	if (i<1 || j<1 || i>n || j>n)
		throw matrixIndexOutofBounds();

	if (i >= j)
		return element[i * (i - 1) / 2 + j - 1];
	else
		return 0;
}

template<class T>
void lowerTriangularMatrix<T>::set(int i, int j, const T& newValue)
{
	if (i<1 || j<1 || i>n || j>n)
		throw matrixIndexOutofBounds();
	if (i >= j)
		element[i * (i - 1) / 2 + j - 1] = newValue;
	else
		if (newValue != 0)
			throw illeagParameterVaule("elements not in lower triangle must be zero");
}