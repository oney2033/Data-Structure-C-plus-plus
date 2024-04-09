#pragma once
#include"myExceptions.h"
//�����Ǿ���,���� n*(n + 1) /2
template<class T>
class lowerTriangularMatrix
{
public:
	lowerTriangularMatrix(int theN = 10);
	~lowerTriangularMatrix() { delete[]element; }
	T get(int, int)const;
	void set(int, int, const T&);
private:
	T* element; //�洢�ԽǾ����һά����
	int n; //�ԽǾ����ά��
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