#include"arrayList.h"
#include"LinearLish.h"
#include"myExceptions.h"
#include<iostream>
using namespace std;
int main()
{
	//测试构造数据
	LinearLish<double>* x = new arrayList<double>(20);
	arrayList<int>y(2), z;

	//测试获取容量的函数
	std::cout 
		<< "Capacity of x, y, z = "
		<< ((arrayList<double>*)x)->capacity() << ","
		<< y.capacity() << ","
		<< z.capacity() << std::endl;

	//测试数组内多少个元素
	std::cout
		<< "Initial size of,x, y, z = "
		<< x->size() << ","
		<< y.size() << ","
		<< z.size() << std::endl;

	//测试判空函数
	if (x->empty())std::cout << "x is empty" << std::endl;
	else std::cout << "x is not empty" << std::endl;
	if (y.empty())std::cout << "y is empty" << std::endl;
	else std::cout << "y is not empty" << std::endl;

	//测试插入函数
	y.insert(0, 2);
	y.insert(1, 6);
	y.insert(0, 1);
	y.insert(2, 4);
	y.insert(3, 5);
	y.insert(2, 3);
	std::cout << "Inserted 6 integers,list y should be 1 2 3 4 5 6" << std::endl;
	std::cout << "Size of y = " << y.size() << std::endl;
	std::cout << "Capacity of y = " << y.capacity() << std::endl;
	if (y.empty())std::cout << "y is empty" << std::endl;
	else std::cout << "y is not empty" << std::endl;
	y.output(std::cout);
	std::cout << std::endl << "Testing overloaded <<" << std::endl;
	std::cout << y << std::endl;

	//测试按值查找第一次出现该值的下标
	int index = y.indexOf(4);
	if (index < 0)std::cout << "4 not found" << std::endl;
	else std::cout << "The index of 4 is " << index << std::endl;

	index = y.indexOf(7);
	if (index < 0)std::cout << "7 not found" << std::endl;
	else std::cout << "The index of 7 is " << index << std::endl;

	//测试按下标获得元素
	std::cout << "Element with index 0 is " << y.get(0) << std::endl;
	std::cout << "Element with index 3 is " << y.get(3) << std::endl;

	//测试删除函数
	y.erase(1);
	cout << "Element 1 erased" << endl;
	cout << "The list is " << y << endl;
	y.erase(2);
	cout << "Element 2 erased" << endl;
	cout << "The list is " << y << endl;

	cout << "Size of y = " << y.size() << endl;
	cout << "Capacity of y = " << y.capacity() << endl;
	if (y.empty()) cout << "y is empty" << endl;
	else cout << "y is not empty" << endl;

	//测试捕捉异常
	try { y.insert(-3, 0); }
	catch (illegalIndex e)
	{
		cout << "Illegal index exception" << endl;
		cout << "Insert index must be between 0 and list size" << endl;
		e.outputMessage();
	}

	// 测试拷贝构造函数
	arrayList<int> w(y);
	y.erase(0);
	y.erase(0);
	cout << "w should be old y, new y has first 2 elements removed" << endl;
	cout << "w is " << w << endl;
	cout << "y is " << y << endl;

	// 再执行几次插入，为了好玩
	y.insert(0, 4);
	y.insert(0, 5);
	y.insert(0, 6);
	y.insert(0, 7);
	cout << "y is " << y << endl;
	return 0;

}