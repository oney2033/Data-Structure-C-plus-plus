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
	//���Թ������溯��
	machinesShop machine;
	machine.inputData();
	machine.startShop();
	machine.simulate();
	machine.outputStatistics();

#if 0
	//����ͼԪʶ�����Ĺ���
	CompontLabeling labeling;
	labeling.inputImage();
	labeling.labelComponts();
	labeling.outputImage();
#endif

#if 0
	//����Ѱ����̵ĵ�·����·��
	wrieRouter w;
	w.inputData();
	if (w.findPath())
		w.outputPath();
	else
		std::cout << "There is no wire path" << std::endl;
#endif
#if 0
	//���Գ��������������ʵ��
	railroadWithQueue rail;
	int p[] = { 0, 3, 6, 9, 2, 4, 7, 1, 8, 5 };
	cout << "Input permutation is 369247185" << endl;
	rail.railroad(p, 9, 3);
#endif

#if 0
	//�����������
	linkedqueue<int> q;
	// ���һЩԪ��
	q.push(1);
	cout << "Queue back is " << q.back() << endl;
	q.push(2);
	cout << "Queue back is " << q.back() << endl;
	q.push(3);
	cout << "Queue back is " << q.back() << endl;
	q.push(4);
	cout << "Queue back is " << q.back() << endl;

	cout << "Queue should be 1234, front to back" << endl;

	// ����empty������size������pop����
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
	//�����������
	arrayqueue<int>q(4);
	//����push������back����
	q.push(1);
	cout << "Queue rear is " << q.back() << endl;
	q.push(2);
	cout << "Queue rear is " << q.back() << endl;
	q.push(3);
	cout << "Queue rear is " << q.back() << endl;
	q.push(4);
	cout << "Queue rear is " << q.back() << endl;

	cout << "Queue should be 1234, front to rear" << endl;

	//����empty������size����
	if (q.empty())
		cout << "The queue is empty" << endl;
	else
		cout << "The queue is not empty" << endl;

	cout << "The queue size is " << q.size() << endl;

	//����front������pop����
	while (!q.empty())
	{
		cout << "Queue front is " << q.front() << endl;
		q.pop();
		cout << "Popped front element" << endl;
	}
	//�����쳣��
	try { q.pop(); }
	catch (queueempty message)
	{
		cout << "Last pop failed" << endl;
		message.output();
	}
	//����һ��ѭ�����в�ִ������ӱ�
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
	// ����empty��size����
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