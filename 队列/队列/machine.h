#pragma once
#include"arrayqueue.h"
#include"job.h"
struct machine
{
	arrayqueue<job*>jobQ; //�������ĵȴ�������������
	int changeTime;	      //��������ת��ʱ��
	int totalWait;		  //��������������ʱ
	int numTask;		  //����������Ĺ�������
	job* activejob;		  //��������ǰ���������

	machine()
	{
		totalWait = 0;
		numTask = 0;
		activejob = NULL;
	}

};