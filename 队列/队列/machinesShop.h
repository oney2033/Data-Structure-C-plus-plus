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
	//���빤������
	void inputData()
	{
		cout << "Enter number of machines and jobs " << endl;
		cin >> numMachines >> numJobs;
		if (numMachines < 1 || numJobs < 1)
			throw illegalParameterVaule("number of machin and job must be >=1");

		//�����¼��ͻ�������
		eList = new eventList(numMachines, largeTime);
		mArray = new machine[numMachines + 1];

		//���������ת��ʱ��
		cout << "Enter change-over time for machines" << endl;
		int ct;
		for (int j = 1; j <= numMachines; j++)
		{
			cin >> ct;
			if (ct < 0)
				throw illegalParameterVaule("change over time must >=0");
			mArray[j].changeTime = ct;
		}
		//��������
		job* theJob;
		int numTasks, firstMachine, theMachin, theTaskTime;
		for (int i = 1; i <= numJobs; i++)
		{
			cout << "Enter number of tasks for job" << i << endl;
			cin >> numTasks;
			firstMachine = 0;//��һ������Ļ���
			if (numTasks < 1)
				throw illegalParameterVaule("each job must hava > 1 task");
			//��������
			theJob = new job(i);
			cout << "Enter the tasks (machine,time)"
				<< " in process order" << endl;
			for (int j = 1; j <= numTasks; j++)
			{
				//��ȡ����i�Ĺ���
				cin >> theMachin >> theTaskTime;
				if (theMachin < 1 || theMachin > numMachines || theTaskTime < 1)
					throw illegalParameterVaule("bad machine number or task time");
				if (j == 1)
					firstMachine = theMachin;//��������ĵ�һ̨����
				theJob->addTask(theMachin, theTaskTime);
			}
			mArray[firstMachine].jobQ.push(theJob);
		}
	}

	//��������
	void startShop()
	{
		//��ÿһ̨������װ�����һ������
		for (int p = 1; p <= numMachines; p++)
			changeStart(p);
	}


	//�޸Ļ���״̬,����theMachine�ϵĹ�������ˣ�������һ������
	job* changeStart(int theMachine)
	{//����ֵ�ǻ���theMachine�ϸո���ɵ�����
		job* lastJob;
		if (mArray[theMachine].activejob == NULL)
		{//���ڿ��л�ת��״̬
			lastJob = NULL;
			//�ȴ���׼�������µ�����
			if (mArray[theMachine].jobQ.empty())//û�еȴ�ִ�е�����
			{
				eList->setFinishTime(theMachine, largeTime);
			}
			else
			{//�Ӷ�������ȡ�����ڻ�����ִ��
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
			//�ڻ���theMachine�ϸո����һ������
			//����ת��ʱ��
			lastJob = mArray[theMachine].activejob;
			mArray[theMachine].activejob = NULL;
			eList->setFinishTime(theMachine, timeNow + mArray[theMachine].changeTime);
		}
		return lastJob;
	}

	
	//����һ������������һ�������Ӧ�Ļ���
	bool moveToNextMachine(job* theJob)
	{
		//��������Ѿ���ɣ��򷵻�false
		if (theJob->taskQ.empty())
		{
			//û����һ������
			cout << "Job " << theJob->id << " has completed at "
				<< timeNow << " Total wait was "
				<< (timeNow - theJob->lenght) << endl;
			return false;
		}
		else
		{
			//����theJob����һ������
			//ȷ��ִ����һ������Ļ���
			int p = theJob->taskQ.front().machine;
			//������������p�ĵȴ��������
			mArray[p].jobQ.push(theJob);
			theJob->arrivalTime = timeNow;
			//�������p���У���ı�����״̬
			if (eList->nextEvenTime(p) == largeTime)
				changeStart(p);

			return true;
		}
	}

	//��������δ���������
	void simulate()
	{
		while (numJobs > 0)
		{
			int nextToFinish = eList->nextEventMachine();
			timeNow = eList->nextEvenTime(nextToFinish);
			//�ı����nextToFinish�ϵ�����
			job* thejob = changeStart(nextToFinish);
			//������thejob���ȵ���һ̨����
			//�������thejob��ɣ������������
			if (thejob != NULL && !moveToNextMachine(thejob))
				numJobs--;
		}
	}
	
	//���ÿ̨�����ĵȴ�ʱ��
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
	int timeNow;	 //��ǰʱ��
	int numMachines; //��������
	int numJobs;     //��������
	eventList* eList; //�¼����ָ��
	machine* mArray;  //��������
	int largeTime = 10000;//�����ʱ��֮ǰ���л���������ɹ���
};