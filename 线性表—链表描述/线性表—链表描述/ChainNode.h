#pragma once
#pragma once
template<class T>
struct chainNode
{
	//���ݳ�Ա
	T element;
	chainNode<T>* next;

	//����ʹ����this->������ʵ�������ݳ�Ա����Ϊʵ�������ݳ�Ա�͹��캯�����β�ͬ����ʹ�������﷨�������ֿ���
	chainNode() {};
	chainNode(const T& element) { this->element = element; }
	chainNode(const T& element, chainNode<T>* next)
	{
		this->element = element;
		this->next = next;
	}
};