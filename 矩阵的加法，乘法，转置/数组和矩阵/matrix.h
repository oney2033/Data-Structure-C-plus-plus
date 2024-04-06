#pragma once

//矩阵的乘法,n * n 的矩阵和 n * n 的矩阵相乘得到矩阵C,行列式的乘法
template<class T>
void squarematrixMultiply(T** a, T** b, T** c, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			T sum = 0;
			for (int k = 0; k < n; k++)
			{
				sum += a[i][k] * b[k][j];
			}
			c[i][j] = sum;
		}
	}
}

//矩阵的乘法,m * n 的矩阵和 n * p 的矩阵相乘得到 m * p 的矩阵C，行列式的乘法
template<class T>
void matrixMultiply(T** a, T** b, T** c, int m, int n, int p)
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < p; j++)
		{
			T sum = 0;
			for (int k = 0; k < n; k++)
			{
				sum += a[i][k] * b[k][j];
			}
			c[i][j] = sum;
		}
	}
}

//矩阵的加法
template<class T>
void matrixAdd(T** a, T** b, T** c, int numberOfRows, int numberOfCloumns)
{
	//只有两个行和列数量都相等的矩阵才能相加
	for (int i = 0; i < numberOfRows; i++)
	{
		for (int j = 0; j < numberOfCloumns; j++)
		{
			c[i][j] = a[i][j] + b[i][j];
		}
	}
}

//矩阵的转置
template<class T>
void transpose(T** a, int rows)
{
	//将n * n 的矩阵转置
	for (int i = 0; i < rows; i++)
		for (int j = i + 1; j < rows; j++)
		{
			std::swap(a[i][j], a[j][i]);
		}
}