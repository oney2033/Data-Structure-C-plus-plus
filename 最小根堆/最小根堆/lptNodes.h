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
	int id,		//�����id
		time;	//������Ҫ��ʱ��
};

class machineNode
{
	friend void makeSchedule(jobNode*, int, int);
public:
	machineNode(int theId = 0, int theAvail = 0)
		:id(theId), avail(theAvail){}
	operator int()const { return avail; }
private:
	int id,		//������id
		avail;	//����ʲôʱ�����
};