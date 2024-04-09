#pragma once
#include"myExceptions.h"
//���ԽǾ��� ���� 0 Ԫ�����������Խ����� ,��|i-j|>1ʱ��M(i,j)=0��
// ���Խ��� �� i = j
// ���Խ���֮�ϵĶԽ��ߣ��߶Խ��ߣ� i = j-1
// ���Խ���֮�µĶԽ��ߣ��ͶԽ��ߣ� i = j+1
// һ���� 3 * rows - 2 ���� 0 �Խ���
template<class T>
class tridiagonalMatrix
{
public:
	tridiagonalMatrix(int theN = 10);
	~tridiagonalMatrix() { delete[]element; }
	T get(int, int)const;
	void set(int, int, const T&);
private:
	T* element; //�洢�ԽǾ����һά����
	int n; //�ԽǾ����ά��
};

//�����Խ���ӳ�䣬���¶Խ��ߵ��϶Խ���
template<class T>
void tridiagonalMatrix<T>::set(int i, int j, const T& newValue)
{
	if (i<1 || j<1 || i>n || j>n)
		throw matrixIndexOutofBounds();

	//ȷ��Ҫ���ص�Ԫ��
	switch (i-j)
	{
	case 1:		//�¶Խ���
		element[i - 2] = newValue; break;
	case 0:		//���Խ���
		element[n + i - 2] = newValue; break;
	case -1:	//�϶Խ���
		element[2 * n + i - 2] = newValue; break;
	default:
		if (newValue != 0)
			throw illeagParameterVaule("non-tridiagonal elements must be zero");
	}
}

//�����Խ���ӳ�䣬���¶Խ��ߵ��϶Խ���
template<class T>
T tridiagonalMatrix<T>::get(int i, int j)const
{
	if (i<1 || j<1 || i>n || j>n)
		throw matrixIndexOutofBounds();

	//ȷ��Ҫ���ص�Ԫ��
	switch (i - j)
	{
	case 1:  //�¶Խ���
		return element[i - 2];
	case 0:  //���Խ���
		return element[n + i - 2];
	case -1: //�϶Խ���
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