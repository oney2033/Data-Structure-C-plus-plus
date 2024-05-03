#pragma once
struct unionFinNode
{
	int parent;//若为真，则表示树的重量，否则是父节点的指针
	bool root;//当节点是根时，值为真

	unionFinNode()
	{
		parent = 1; root = true;
	}
};