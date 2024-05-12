#include<iostream>
#include"minHeap.h"
#include"maxHeapSort.h"
#include"lptSchedule.h"

using namespace std;
int main()
{
	//测试 m 台机器的lpt调度
	jobNode a[11];
	int n = 10;
	for (int i = 1; i <= n; i++)
	{
		a[i].setid(i);
		int time = 2 * i * i;
		a[i].setTime(time);
	}
	makeSchedule(a, 10, 3);
#if 0
	//测试最小根堆
	// 测试构造函数和push函数
	minHeap<int> h(4);
	h.push(10);
	h.push(20);
	h.push(5);

	cout << "Heap size is " << h.size() << endl;
	cout << "Elements in array order are" << endl;
	cout << h << endl;

	h.push(15);
	h.push(30);

	cout << "Heap size is " << h.size() << endl;
	cout << "Elements in array order are" << endl;
	cout << h << endl;

	// 测试top函数和pop函数
	cout << "The min element is " << h.top() << endl;
	h.pop();
	cout << "The min element is " << h.top() << endl;
	h.pop();
	cout << "The min element is " << h.top() << endl;
	h.pop();
	cout << "Heap size is " << h.size() << endl;
	cout << "Elements in array order are" << endl;
	cout << h << endl;

	// 测试初始化小根堆
	int z[10];
	for (int i = 1; i < 10; i++)
		z[i] = 10 - i;
	h.initial(z, 9);
	cout << "Elements in array order are" << endl;
	cout << h << endl;
	return 0;
#endif
}