#include<iostream>
#include"make2DarrayNoCatch.h"
#include"matrix.h"
using namespace std;

int main()
{

	//m * n������� n * p �ľ���õ� m * p �ľ���
	int** a, ** b, ** c;
	make2Darray(a, 2, 2);
	make2Darray(b, 2, 2);
	make2Darray(c, 2, 2);

	a[0][0] = 1; a[0][1] = 2; a[1][0] = 3; a[1][1] = 4;
	b[0][0] = 5; b[0][1] = 6; b[1][0] = 1; b[1][1] = 2;

	cout << "The first matrix is" << endl;
	cout << a[0][0] << ' ' << a[0][1] << endl;
	cout << a[1][0] << ' ' << a[1][1] << endl;

	cout << "The second matrix is" << endl;
	cout << b[0][0] << ' ' << b[0][1] << endl;
	cout << b[1][0] << ' ' << b[1][1] << endl;

	matrixMultiply(a, b, c, 2, 2, 2);

	cout << "Their product is" << endl;
	cout << c[0][0] << ' ' << c[0][1] << endl;
	cout << c[1][0] << ' ' << c[1][1] << endl;


#if 0
	//����˷�
	int** a, ** b, ** c;
	make2Darray(a, 2, 2);
	make2Darray(b, 2, 2);
	make2Darray(c, 2, 2);

	a[0][0] = 1; a[0][1] = 2; a[1][0] = 3; a[1][1] = 4;
	b[0][0] = 5; b[0][1] = 6; b[1][0] = 1; b[1][1] = 2;

	cout << "The first matrix is" << endl;
	cout << a[0][0] << ' ' << a[0][1] << endl;
	cout << a[1][0] << ' ' << a[1][1] << endl;

	cout << "The second matrix is" << endl;
	cout << b[0][0] << ' ' << b[0][1] << endl;
	cout << b[1][0] << ' ' << b[1][1] << endl;

	squarematrixMultiply(a, b, c, 2);

	cout << "Their product is" << endl;
	cout << c[0][0] << ' ' << c[0][1] << endl;
	cout << c[1][0] << ' ' << c[1][1] << endl;
#endif

#if 0
	//����ӷ�
	int** a, ** b, ** c;
	make2Darray(a, 2, 2);
	make2Darray(b, 2, 2);
	make2Darray(c, 2, 2);

	a[0][0] = 1; a[0][1] = 2; a[1][0] = 3; a[1][1] = 4;
	b[0][0] = 5; b[0][1] = 6; b[1][0] = 1; b[1][1] = 2;

	cout << "The first matrix is" << endl;
	cout << a[0][0] << ' ' << a[0][1] << endl;
	cout << a[1][0] << ' ' << a[1][1] << endl;

	cout << "The second matrix is" << endl;
	cout << b[0][0] << ' ' << b[0][1] << endl;
	cout << b[1][0] << ' ' << b[1][1] << endl;

	matrixAdd(a, b, c, 2, 2);

	cout << "Their sum is" << endl;
	cout << c[0][0] << ' ' << c[0][1] << endl;
	cout << c[1][0] << ' ' << c[1][1] << endl;
	
	int** e;
	make2Darray(e, 2, 2);
	e[0][0] = 1; e[0][1] = 2; e[1][0] = 3; e[1][1] = 4;
	std::cout << "The matrix is" << std::endl;
	std::cout << e[0][0] << ' ' << e[0][1] << std::endl;
	std::cout << e[1][0] << ' ' << e[1][1] << std::endl;
	transpose(e, 2);
	std::cout << "The transposed matrix is" << std::endl;
	std::cout << e[0][0] << ' ' << e[0][1] << std::endl;
	std::cout << e[1][0] << ' ' << e[1][1] << std::endl;

#endif

}
#if 0
	//һ���������ά����Ĵ�����ʹ��
	int numberOfRows = 5;
	//����ÿһ�еĳ���
	int length[5] = { 6,3,4,2,7 };
	//����һ����ά�������
	//������Ҫ������
	int** irregularArray = new int* [numberOfRows];
	//����ÿһ�еĿռ�
	for (int i = 0; i < numberOfRows; i++)
		irregularArray[i] = new int[length[i]];

	//��ʹ�ù�������һ��ʹ�ò���������
	irregularArray[2][3] = 5;
	irregularArray[4][6] = irregularArray[2][3] + 2;
	irregularArray[1][1] = 3;

	//ѡ��Ҫ���������Ԫ��
	std::cout << irregularArray[2][3] << std::endl;
	std::cout << irregularArray[4][6] << std::endl;
	std::cout << irregularArray[1][1] << std::endl;

	//ɾ��������ڴ�
	for (int i = 0; i < 5; i++)
		delete[]irregularArray[i];
	delete[]irregularArray;
}
#endif