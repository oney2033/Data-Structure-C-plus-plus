#pragma once
//ÿ����������������ɣ�ִ�иù���Ļ���(machine)����ɸù����ʱ��(time)
struct task
{
	int machine;
	int time;

	task(int themachine = 0, int thetime = 0)
	{
		machine = themachine;
		time = thetime;
	}
};