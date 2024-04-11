#pragma once
#include<exception>
template<class T>
bool make2Darray(T**& x, int numberOfRows, int numberOfColumns)
{
	//����2D����
	try
	{
		x = new T * [numberOfRows];
		for (int i = 0; i < numberOfRows; i++)
		{
			x[i] = new int[numberOfColumns];
		}
			return true;
	}
	catch (std::bad_alloc) { return false; }
}