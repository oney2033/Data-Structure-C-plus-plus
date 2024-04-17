#pragma once
#include"task.h"
#include"arrayqueue.h"
//每项任务都有一个工序表，每道工序按表中的顺序执行，可以将工序表描述成一个队列。
//为了计算一项任务等待时间，需要知道该任务的长度和完成时间，完成时间通过计时确定，任务长度为个工序时间之和。
struct job
{
	arrayqueue<task> taskQ;    //任务的工序
	int lenght;					//该任务的总长度
	int arrivalTime;			//到达当前队列的时间
	int id;						//任务标识符

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
		//删除任务的下一道工序，返回它的时间，更新长度
		int theTime = taskQ.front().time;
		taskQ.pop();
		lenght += theTime;
		return theTime;
	}
};