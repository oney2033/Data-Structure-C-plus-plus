#pragma once
template<class T>
void make2Darray(T**& x, int numberOfRows, int numberOfColumns)
{	//创建二维数组
		//创建行的指针
		x = new T * [numberOfRows];

		//创建每行的指针
		for (int i = 0; i < numberOfRows; i++)
		{
			x[i] = new T[numberOfColumns];
		}
}