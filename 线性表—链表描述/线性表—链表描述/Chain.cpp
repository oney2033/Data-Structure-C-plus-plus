#include"Chain.h"
#include<iostream>
#include"LinearLish.h"
#include<numeric>
#include"StudentRecord.h"
#include"StudentRecord4.h"
using namespace std;

inline int f1(StudentRecord4& s) { return s.exam1; }
inline int f2(StudentRecord4& s) { return s.exam2; }
inline int f3(StudentRecord4& s)
{
	return s.exam1 + s.exam2 + s.exam3;
}
int main()
{	
	//Ͱ���򣬷���chain������
	studentRecord s;
	chain<studentRecord>theChain;
	for (int i = 1; i <= 20; i++)
	{
		s.score = i / 2;
		s.name = new string(s.score, 'a');
		theChain.insert(0, s);
	}
	cout << "The unsorted chain is" << endl;
	cout << "  " << theChain << endl;
	theChain.binSort(10);
	cout << "The sorted chain is" << endl;
	cout << "  " << theChain << endl;

	//�����еĽڵ��������,�����Ϊ value��theElement��
	StudentRecord4 x;
	chain<StudentRecord4>basesort;
	for (int i = 1; i <= 20; i++)
	{
		x.exam1 = i / 2;
		x.exam1 = i / 2;
		x.exam2 = 20 - i;
		x.exam3 = rand() % 100;
		x.name = i;
		basesort.insert(0, x);
	}
	basesort.binSort(10, f1);
	cout << "Sort on exam 1" << endl;
	cout << "  " << basesort << endl;
	basesort.binSort(20, f2);
	cout << "Sort on exam 2" << endl;
	cout << "  " << basesort << endl;
	basesort.binSort(130, f3);
	cout << "Sort on sum of exams" << endl;
	cout << "  " << basesort << endl;

}


//Ͱ����û�з���chain������
#if 0
void binSort(chain<studentRecord>& thechain, int range)
{
	//����������,��ʼ������
	chain<studentRecord>* bin;
	bin = new chain<studentRecord>[range + 1];

	//��ѧ����¼������ַ���������
	int	numberOfElements = thechain.size();
	for (int i = 1; i <= numberOfElements; i++)
	{
		studentRecord x = thechain.get(0);
		thechain.erase(0);
		bin[x.score].insert(0, x);
	}

	//���������ռ�Ԫ��
	for (int j = range; j >= 0; j--)
	{
		while (!bin[j].empty())
		{
			studentRecord x = bin[j].get(0);
			bin[j].erase(0);
			thechain.insert(0, x);
		}
	}
	delete[] bin;

}
int main()
{
	studentRecord s;
	chain<studentRecord> c;
	for (int i = 1; i <= 20; i++)
	{
		s.score = i / 2;
		s.name = new string(s.score, 'a');
		c.insert(0, s);
	}
	cout << "The unsorted chain is" << endl;
	cout << "  " << c << endl;
	binSort(c, 10);
	cout << "The sorted chain is" << endl;
	cout << "  " << c << endl;
}
#endif

#if 0
//����������
int main()
{
	// ��������
	chain<int> y;
	y.insert(0, 2);
	y.insert(1, 6);
	y.insert(0, 1);
	y.insert(2, 4);
	y.insert(3, 5);
	y.insert(2, 3);
	cout << "Inserted 6 integers, list y should be 1 2 3 4 5 6" << endl;
	cout << "Size of y = " << y.size() << endl;

	// ���Ե�����
	cout << "Ouput using forward iterators pre and post ++" << endl;
	for (chain<int>::iterator i = y.begin();
		i != y.end(); i++)
		cout << *i << "  ";
	cout << endl;
	for (chain<int>::iterator i = y.begin();
		i != y.end(); ++i)
	{
		cout << *i << "  ";
		*i += 1;
	}
	cout << endl;

	cout << "Incremented by 1 list is " << y << endl;

	// ����STL�㷨
	int sum = std::accumulate(y.begin(), y.end(), 0);
	cout << "The sum of the elements is " << sum << endl;

	return 0;
}
#endif

#if 0
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
#endif