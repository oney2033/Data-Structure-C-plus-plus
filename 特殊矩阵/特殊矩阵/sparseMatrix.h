#pragma once
#include"arrayLish.h"
#include"matrixTerm.h"
#include<iterator>
#include<iostream>

//稀疏矩阵： 矩阵中存在大量为 0 的元素，我们用行主次序把无规则稀疏矩阵的非 0 元素映射到一维线性表中
//为了重建矩阵，需要记录非 0 元素的行号，列号，以及元素的值
//我们定义一个结构，里面有以上三个数据成员，然后把这个结构存入线性表中
//线性表的索引代表了第几个非 0 元素，比如说arryLish[0] 代表了第一个非元素
template<class T>
class sparseMatrix
{
	//重载输出运算符
	friend std::ostream& operator<<
		(std::ostream&, sparseMatrix<T>&);

	//重载输入运算符
	friend std::istream& operator>>
		(std::istream&, sparseMatrix<T>&);
public:
	void transpose(sparseMatrix<T>& b); //稀疏矩阵的转置，转置后存储在矩阵 b中
	void add(sparseMatrix<T>& b, sparseMatrix<T>& c);//将当前矩阵和矩阵b相加，相加后的结构存储在矩阵c中
private:
	int rows,//稀疏矩阵的行
		cols;//稀疏矩阵的列
	arrayLish<matrixTerm<T>> terms;//稀疏矩阵中非0元素的列表
};


//重载输出运算符
template<class T>
std::ostream& operator<<(std::ostream& out, sparseMatrix<T>& x)
{
	//输出矩阵的特征，有几行几列有几个非 0 元素
	std::cout << "rows = " << x.rows << "columns = " << x.cols << std::endl;
	std::cout << "nonzero terms = " << x.terms.size() << std::endl;

	//输出矩阵项，一行一个
	for (typename arrayLish<matrixTerm<T>>::iterator i = x.terms.begin();i != x.terms.end(); i++)
	{
		out << "a(" << (*i).row << ',' << (*i).col
			<< ") = " << (*i).value << std::endl;
	}
	return out;
}

//重载输入运算符
template<class T>
std::istream& operator>>(std::istream& in, sparseMatrix<T>& x)
{
	//输入矩阵的特征，有几行几列几个非 0 元素
	int numberOfterms;
	std::cout << "Enter number of rows, columns, and #terms"
		<< std::endl;
	in >> x.rows >> x.cols >> numberOfterms;

	//设置 x.terms 的大小并确保足够的容量
	x.terms.reSet(numberOfterms);

	//输入每一项
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
//显示的声明T为int类型 用来测试代码,因为编译器不能使用模板进行生成

//重载输出操作符<<
std::ostream& operator<<(std::ostream& out, sparseMatrix<int>& x)
{
	//输出矩阵的特征，有几行几列有几个非 0 元素
	std::cout << "rows = " << x.rows << "columns = " << x.cols << std::endl;
	std::cout << "nonzero terms = " << x.terms.size() << std::endl;
	//输出矩阵项，一行一个
	for (typename arrayLish<matrixTerm<int>>::iterator i = x.terms.begin();
		i != x.terms.end(); i++)
	{
		out << "a(" << (*i).row << ","<<(*i).col
			<< ") = " << (*i).value << std::endl;
	}
	return out;
}

//重载输入运算符
std::istream& operator>>(std::istream& in, sparseMatrix<int>& x)
{
	//输入矩阵的特征，有几行几列几个非 0 元素
	int numberOfterms;
	std::cout << "Enter number of rows, columns, and #terms"
		<< std::endl;
	in >> x.rows >> x.cols >> numberOfterms;

	//设置 x.terms 的大小并确保足够的容量
	x.terms.reSet(numberOfterms);

	//输入每一项
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



//矩阵的转置，转置后存储在矩阵 b中
template<class T>
void sparseMatrix<T>::transpose(sparseMatrix<T>& b)
{
	//设置转置矩阵的行列和大小
	b.cols = rows;
	b.rows = cols;
	b.terms.reSet(terms.size());
	//初始化以实现转置
	//colSize数组存的是输入矩阵第i列非 0 元素的个数
	int* colSize = new int[cols + 1];
	//rowNext数组存的是转置后矩阵每一行非 0 元素在一维数组中的索引的起始位置
	//比如说，转置后的矩阵，第一行的非零元素有2个，rowNext[1] = 0,rowNext[2] = 2;
	int* rowNext = new int[cols + 1];

	//寻找输入矩阵中每一列非 0 元素的个数
	for (int i = 1; i <= cols; i++)
		colSize[i] = 0;
	for (typename arrayLish<matrixTerm<T>>::iterator i = terms.begin();i != terms.end(); i++)
		colSize[(*i).col]++;

	//寻找矩阵b中每一行的起始点
	rowNext[1] = 0;
	for (int i = 2; i <= cols; i++)
		rowNext[i] = rowNext[i - 1] + colSize[i - 1];

	//实现从输入矩阵到矩阵b的复制
	matrixTerm<T>mTerm;
	for (typename arrayLish<matrixTerm<T>>::iterator i = terms.begin();
		i != terms.end(); i++)
	{
		int j = rowNext[(*i).col]++;//b中的位置
		mTerm.row = (*i).col;
		mTerm.col = (*i).row;
		mTerm.value = (*i).value;
		b.terms.set(j, mTerm);
	}
}

//将当前矩阵和矩阵b相加，相加后的结构存储在矩阵c中
template<class T>
void sparseMatrix<T>::add(sparseMatrix<T>& b, sparseMatrix<T>& c)
{
	//检查行列的数量是否相等
	if (rows != b.rows || cols != b.cols)
		throw matrixSizeMismatch();

	//设置结果矩阵c的特征
	c.rows = rows;
	c.cols = cols;
	c.terms.clear();
	int cSize = 0;

	//定义当前矩阵和矩阵b的迭代器
	typename arrayLish<matrixTerm<T>>::iterator it = terms.begin();
	typename arrayLish<matrixTerm<T>>::iterator ib = b.terms.begin();
	typename arrayLish<matrixTerm<T>>::iterator itEnd = terms.end();
	typename arrayLish<matrixTerm<T>>::iterator ibEnd = b.terms.end();

	//遍历当前矩阵和矩阵b，把相关项相加
	while (it != itEnd && ib != ibEnd)
	{
		//第几行第几个元素的下标
		int tIndex = (*it).row * cols + (*it).col;
		int bIndex = (*ib).row * cols + (*ib).col;
		
		//比较下标大小
		if (tIndex < bIndex)
		{
			c.terms.insert(cSize++, *it);
			it++;
		}
		else
		{//两个下标相等进行相加
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
	//将剩下的添加进矩阵c
	for (; it != itEnd; it++)
		c.terms.insert(cSize++, *it);
	for (; ib != ibEnd; ib++)
		c.terms.insert(cSize++, *ib);
}
