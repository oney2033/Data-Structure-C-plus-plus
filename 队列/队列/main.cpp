#include"arrayqueue.h"
#include<iostream>
#include"linkedqueue.h"
#include"railroadwWthQueue.h"
#include"wrieRouter.h"
#include"CompontLabeling.h"
#include"machinesShop.h"
using namespace std;
int main()
{
	//测试工厂仿真函数
	machinesShop machine;
	machine.inputData();
	machine.startShop();
	machine.simulate();
	machine.outputStatistics();

#if 0
	//测试图元识别函数的功能
	CompontLabeling labeling;
	labeling.inputImage();
	labeling.labelComponts();
	labeling.outputImage();
#endif

#if 0
	//测试寻找最短的电路布线路径
	wrieRouter w;
	w.inputData();
	if (w.findPath())
		w.outputPath();
	else
		std::cout << "There is no wire path" << std::endl;
#endif
#if 0
	//测试车厢重排数组队列实现
	railroadWithQueue rail;
	int p[] = { 0, 3, 6, 9, 2, 4, 7, 1, 8, 5 };
	cout << "Input permutation is 369247185" << endl;
	rail.railroad(p, 9, 3);
#endif

#if 0
	//测试链表队列
	linkedqueue<int> q;
	// 添加一些元素
	q.push(1);
	cout << "Queue back is " << q.back() << endl;
	q.push(2);
	cout << "Queue back is " << q.back() << endl;
	q.push(3);
	cout << "Queue back is " << q.back() << endl;
	q.push(4);
	cout << "Queue back is " << q.back() << endl;

	cout << "Queue should be 1234, front to back" << endl;

	// 测试empty函数和size函数和pop函数
	if (q.empty())
		cout << "The queue is empty" << endl;
	else
		cout << "The queue is not empty" << endl;
	cout << "The queue size is " << q.size() << endl;

	while (!q.empty())
	{
		cout << "Queue front is " << q.front() << endl;
		q.pop();
		cout << "Popped front element" << endl;
	}

	try { q.pop(); }
	catch (queueempty message)
	{
		cout << "Last pop failed" << endl;
		message.output();
	}
#endif

#if 0
	//测试数组队列
	arrayqueue<int>q(4);
	//测试push函数和back函数
	q.push(1);
	cout << "Queue rear is " << q.back() << endl;
	q.push(2);
	cout << "Queue rear is " << q.back() << endl;
	q.push(3);
	cout << "Queue rear is " << q.back() << endl;
	q.push(4);
	cout << "Queue rear is " << q.back() << endl;

	cout << "Queue should be 1234, front to rear" << endl;

	//测试empty函数和size函数
	if (q.empty())
		cout << "The queue is empty" << endl;
	else
		cout << "The queue is not empty" << endl;

	cout << "The queue size is " << q.size() << endl;

	//测试front函数和pop函数
	while (!q.empty())
	{
		cout << "Queue front is " << q.front() << endl;
		q.pop();
		cout << "Popped front element" << endl;
	}
	//测试异常类
	try { q.pop(); }
	catch (queueempty message)
	{
		cout << "Last pop failed" << endl;
		message.output();
	}
	//创建一个循环队列并执行数组加倍
	arrayqueue<int> r(4);
	r.push(1);
	r.push(2);
	r.push(3);
	r.pop();
	r.pop();
	r.push(4);
	r.push(5);
	r.push(6);
	r.push(7);
	cout << "Queue should be 34567, front to rear" << endl;
	// 测试empty和size函数
	if (r.empty())
		cout << "The queue is empty" << endl;
	else
		cout << "The queue is not empty" << endl;

	cout << "The queue size is " << r.size() << endl;

	while (!r.empty())
	{
		cout << "Queue front is " << r.front() << endl;
		r.pop();
		cout << "Popped front element" << endl;
	}
#endif

}