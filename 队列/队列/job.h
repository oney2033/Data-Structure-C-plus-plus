#pragma once
#include"task.h"
#include"arrayqueue.h"
//ÿ��������һ�������ÿ�����򰴱��е�˳��ִ�У����Խ������������һ�����С�
//Ϊ�˼���һ������ȴ�ʱ�䣬��Ҫ֪��������ĳ��Ⱥ����ʱ�䣬���ʱ��ͨ����ʱȷ�������񳤶�Ϊ������ʱ��֮�͡�
struct job
{
	arrayqueue<task> taskQ;    //����Ĺ���
	int lenght;					//��������ܳ���
	int arrivalTime;			//���ﵱǰ���е�ʱ��
	int id;						//�����ʶ��

	job(int theId = 0)
	{
		id = theId;
		lenght = 0;
		arrivalTime = 0;
	}
	
	void addTask(int themachine, int thetime)
	{
		task theTask(themachine, thetime);
		taskQ.push(theTask);
	}

	int removeNextTask()
	{
		//ɾ���������һ�����򣬷�������ʱ�䣬���³���
		int theTime = taskQ.front().time;
		taskQ.pop();
		lenght += theTime;
		return theTime;
	}
};