#pragma once
template<class T>
class queue
{
public:
	virtual ~queue(){}
	virtual bool empty()const = 0;//�ж϶����Ƿ�Ϊ��
	virtual int size()const = 0;//���ض�����Ԫ�ظ���
	virtual T& front() = 0;//����ͷԪ�ص�����
	virtual T& back() = 0;//����βԪ�ص�����
	virtual void pop() = 0;//ɾ����Ԫ��
	virtual void push(const T& theelement) = 0;//��Ԫ��element�����β
};