#pragma once
#include"myExceptions.h"

//�ԽǾ��� �� �� i ��= j ʱ��M(i,j) = 0
//rows * rows �ĶԽǾ����ö�ά�����ʾ�Ļ���Ҫ rows^2������Ϊ T �����ݿռ�
//���ݶԽǾ�������ʣ�ֻ��rows���� 0 Ԫ�أ��������ǿ�����һά��������ʾ��û���������ڳ��ֵ�Ԫ�ؾ�Ϊ 0 
template<class T>
class diagonaMatrix
{
public:
	diagonaMatrix(int theN = 10);
	~diagonaMatrix() { delete[] element; }
	T get(int, int)const;
	void set(int, int, const T&);
private:
	T* element;//�洢�ԽǾ����һά����
	int n;//�ԽǾ����ά��
};

//���캯��
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