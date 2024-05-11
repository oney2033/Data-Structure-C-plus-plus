#include"linkedBinaryTree.h"
#include<iostream>
#include"booster.h"
#include"unionFinWithTrees.h"
#include"unionFinWithweightingRule.h"
#include"maxHeap.h"
#include"maxHblt.h"
#include"maxPriorityQueue.h"

using namespace std;
int main(void)
{
	//测试高度优先的最大左高树,后序遍历输出
	maxHblt<int> h, j;
	int a[6] = { 0, 7, 9, 1, 8, 11 };
	h.initialize(a, 5);
	cout << "One tree in postorder is" << endl;
	cout << "Tree size is " << h.size() << endl;
	h.output();
	int b[5] = { 0, 2, 6, 4, 9 };

	j.initialize(b, 4);
	cout << "Other tree in postorder is" << endl;
	cout << "Tree size is " << j.size() << endl;
	j.output();

	int w = h.top();
	h.pop();
	int x = h.top();
	h.pop();
	int y = h.top();
	h.pop();
	int z = h.top();
	h.pop();
	cout << "After popping four elements, the tree is" << endl;
	cout << "Tree size is " << h.size() << endl;
	h.output();
	cout << "The popped elements, in order, are" << endl;
	cout << w << "  " << x << "  " << y << "  " << z << endl;

	h.push(10);
	h.push(20);
	h.push(5);
	cout << "After pushing 10, 20 & 5, the tree is" << endl;
	cout << "Leftist tree in postorder" << endl;
	cout << "Tree size is " << h.size() << endl;
	h.output();

	h.push(15);
	h.push(30);
	h.push(2);
	cout << "After pushing 15, 30 & 15, the tree is" << endl;
	cout << "Leftist tree in postorder" << endl;
	cout << "Tree size is " << h.size() << endl;
	h.output();

	cout << "The max element is " << h.top() << endl;

	h.pop();
	cout << "Popped max element " << endl;
	cout << "Leftist tree in postorder" << endl;
	cout << "Tree size is " << h.size() << endl;
	h.output();

	x = h.top();
	h.pop();
	cout << "Popped max element " << x << endl;
	cout << "Tree size is " << h.size() << endl;
	cout << "Leftist tree in postorder" << endl;
	h.output();

	while (true)
	{// 清空
		try
		{
			x = h.top();
			h.pop();
			cout << "Popped " << x << endl;
			cout << "Tree size is " << h.size() << endl;
		}
		catch (queempty) { break; }
	}

#if 0
	//测试优先队列
	//测试构造函数和push函数
	maxHeap<int>h(4);
	h.push(10);
	h.push(20);
	h.push(5);

	cout << "Heap size is " << h.size() << endl;
	cout << "Elements in array order are" << endl;
	cout << h << endl;

	h.push(15);
	h.push(30);

	cout << "Heap size is " << h.size() << endl;
	cout << "Elements in array order are" << endl;
	cout << h << endl;

	// 测试top函数和pop函数
	cout << "The max element is " << h.top() << endl;
	h.pop();
	cout << "The max element is " << h.top() << endl;
	h.pop();
	cout << "The max element is " << h.top() << endl;
	h.pop();
	cout << "Heap size is " << h.size() << endl;
	cout << "Elements in array order are" << endl;
	cout << h << endl;

	//// 测试initialize，初始化一个非空大根堆
	int z[10];
	for (int i = 1; i < 10; i++)
		(z[i]) = i;
	h.initialize(z, 9);
	cout << "Elements in array order are" << endl;
	cout << h << endl;
	return 0;
#endif

#if 0
	//测试基于树结构根据重量规则进行合并和用路径紧缩来查找一个元素的并查集
	unionFinWithWeightingRule uFR;
	uFR.initialize(10);
	uFR.unite(1, 2);
	uFR.unite(3, 4);
	uFR.unite(1, 3);
	cout << "find(1) = " << uFR.find(1) << " find(2) = " << uFR.find(2) << endl;
	cout << "find(3) = " << uFR.find(3) << " find(4) = " << uFR.find(4) << endl;
	cout << "find(5) = " << uFR.find(5) << " find(6) = " << uFR.find(6) << endl;
#endif
#if 0
	//测试基于树结构的并查集问题解决方案
	unionFinWithTrees unionFin;
	unionFin.initialize(10);
	unionFin.unite(1, 2);
	unionFin.unite(3, 4);
	unionFin.unite(1, 3);
	cout << "find(1) = " << unionFin.find(1) << " find(2) = " << unionFin.find(2) << endl;
	cout << "find(3) = " << unionFin.find(3) << " find(4) = " << unionFin.find(4) << endl;
	cout << "find(5) = " << unionFin.find(5) << " find(6) = " << unionFin.find(6) << endl;
#endif

#if 0
	//测试放置信号放大器的功能,用后序遍历
	booster a, b;
	a.degradeFromParent = 2;
	a.degradeToleaf = 0;
	a.boosterHere = 0;
	b.degradeFromParent = 1;
	b.degradeToleaf = 0;
	b.boosterHere = 0;

	linkedBinaryTree<booster> t, u, v, w, x, y;
	u.makeTree(a, x, x);//1
	cout << "u :" ;
	u.postOrderOutput();

	v.makeTree(b, u, x);//2
	cout << "v :";
	v.postOrderOutput();

	u.makeTree(a, x, x);//3
	cout << "u :";
	u.postOrderOutput();

	w.makeTree(a, u, x);//4
	cout << "w :";
	w.postOrderOutput();

	b.degradeFromParent = 3;
	u.makeTree(b, v, w);//5
	cout << "u :";
	u.postOrderOutput();

	v.makeTree(a, x, x);//6
	cout << "v :";
	v.postOrderOutput();

	b.degradeFromParent = 3;
	w.makeTree(b, x, x);//7
	cout << "w :";
	w.postOrderOutput();

	y.makeTree(a, v, w);//8
	cout << "y :";
	y.postOrderOutput();

	w.makeTree(a, x, x);//9
	cout << "w :";
	w.postOrderOutput();

	t.makeTree(b, y, w);//10
	cout << "t :";
	t.postOrderOutput();

	b.degradeFromParent = 0;
	cout << "v :";
	v.makeTree(b, t, u);//11
	v.postOrderOutput();

	v.postOrder(placeBoosters);
	v.postOrderOutput();

	return 0;
#endif
#if 0
	//测试二叉树的遍历功能
	linkedBinaryTree<int> a, x, y, z;
	y.makeTree(1, a, a);
	z.makeTree(2, a, a);
	x.makeTree(3, y, z);
	y.makeTree(4, x, a);
	cout << "Number of nodes = ";
	cout << y.size() << endl;
	cout << "height = ";
	cout << y.height() << endl;
	cout << "Preorder sequence is ";
	y.preOrderOutput();
	cout << "Inorder sequence is ";
	y.inOrderOutput();
	cout << "Postorder sequence is ";
	y.postOrderOutput();
	cout << "Level order sequence is ";
	y.levelOrderOutput();
#endif

}