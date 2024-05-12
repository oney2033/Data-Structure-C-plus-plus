#pragma once
class jobNode
{
	friend void makeSchedule(jobNode*, int, int);
	friend void imain(void);
public:
	operator int()const { return time; }
	void setid(int& theId) { id = theId; }
	void setTime(int& theTime) { time = theTime; }
private:
	int id,		//任务的id
		time;	//任务需要的时间
};

class machineNode
{
	friend void makeSchedule(jobNode*, int, int);
public:
	machineNode(int theId = 0, int theAvail = 0)
		:id(theId), avail(theAvail){}
	operator int()const { return avail; }
private:
	int id,		//机器的id
		avail;	//机器什么时候空闲
};