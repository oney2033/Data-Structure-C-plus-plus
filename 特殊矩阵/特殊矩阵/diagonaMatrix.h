#pragma once
#include"myExceptions.h"

//对角矩阵 ： 当 i ！= j 时，M(i,j) = 0
//rows * rows 的对角矩阵用二维数组表示的话需要 rows^2个类型为 T 的数据空间
//根据对角矩阵的性质，只有rows个非 0 元素，所以我们可以用一维数组来表示，没有在数组内出现的元素均为 0 
template<class T>
class diagonaMatrix
{
public:
	diagonaMatrix(int theN = 10);
	~diagonaMatrix() { delete[] element; }
	T get(int, int)const;
	void set(int, int, const T&);
private:
	T* element;//存储对角矩阵的一维数组
	int n;//对角矩阵的维数
};

//构造函数
template<class T>
diagonaMatrix<T>::diagonaMatrix(int theN)
{
	if (theN < 1)
		throw illeagParameterVaule("Matrix size must be > 10");

	n = theN;
	element = new T[n];
}

template<class T>
T diagonaMatrix<T>::get(int i, int j)const
{
	if (i <1 || j<1 || i>n || j>n)
		throw matrixIndexOutofBounds();
	if (i == j)
		return element[i - 1];
	else
		return 0;
}

template<class T>
void diagonaMatrix<T>::set(int i, int j, const T& newValue)
{
	if (i<1 || j<1 || i>n || j>n)
		throw matrixIndexOutofBounds();
	if (i == j)
		element[i - 1] = newValue;
	else
		if (newValue != 0)
			throw illeagParameterVaule("nondiagonal elements must be zero");
}