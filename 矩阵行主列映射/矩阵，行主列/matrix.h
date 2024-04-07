#pragma once
#include"myExceptions.h"
//行主映射的矩阵,将二维转换为一维 :total = x + y *weidth

template<class T>
class matrix
{
public:
	matrix(int theRows = 0, int theColumns = 0);
	matrix(const matrix<T>&);
	~matrix() { delete[]elment; }
	int rows()const { return theRows; }
	int columns()const { return theColumns; }
	T& operator () (int i, int j)const;//重载()操作符，使得操作能像数学里的矩阵那样matrix(i,j)获取下标的值
	matrix<T>& operator = (const matrix<T>&);//重载赋值操作符号 = ,和上面的()运算符号组合起来就能实现，matrix(i,j)=2,或者x=matrix(i,j)
	matrix<T> operator + (const matrix<T>&) const;//重载操作符 + ,实现矩阵的加法
	matrix<T> operator + ()const;//重载一元运算符 + ，相当于矩阵的每个元素乘以 1
	matrix<T> operator - (const matrix<T>&)const;//重载操作符 - ,实现矩阵的减法
	matrix<T> operator - ()const;//重载一元运算符 -，返回-的矩阵
	matrix<T> operator * (const matrix<T>&)const;//重载操作符 *，实现矩阵乘法
	matrix<T>& operator += (const T&);//重载操作符 +=

	friend std::ostream& operator<<(std::ostream&, const matrix<T>& m);//定义为friend函数，这样可以直接访问private成员
private:
	int theRows,    //矩阵的行数
		theColumns; //矩阵的列数
	T* elment;		//元素数组
};

//构造函数
template<class T>
matrix<T>::matrix(int theRows, int theColumns)
{
	//检查矩阵的行和列,矩阵不仅生成行和列都大于0的，还生成 0 * 0 的矩阵
	if (theRows < 0 || theColumns < 0)
		throw illegalParameterValue("Rows and Columns must be >=0");
	if ((theRows == 0 || theColumns == 0) && (theRows != 0 || theColumns != 0))
		throw illegalParameterValue
		("Either both or neither rows and columns should be zero");

	//创建矩阵
	this->theRows = theRows;
	this->theColumns = theColumns;
	elment = new T[theRows * theColumns];
}

//复制构造函数
template<class T>
matrix<T>::matrix(const matrix<T>& m)
{
	theRows = m.theRows;
	theColumns = m.theColumns;
	elment = new T[theRows * theColumns];
	//复制m的每一个元素
	std::copy(m.elment, m.elment + theRows * theColumns, elment);
}

//定义为friend函数，这样可以直接访问private成员
template<class T>
std::ostream& operator<<(std::ostream& out, const matrix<T>& m)
{
	int k = 0;
	for (int i = 0; i < m.theRows; i++)
	{
		for (int j = 0; j < m.theColumns; j++)
		{
			out << m.elment[k++] << " ";
		}
		out << std::endl;
	}
	return out;
}

//由于某种原因编译器无法自行创建它,和上面那句一样，只是没有用模板
std::ostream& operator<<(std::ostream& out, const matrix<int>& m)
{
	int k = 0;
	for (int i = 0; i < m.theRows; i++)
	{
		for (int j = 0; j < m.theColumns; j++)
		{
			out << m.elment[k++] << " ";
		}
		out << std::endl;
	}
	return out;
}


//重载操作符 +=
template<class T>
matrix<T>& matrix<T>::operator+=(const T& x)
{
	for (int i = 0; i < theRows * theColumns; i++)
		elment[i] += x;
	return *this;
}

//重载操作符 *，实现矩阵乘法,用点乘的方法
template<class T>
matrix<T> matrix<T>::operator*(const matrix<T>& m)const
{
	if (theColumns != m.theRows)
		throw matrixSizeMismatch();
	//创建结果矩阵
	matrix<T>w(theRows, m.theColumns);
	//定义三个游标 ct、cm 和 cw，分别用于遍历当前矩阵、传入矩阵和结果矩阵，并初始化它们的位置为 (1,1) 元素的位置。
	//在数组中的索引是 0
	int ct = 0, cm = 0, cw = 0;

	//计算所有的i和j
	for (int i = 1; i <= theRows; i++)
	{
		for (int j = 1; j <= m.theColumns; j++)
		{
			//先计算 i 和 j的第一项乘积
			T sum = elment[ct] * m.elment[cm];
			//将剩下的加起来
			for (int k = 2; k <= theColumns; k++)
			{
				ct++;//移动当前矩阵的游标
				cm += m.theColumns;//移动传入矩阵的游标
				sum += elment[ct] * m.elment[cm];//相加
			}

			w.elment[cw++] = sum;
			ct -= theColumns - 1;//将当前矩阵的游标移回去，进行下一列的相乘
			cm = j;//将传入矩阵的游标移到下一列
		}

		//重置为下一行和第一列的开头
		ct += theColumns;
		cm = 0;
	}
	return w;
}

//重载一元运算符 -，返回-的矩阵
template<class T>
matrix<T> matrix<T>::operator-()const
{
	matrix<T>w(theRows, theColumns);
	for (int i = 0; i < theRows * theColumns; i++)
		w.elment[i] = -elment[i];
	return w;
}

//重载操作符 - ,实现矩阵的减法
template<class T>
matrix<T> matrix<T>::operator-(const matrix<T>& m)const
{
	if (theRows != m.theRows || theColumns != m.theColumns)
		throw matrixSizeMismatch();
	// 创建一个新矩阵来存储结果
	matrix<T>w(theRows, theColumns);
	for (int i = 0; i < theRows * theColumns; i++)
	{
		w.elment[i] = elment[i] + m.elment[i];
	}
	return w;
}

//重载操作符 + ,实现矩阵的加法
template<class T>
matrix<T> matrix<T>::operator+(const matrix<T>& m)const
{
	if (theRows != m.theRows || theColumns != m.theColumns)
		throw matrixSizeMismatch();

	//创建一个新矩阵来存储结果
	matrix<T>w(theRows, theColumns);
	for (int i = 0; i < theRows * theColumns; i++)
	{
		w.elment[i] = elment[i] + m.elment[i];
	}
	return w;
}

//重载赋值操作符号 = ,和()运算符号组合起来就能实现，matrix(i,j)=2,或者x=matrix(i,j)
template<class T>
matrix<T>& matrix<T>::operator=(const matrix<T>& m)
{
	//不能直接复制自己
	if (this != &m)
	{
		delete[] elment;
		theRows = m.theRows;
		theColumns = m.theColumns;
		elment = new T[theRows * theColumns];
		//复制每一个元素
		std::copy(m.elment, m.elment + theRows * theColumns, elment);
	}
	return *this;
}

//重载()操作符，使得操作能像二维数组那样matrix[i][j]获取下标的值
template<class T>
T& matrix<T>::operator()(int i, int j)const
{
	if (1 < 1 || i > theRows
		|| j<1 || j>theColumns)
		throw matrixIndexOutOfBounds();
	return elment[(i - 1) * theColumns + j - 1];
}
