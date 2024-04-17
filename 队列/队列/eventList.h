#pragma once
#include"myExceptions.h"
class eventList
{
public:
	eventList(int theNumMachines, int theLargeTime)
	{
		//为m台机器，初始化其完成时间
		if (theNumMachines < 1)
			throw illegalParameterVaule("number of machines must be >= 1");
		numMachines = theNumMachines;
		finishTime = new int[numMachines + 1];
		//所有机器都空闲，用大的完成时间初始化
		for (int i = 1; i <= numMachines; i++)
			finishTime[i] = theLargeTime;
	}

		//返回值是处理下一项工序的机器
	int nextEventMachine()
	{
		//寻找完成时间最早的机器
		int p = 1;
		int t = finishTime[1];
		for (int i = 2; i <= numMachines; i++)
		{
			if (finishTime[i] < t)
			{
				//机器i完成时间更早
				p = i;
				t = finishTime[i];
			}
		}
		return p;
	}

	//返回机器p完成其活动工序的时间
	int nextEvenTime(int theMachine)
	{
		return finishTime[theMachine];
	}

	//用来设置完成一个工序要多少时间
	void setFinishTime(int theMachine, int theTime)
	{
		finishTime[theMachine] = theTime;
	}

private:
	int* finishTime;//完成时间的数组,表示每台机器完成的时间
	int numMachines;//机器数量
};