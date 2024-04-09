#pragma once
#include"arrayLish.h"
#include"matrixTerm.h"
#include<iterator>
#include<iostream>

//ϡ����� �����д��ڴ���Ϊ 0 ��Ԫ�أ�����������������޹���ϡ�����ķ� 0 Ԫ��ӳ�䵽һά���Ա���
//Ϊ���ؽ�������Ҫ��¼�� 0 Ԫ�ص��кţ��кţ��Լ�Ԫ�ص�ֵ
//���Ƕ���һ���ṹ�������������������ݳ�Ա��Ȼ�������ṹ�������Ա���
//���Ա�����������˵ڼ����� 0 Ԫ�أ�����˵arryLish[0] �����˵�һ����Ԫ��
template<class T>
class sparseMatrix
{
	//������������
	friend std::ostream& operator<<
		(std::ostream&, sparseMatrix<T>&);

	//�������������
	friend std::istream& operator>>
		(std::istream&, sparseMatrix<T>&);
public:
	void transpose(sparseMatrix<T>& b); //ϡ������ת�ã�ת�ú�洢�ھ��� b��
	void add(sparseMatrix<T>& b, sparseMatrix<T>& c);//����ǰ����;���b��ӣ���Ӻ�Ľṹ�洢�ھ���c��
private:
	int rows,//ϡ��������
		cols;//ϡ��������
	arrayLish<matrixTerm<T>> terms;//ϡ������з�0Ԫ�ص��б�
};


//������������
template<class T>
std::ostream& operator<<(std::ostream& out, sparseMatrix<T>& x)
{
	//���������������м��м����м����� 0 Ԫ��
	std::cout << "rows = " << x.rows << "columns = " << x.cols << std::endl;
	std::cout << "nonzero terms = " << x.terms.size() << std::endl;

	//��������һ��һ��
	for (typename arrayLish<matrixTerm<T>>::iterator i = x.terms.begin();i != x.terms.end(); i++)
	{
		out << "a(" << (*i).row << ',' << (*i).col
			<< ") = " << (*i).value << std::endl;
	}
	return out;
}

//�������������
template<class T>
std::istream& operator>>(std::istream& in, sparseMatrix<T>& x)
{
	//���������������м��м��м����� 0 Ԫ��
	int numberOfterms;
	std::cout << "Enter number of rows, columns, and #terms"
		<< std::endl;
	in >> x.rows >> x.cols >> numberOfterms;

	//���� x.terms �Ĵ�С��ȷ���㹻������
	x.terms.reSet(numberOfterms);

	//����ÿһ��
	matrixTerm<T> mTerm;
	for (int i = 0; i < numberOfterms; i++)
	{
		std::cout << "Enter row, column, and value of term "
			<< (i + 1) << std::endl;
		in >> mTerm.row >> mTerm.col >> mTerm.value;
		x.terms.set(i, mTerm);
	}
	return in;
}


/****************************************************************/
//��ʾ������TΪint���� �������Դ���,��Ϊ����������ʹ��ģ���������

//�������������<<
std::ostream& operator<<(std::ostream& out, sparseMatrix<int>& x)
{
	//���������������м��м����м����� 0 Ԫ��
	std::cout << "rows = " << x.rows << "columns = " << x.cols << std::endl;
	std::cout << "nonzero terms = " << x.terms.size() << std::endl;
	//��������һ��һ��
	for (typename arrayLish<matrixTerm<int>>::iterator i = x.terms.begin();
		i != x.terms.end(); i++)
	{
		out << "a(" << (*i).row << ","<<(*i).col
			<< ") = " << (*i).value << std::endl;
	}
	return out;
}

//�������������
std::istream& operator>>(std::istream& in, sparseMatrix<int>& x)
{
	//���������������м��м��м����� 0 Ԫ��
	int numberOfterms;
	std::cout << "Enter number of rows, columns, and #terms"
		<< std::endl;
	in >> x.rows >> x.cols >> numberOfterms;

	//���� x.terms �Ĵ�С��ȷ���㹻������
	x.terms.reSet(numberOfterms);

	//����ÿһ��
	matrixTerm<int> mTerm;
	for (int i = 0; i < numberOfterms; i++)
	{
		std::cout << "Enter row, column, and value of term "
			<< (i + 1) << std::endl;
		in >> mTerm.row >> mTerm.col >> mTerm.value;
		x.terms.set(i, mTerm);
	}
	return in;
}
/****************************************************************/



