#pragma once
template<class T>
class queue
{
public:
	virtual ~queue(){}
	virtual bool empty()const = 0;//判断队列是否为空
	virtual int size()const = 0;//返回队列内元素个数
	virtual T& front() = 0;//返回头元素的引用
	virtual T& back() = 0;//返回尾元素的引用
	virtual void pop() = 0;//删除首元素
	virtual void push(const T& theelement) = 0;//把元素element加入队尾
};