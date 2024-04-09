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
	//����һ�����Ա�������ϡ�����
	sparseMatrix<int>a, b, c;

	//������������
	cin >> a;
	cout << "Matrix a is" << endl << a;
	cin >> b;
	cout << "Matrix b is" << endl << b;

	// ����ת��
	a.transpose(c);
	cout << "The transpose of a is" << endl << c;

	// �������
	a.add(b, c);
	cout << "The sum of a and b is" << endl << c;

}
#if 0
	//���������Ǿ���
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
	//�������Խ��߾�����
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
	//���ԶԽǾ���ĺ���
	diagonaMatrix<int>x(20);
	x.set(1, 1, 22);
	x.set(5, 5, 44);
	x.set(8, 5, 0);
	cout << x.get(5, 5) << endl;
	cout << x.get(1, 1) << endl;
	cout << x.get(10, 1) << endl;
}
#endif