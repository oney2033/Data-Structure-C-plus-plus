#pragma once
#include"arrayqueue.h"
#include"job.h"
struct machine
{
	arrayqueue<job*>jobQ; //本机器的等待处理的任务队列
	int changeTime;	      //本机器的转换时间
	int totalWait;		  //本机器的总体延时
	int numTask;		  //本机器处理的工序数量
	job* activejob;		  //本机器当前处理的任务

	machine()
	{
		totalWait = 0;
		numTask = 0;
		activejob = NULL;
	}

};