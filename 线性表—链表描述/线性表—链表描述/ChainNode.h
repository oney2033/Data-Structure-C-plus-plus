#pragma once
#pragma once
template<class T>
struct chainNode
{
	//数据成员
	T element;
	chainNode<T>* next;

	//这里使用了this->来访问实例的数据成员，因为实例的数据成员和构造函数的形参同名，使用这种语法才能区分开来
	chainNode() {};
	chainNode(const T& element) { this->element = element; }
	chainNode(const T& element, chainNode<T>* next)
	{
		this->element = element;
		this->next = next;
	}
};