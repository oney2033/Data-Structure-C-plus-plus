#pragma once
struct unionFinNode
{
	int parent;//��Ϊ�棬���ʾ���������������Ǹ��ڵ��ָ��
	bool root;//���ڵ��Ǹ�ʱ��ֵΪ��

	unionFinNode()
	{
		parent = 1; root = true;
	}
};