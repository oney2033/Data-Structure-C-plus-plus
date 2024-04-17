#pragma once
#include<iostream>
#include"task.h"
#include"job.h"
#include"machine.h"
#include"eventList.h"
#include"myExceptions.h"
using namespace std;
class machinesShop
{
public:
	//输入工厂数据
	void inputData()
	{
		cout << "Enter number of machines and jobs " << endl;
		cin >> numMachines >> numJobs;
		if (numMachines < 1 || numJobs < 1)
			throw illegalParameterVaule("number of machin and job must be >=1");

		//生成事件和机器队列
		eList = new eventList(numMachines, largeTime);
		mArray = new machine[numMachines + 1];

		//输入机器的转换时间
		cout << "Enter change-over time for machines" << endl;
		int ct;
		for (int j = 1; j <= numMachines; j++)
		{
			cin >> ct;
			if (ct < 0)
				throw illegalParameterVaule("change over time must >=0");
			mArray[j].changeTime = ct;
		}
		//输入任务
		job* theJob;
		int numTasks, firstMachine, theMachin, theTaskTime;
		for (int i = 1; i <= numJobs; i++)
		{
			cout << "Enter number of tasks for job" << i << endl;
			cin >> numTasks;
			firstMachine = 0;//第一道工序的机器
			if (numTasks < 1)
				throw illegalParameterVaule("each job must hava > 1 task");
			//生成任务
			theJob = new job(i);
			cout << "Enter the tasks (machine,time)"
				<< " in process order" << endl;
			for (int j = 1; j <= numTasks; j++)
			{
				//读取任务i的工序
				cin >> theMachin >> theTaskTime;
				if (theMachin < 1 || theMachin > numMachines || theTaskTime < 1)
					throw illegalParameterVaule("bad machine number or task time");
				if (j == 1)
					firstMachine = theMachin;//处理任务的第一台机器
				theJob->addTask(theMachin, theTaskTime);
			}
			mArray[firstMachine].jobQ.push(theJob);
		}
	}

	//启动仿真
	void startShop()
	{
		//在每一台机器上装载其第一个任务
		for (int p = 1; p <= numMachines; p++)
			changeStart(p);
	}


	//修改机器状态,机器theMachine上的工序完成了，调度下一道工序
	job* changeStart(int theMachine)
	{//返回值是机器theMachine上刚刚完成的任务
		job* lastJob;
		if (mArray[theMachine].activejob == NULL)
		{//处于空闲或转换状态
			lastJob = NULL;
			//等待，准备处理新的任务
			if (mArray[theMachine].jobQ.empty())//没有等待执行的任务
			{
				eList->setFinishTime(theMachine, largeTime);
			}
			else
			{//从队列中提取任务，在机器上执行
				mArray[theMachine].activejob = mArray[theMachine].jobQ.front();
				mArray[theMachine].jobQ.pop();
				mArray[theMachine].totalWait += timeNow - mArray[theMachine].activejob->arrivalTime;
				mArray[theMachine].numTask++;
				int t = mArray[theMachine].activejob->removeNextTask();
				eList->setFinishTime(theMachine, timeNow + t);
			}
		}
		else
		{
			//在机器theMachine上刚刚完成一道工序
			//设置转换时间
			lastJob = mArray[theMachine].activejob;
			mArray[theMachine].activejob = NULL;
			eList->setFinishTime(theMachine, timeNow + mArray[theMachine].changeTime);
		}
		return lastJob;
	}

	
	//把下一项任务移至下一道工序对应的机器
	bool moveToNextMachine(job* theJob)
	{
		//如果任务已经完成，则返回false
		if (theJob->taskQ.empty())
		{
			//没有下一道工序
			cout << "Job " << theJob->id << " has completed at "
				<< timeNow << " Total wait was "
				<< (timeNow - theJob->lenght) << endl;
			return false;
		}
		else
		{
			//任务theJob有下一道工序
			//确定执行下一道工序的机器
			int p = theJob->taskQ.front().machine;
			//把任务插入机器p的等待任务队列
			mArray[p].jobQ.push(theJob);
			theJob->arrivalTime = timeNow;
			//如果机器p空闲，则改变它的状态
			if (eList->nextEvenTime(p) == largeTime)
				changeStart(p);

			return true;
		}
	}

	//处理所有未处理的任务
	void simulate()
	{
		while (numJobs > 0)
		{
			int nextToFinish = eList->nextEventMachine();
			timeNow = eList->nextEvenTime(nextToFinish);
			//改变机器nextToFinish上的任务
			job* thejob = changeStart(nextToFinish);
			//把任务thejob调度到下一台机器
			//如果任务thejob完成，则减少任务数
			if (thejob != NULL && !moveToNextMachine(thejob))
				numJobs--;
		}
	}
	
	//输出每台机器的等待时间
	void outputStatistics()
	{
		cout << "Finish time = " << timeNow << endl;
		for (int p = 1; p <= numMachines; p++)
		{
			cout << "Machine " << p << " completed "
				<< mArray[p].numTask << " tasks" << endl;
			cout << "The total wait time was "
				<< mArray[p].totalWait << endl;
			cout << endl;
		}
	}
private:
	int timeNow;	 //当前时间
	int numMachines; //机器数量
	int numJobs;     //任务数量
	eventList* eList; //事件表的指针
	machine* mArray;  //机器数组
	int largeTime = 10000;//在这个时间之前所有机器都已完成工序
};