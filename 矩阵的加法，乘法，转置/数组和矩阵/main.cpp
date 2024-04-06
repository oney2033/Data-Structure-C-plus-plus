#include<iostream>
#include"make2DarrayNoCatch.h"
#include"matrix.h"
using namespace std;

int main()
{

	//m * n矩阵乘于 n * p 的矩阵得到 m * p 的矩阵
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
	//方阵乘法
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
	//矩阵加法
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
	//一个不规则二维数组的创建和使用
	int numberOfRows = 5;
	//定义每一行的长度
	int length[5] = { 6,3,4,2,7 };
	//声明一个二维数组变量
	//分配需要的行数
	int** irregularArray = new int* [numberOfRows];
	//分配每一行的空间
	for (int i = 0; i < numberOfRows; i++)
		irregularArray[i] = new int[length[i]];

	//想使用规则数组一样使用不规则数组
	irregularArray[2][3] = 5;
	irregularArray[4][6] = irregularArray[2][3] + 2;
	irregularArray[1][1] = 3;

	//选择要输出的数组元素
	std::cout << irregularArray[2][3] << std::endl;
	std::cout << irregularArray[4][6] << std::endl;
	std::cout << irregularArray[1][1] << std::endl;

	//删除分配的内存
	for (int i = 0; i < 5; i++)
		delete[]irregularArray[i];
	delete[]irregularArray;
}
#endif