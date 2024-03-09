#pragma once
#include<iostream>
//������LinearLisht
//���з��������麯��

template<class T>
class LinearLish
{
public:
	virtual ~LinearLish() {};
	virtual bool empty()const = 0;	//���б�Ϊ��ʱ����true
	virtual int size()const = 0;	//�����б���Ԫ�ص�����
	virtual T& get(int theIndex)const = 0;	//�����б�������ΪtheIndex��Ԫ��
	virtual int indexOf(const T& theElement)const = 0; //����Ԫ�����б��е�һ�γ��ֵ�λ��
	virtual void erase(int theIndex) = 0;  //ɾ������ΪtheIndex��Ԫ��
	virtual void insert(int theIndex, const T& theElement) = 0;//����Ԫ�أ�ʹ������ΪtheIndex
	virtual void output(std::ostream& out)const = 0;//���б����������
};