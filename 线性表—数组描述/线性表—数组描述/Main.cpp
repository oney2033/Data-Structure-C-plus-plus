#include"arrayList.h"
#include"LinearLish.h"
#include"myExceptions.h"
#include<iostream>
#include<numeric>
using namespace std;
int main()
{
	//���Ե�����
	//����һ������
	arrayList<int>t(2);
	t.insert(0, 2);
	t.insert(1, 6);
	t.insert(0, 1);
	t.insert(2, 4);
	t.insert(3, 5);
	t.insert(2, 3);
	cout << "Inserted 6 integers, list t should be 1 2 3 4 5 6" << endl;
	cout << "Size of t = " << t.size() << endl;
	cout << "Capacity of t = " << t.capacity() << endl;

	//���Ե������Ĺ���i++��++i
	cout << "Ouput using forward iterators pre and post ++" << endl;
	for (arrayList<int>::iterator i = t.begin(); i != t.end(); i++)
	{
		cout << *i << " ";
	}
	cout << endl;
	for (arrayList<int>::iterator i = t.begin(); i != t.end(); ++i)
	{
		cout << *i << " ";
	}
	cout << endl;

	//���Ե������Ĺ���i--��--i
	cout << "Ouput using backward iterators pre and post --" << endl;
	for (arrayList<int>::iterator i = t.end(); i != t.begin(); cout << *(--i) << " ");
	cout << endl;
	for (arrayList<int>::iterator i = t.end(); i != t.begin();)
	{
		i--;
		cout << *i << " ";
		//�б��ڵ�Ԫ�ؼ�1
		*i += 1;
	}
	cout << endl;
	//�����1����б�
	cout << "Incremented by 1 list is " << t << endl;

	//����һЩSTL�㷨
	std::reverse(t.begin(), t.end());
	cout << "The reversed list is " << t << endl;
	int sum = std::accumulate(t.begin(), t.end(), 0);
	cout << "The sum of the elements is " << sum << endl;

	//���Էǵ�����
	//���Թ�������
	LinearLish<double>* x = new arrayList<double>(20);
	arrayList<int>y(2), z;

	//���Ի�ȡ�����ĺ���
	std::cout
		<< "Capacity of x, y, z = "
		<< ((arrayList<double>*)x)->capacity() << ","
		<< y.capacity() << ","
		<< z.capacity() << std::endl;

	//���������ڶ��ٸ�Ԫ��
	std::cout
		<< "Initial size of,x, y, z = "
		<< x->size() << ","
		<< y.size() << ","
		<< z.size() << std::endl;

	//�����пպ���
	if (x->empty())std::cout << "x is empty" << std::endl;
	else std::cout << "x is not empty" << std::endl;
	if (y.empty())std::cout << "y is empty" << std::endl;
	else std::cout << "y is not empty" << std::endl;

	//���Բ��뺯��
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

	//���԰�ֵ���ҵ�һ�γ��ָ�ֵ���±�
	int index = y.indexOf(4);
	if (index < 0)std::cout << "4 not found" << std::endl;
	else std::cout << "The index of 4 is " << index << std::endl;

	index = y.indexOf(7);
	if (index < 0)std::cout << "7 not found" << std::endl;
	else std::cout << "The index of 7 is " << index << std::endl;

	//���԰��±���Ԫ��
	std::cout << "Element with index 0 is " << y.get(0) << std::endl;
	std::cout << "Element with index 3 is " << y.get(3) << std::endl;

	//����ɾ������
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

	//���Բ�׽�쳣
	try { y.insert(-3, 0); }
	catch (illegalIndex e)
	{
		cout << "Illegal index exception" << endl;
		cout << "Insert index must be between 0 and list size" << endl;
		e.outputMessage();
	}

	// ���Կ������캯��
	arrayList<int> w(y);
	y.erase(0);
	y.erase(0);
	cout << "w should be old y, new y has first 2 elements removed" << endl;
	cout << "w is " << w << endl;
	cout << "y is " << y << endl;

	// ��ִ�м��β��룬Ϊ�˺���
	y.insert(0, 4);
	y.insert(0, 5);
	y.insert(0, 6);
	y.insert(0, 7);
	cout << "y is " << y << endl;
	return 0;


}