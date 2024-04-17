#pragma once
#include"myExceptions.h"
class eventList
{
public:
	eventList(int theNumMachines, int theLargeTime)
	{
		//Ϊm̨��������ʼ�������ʱ��
		if (theNumMachines < 1)
			throw illegalParameterVaule("number of machines must be >= 1");
		numMachines = theNumMachines;
		finishTime = new int[numMachines + 1];
		//���л��������У��ô�����ʱ���ʼ��
		for (int i = 1; i <= numMachines; i++)
			finishTime[i] = theLargeTime;
	}

		//����ֵ�Ǵ�����һ���Ļ���
	int nextEventMachine()
	{
		//Ѱ�����ʱ������Ļ���
		int p = 1;
		int t = finishTime[1];
		for (int i = 2; i <= numMachines; i++)
		{
			if (finishTime[i] < t)
			{
				//����i���ʱ�����
				p = i;
				t = finishTime[i];
			}
		}
		return p;
	}

	//���ػ���p����������ʱ��
	int nextEvenTime(int theMachine)
	{
		return finishTime[theMachine];
	}

	//�����������һ������Ҫ����ʱ��
	void setFinishTime(int theMachine, int theTime)
	{
		finishTime[theMachine] = theTime;
	}

private:
	int* finishTime;//���ʱ�������,��ʾÿ̨������ɵ�ʱ��
	int numMachines;//��������
};