//�����ת�ã�ת�ú�洢�ھ��� b��
template<class T>
void sparseMatrix<T>::transpose(sparseMatrix<T>& b)
{
	//����ת�þ�������кʹ�С
	b.cols = rows;
	b.rows = cols;
	b.terms.reSet(terms.size());
	//��ʼ����ʵ��ת��
	//colSize����������������i�з� 0 Ԫ�صĸ���
	int* colSize = new int[cols + 1];
	//rowNext��������ת�ú����ÿһ�з� 0 Ԫ����һά�����е���������ʼλ��
	//����˵��ת�ú�ľ��󣬵�һ�еķ���Ԫ����2����rowNext[1] = 0,rowNext[2] = 2;
	int* rowNext = new int[cols + 1];

	//Ѱ�����������ÿһ�з� 0 Ԫ�صĸ���
	for (int i = 1; i <= cols; i++)
		colSize[i] = 0;
	for (typename arrayLish<matrixTerm<T>>::iterator i = terms.begin();i != terms.end(); i++)
		colSize[(*i).col]++;

	//Ѱ�Ҿ���b��ÿһ�е���ʼ��
	rowNext[1] = 0;
	for (int i = 2; i <= cols; i++)
		rowNext[i] = rowNext[i - 1] + colSize[i - 1];

	//ʵ�ִ�������󵽾���b�ĸ���
	matrixTerm<T>mTerm;
	for (typename arrayLish<matrixTerm<T>>::iterator i = terms.begin();
		i != terms.end(); i++)
	{
		int j = rowNext[(*i).col]++;//b�е�λ��
		mTerm.row = (*i).col;
		mTerm.col = (*i).row;
		mTerm.value = (*i).value;
		b.terms.set(j, mTerm);
	}
}

//����ǰ����;���b��ӣ���Ӻ�Ľṹ�洢�ھ���c��
template<class T>
void sparseMatrix<T>::add(sparseMatrix<T>& b, sparseMatrix<T>& c)
{
	//������е������Ƿ����
	if (rows != b.rows || cols != b.cols)
		throw matrixSizeMismatch();

	//���ý������c������
	c.rows = rows;
	c.cols = cols;
	c.terms.clear();
	int cSize = 0;

	//���嵱ǰ����;���b�ĵ�����
	typename arrayLish<matrixTerm<T>>::iterator it = terms.begin();
	typename arrayLish<matrixTerm<T>>::iterator ib = b.terms.begin();
	typename arrayLish<matrixTerm<T>>::iterator itEnd = terms.end();
	typename arrayLish<matrixTerm<T>>::iterator ibEnd = b.terms.end();

	//������ǰ����;���b������������
	while (it != itEnd && ib != ibEnd)
	{
		//�ڼ��еڼ���Ԫ�ص��±�
		int tIndex = (*it).row * cols + (*it).col;
		int bIndex = (*ib).row * cols + (*ib).col;
		
		//�Ƚ��±��С
		if (tIndex < bIndex)
		{
			c.terms.insert(cSize++, *it);
			it++;
		}
		else
		{//�����±���Ƚ������
			if (tIndex == bIndex)
			{
				if ((*it).value + (*ib).value != 0)
				{
					matrixTerm<T>mTerm;
					mTerm.row = (*it).row;
					mTerm.col = (*it).col;
					mTerm.value = (*it).value + (*ib).value;
					c.terms.insert(cSize++, mTerm);
				}
				it++;
				ib++;
			}
			else
			{
				c.terms.insert(cSize++, *ib);
				ib++;
			}
		}
	}
	//��ʣ�µ���ӽ�����c
	for (; it != itEnd; it++)
		c.terms.insert(cSize++, *it);
	for (; ib != ibEnd; ib++)
		c.terms.insert(cSize++, *ib);
}
