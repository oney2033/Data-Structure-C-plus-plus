#include<iostream>
#include"arraystack.h"
#include"linkedstack.h"
#include"Solutions.h"

using namespace std;
int main()
{
	Solutions solution;
	//测试迷宫老鼠
	solution.inputMaze();
	if (solution.findpath())
		solution.outputPath();
	else
		std::cout << "No path" << std::endl;

#if 0
	//测试离线等价类问题的功能
	try
	{
	solution.equivalence();
	}
	catch (illegalParameterValue e)
	{
		e.output();
	}

	//测试开关盒布线功能
	int b[] = { 1,2,2,1,3,3,4,4 };
	solution.checkBox(b, 8);
#endif
#if 0
	//测试车厢重排功能
	//数组前添加一个 0 ，因为我们从车厢1开始
	int a[] = {0,3,6,9,2,4,7,1,8,5 };
	if (solution.railroad(a, 9, 3))
		std::cout << "Ok" << std::endl;
	else
		std::cout << "No" << std::endl;
	
	//测试括号匹配功能
	std::string text = "(a(b(c)d)e)";
	solution.printMatchedPairs(text);
#endif
#if 0
	//测试链表栈
	linkedstack<int>s;
	//添加元素
	s.push(1);
	s.push(2);
	s.push(3);
	s.push(4);

	cout << "Stack should be 1234, bottom to top" << endl;

	// 测试empty函数和size函数
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
	//测试数组栈
	arraystack<int>s;
	//添加元素
	s.push(1);
	s.push(2);
	s.push(3);
	s.push(4);

	cout << "Stack should be 1234, bottom to top" << endl;

	// 测试empty函数和size函数
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