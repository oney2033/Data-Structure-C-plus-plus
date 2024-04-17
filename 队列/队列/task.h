#pragma once
//每个工序由两部分组成：执行该工序的机器(machine)和完成该工序的时间(time)
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