#pragma once
template<class T>
void make2Darray(T**& x, int numberOfRows, int numberOfColumns)
{	//������ά����
		//�����е�ָ��
		x = new T * [numberOfRows];

		//����ÿ�е�ָ��
		for (int i = 0; i < numberOfRows; i++)
		{
			x[i] = new T[numberOfColumns];
		}
}