#include<iostream>
#include"arraystack.h"
#include"linkedstack.h"
#include"Solutions.h"

using namespace std;
int main()
{
	Solutions solution;
	//�����Թ�����
	solution.inputMaze();
	if (solution.findpath())
		solution.outputPath();
	else
		std::cout << "No path" << std::endl;

#if 0
	//�������ߵȼ�������Ĺ���
	try
	{
	solution.equivalence();
	}
	catch (illegalParameterValue e)
	{
		e.output();
	}

	//���Կ��غв��߹���
	int b[] = { 1,2,2,1,3,3,4,4 };
	solution.checkBox(b, 8);
#endif
#if 0
	//���Գ������Ź���
	//����ǰ���һ�� 0 ����Ϊ���Ǵӳ���1��ʼ
	int a[] = {0,3,6,9,2,4,7,1,8,5 };
	if (solution.railroad(a, 9, 3))
		std::cout << "Ok" << std::endl;
	else
		std::cout << "No" << std::endl;
	
	//��������ƥ�书��
	std::string text = "(a(b(c)d)e)";
	solution.printMatchedPairs(text);
#endif
#if 0
	//��������ջ
	linkedstack<int>s;
	//���Ԫ��
	s.push(1);
	s.push(2);
	s.push(3);
	s.push(4);

	cout << "Stack should be 1234, bottom to top" << endl;

	// ����empty������size����
	if (s.empty())
		cout << "The stack is empty" << endl;
	else
		cout << "The stack is not empty" << endl;

	cout << "The stack size is " << s.size() << endl;
	while (!s.empty())
	{
		cout << "Stack top is " << s.top() << endl;
		s.pop();
		cout << "Popped top element" << endl;
	}

	try { s.pop(); }
	catch (stackEmpty message)
	{
		cout << "Last pop failed " << endl;
		message.output();
	}
#endif

#if 0
	//��������ջ
	arraystack<int>s;
	//���Ԫ��
	s.push(1);
	s.push(2);
	s.push(3);
	s.push(4);

	cout << "Stack should be 1234, bottom to top" << endl;

	// ����empty������size����
	if (s.empty())
		cout << "The stack is empty" << endl;
	else
		cout << "The stack is not empty" << endl;
	cout << "The stack size is " << s.size() << endl;
	while (!s.empty())
	{
		cout << "Stack top is " << s.top() << endl;
		s.pop();
		cout << "Popped top element" << endl;
	}	
	try { s.pop(); }
	catch (stackEmpty message)
	{
		cout << "Last pop failed " << endl;
		message.output();
	}
#endif
}