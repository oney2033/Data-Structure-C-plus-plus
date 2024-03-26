#include"Chain.h"
#include<iostream>
#include"LinearLish.h"

//����������
int main()
{
	//���Թ��캯��
	LinearLish<double>* x = new chain<double>;
	chain<int> y, z;

	//����size����
	std::cout << "Initial size of x, y, and z = "
		<< x->size() << ","
		<< y.size() << ","
		<< z.size() << std::endl;

	//����empty����
	if (x->empty()) std::cout << "x is empty" << std::endl;
	else std::cout << "x is not empty" << std::endl;
	if (y.empty()) std::cout << "y is empty" << std::endl;
	else std::cout << "y is not empty" << std::endl;

	//����insert����
	y.insert(0, 2);
	y.insert(1, 6);
	y.insert(0, 1);
	y.insert(2, 4);
	y.insert(3, 5);
	y.insert(2, 3);
	std::cout << "Inserted 6 integers, list y should be 1 2 3 4 5 6" << std::endl;
	std::cout << "Size of y = " << y.size() << std::endl;
	if (y.empty()) std::cout << "y is empty" << std::endl;
	else std::cout << "y is not empty" << std::endl;

	//�����������
	y.output(std::cout);

	//�������������<<
	std::cout << std::endl << "Testing overloaded <<" << std::endl;
	std::cout << y << std:: endl;
	
	//����indexOf
	int index = y.indexOf(4);
	if (index < 0) std::cout << "4 not found" << std::endl;
	else std::cout << "The index of 4 is " << index << std::endl;

	//����get����
	std::cout << "Element with index 0 is " << y.get(0) << std::endl;
	std::cout << "Element with index 3 is " << y.get(3) << std::endl;

	//����erase����
	y.erase(1);
	std::cout << "Element 1 erased" << std::endl;
	std::cout << "The list is " << y << std::endl;
	y.erase(2);
	std::cout << "Element 2 erased" << std::endl;
	std::cout << "The list is " << y << std::endl;
	y.erase(0);
	std::cout << "Element 0 erased" << std::endl;
	std::cout << "The list is " << y << std::endl;

	std::cout << "Size of y = " << y.size() << std::endl;
	if (y.empty()) std::cout << "y is empty" << std::endl;
	else std::cout << "y is not empty" << std::endl;

	//���Բ�׽�쳣
	try { y.insert(-3, 0); }
	catch (illegalIndex e)
	{
		std::cout << "Illegal index exception" << std::endl;
		std::cout << "Insert index must be between 0 and list size" << std::endl;
		e.output();
	}

	//���Ը��ƹ��캯��
	chain<int> w(y);
	y.erase(0);
	y.erase(0);
	std::cout << "w should be old y, new y has first 2 elements removed" << std::endl;
	std::cout << "w is " << w << std::endl;
	std::cout << "y is " << y << std::endl;

	return 0;
}