#pragma once

//����ĳ˷�,n * n �ľ���� n * n �ľ�����˵õ�����C,����ʽ�ĳ˷�
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

//����ĳ˷�,m * n �ľ���� n * p �ľ�����˵õ� m * p �ľ���C������ʽ�ĳ˷�
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

//����ļӷ�
template<class T>
void matrixAdd(T** a, T** b, T** c, int numberOfRows, int numberOfCloumns)
{
	//ֻ�������к�����������ȵľ���������
	for (int i = 0; i < numberOfRows; i++)
	{
		for (int j = 0; j < numberOfCloumns; j++)
		{
			c[i][j] = a[i][j] + b[i][j];
		}
	}
}

//�����ת��
template<class T>
void transpose(T** a, int rows)
{
	//��n * n �ľ���ת��
	for (int i = 0; i < rows; i++)
		for (int j = i + 1; j < rows; j++)
		{
			std::swap(a[i][j], a[j][i]);
		}
}