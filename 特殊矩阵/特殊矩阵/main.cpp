#include"diagonaMatrix.h"
#include"tridiagonalMatrix.h"
#include<iostream>
#include"lowerTriangularMatrix.h"
#include"arrayLish.h"
#include"myExceptions.h"
#include"sparseMatrix.h"

using namespace std;
int main()
{
	//测试一个线性表描述的稀疏矩阵
	sparseMatrix<int>a, b, c;

	//测试输入和输出
	cin >> a;
	cout << "Matrix a is" << endl << a;
	cin >> b;
	cout << "Matrix b is" << endl << b;

	// 测试转置
	a.transpose(c);
	cout << "The transpose of a is" << endl << c;

	// 测试相加
	a.add(b, c);
	cout << "The sum of a and b is" << endl << c;

}
#if 0
	//测试下三角矩阵
	lowerTriangularMatrix<int> x(20);
	x.set(1, 1, 22);
	x.set(5, 3, 44);
	x.set(8, 5, 0);
	x.set(10, 2, 55);
	x.set(8, 5, 0);
	cout << x.get(10, 2) << endl;
	cout << x.get(5, 3) << endl;
	cout << x.get(1, 1) << endl;
	cout << x.get(10, 14) << endl;
	cout << x.get(8, 5) << endl;
#endif

#if 0
	//测试三对角线矩阵函数
	tridiagonalMatrix<int> x(20);
	x.set(1, 1, 22);
	x.set(5, 5, 44);
	x.set(8, 5, 0);
	x.set(7, 8, 55);
	cout << x.get(7, 8) << endl;
	cout << x.get(5, 5) << endl;
	cout << x.get(1, 1) << endl;
	cout << x.get(10, 1) << endl;
	cout << x.get(1, 5) << endl;
#endif

#if 0
	//测试对角矩阵的函数
	diagonaMatrix<int>x(20);
	x.set(1, 1, 22);
	x.set(5, 5, 44);
	x.set(8, 5, 0);
	cout << x.get(5, 5) << endl;
	cout << x.get(1, 1) << endl;
	cout << x.get(10, 1) << endl;
}
#endif