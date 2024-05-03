#include"linkedBinaryTree.h"
#include<iostream>
#include"booster.h"
#include"unionFinWithTrees.h"
#include"unionFinWithweightingRule.h"
using namespace std;
int main()
{
	//测试基于树结构根据重量规则进行合并和用路径紧缩来查找一个元素的并查集
	unionFinWithWeightingRule uFR;
	uFR.initialize(10);
	uFR.unite(1, 2);
	uFR.unite(3, 4);
	uFR.unite(1, 3);
	cout << "find(1) = " << uFR.find(1) << " find(2) = " << uFR.find(2) << endl;
	cout << "find(3) = " << uFR.find(3) << " find(4) = " << uFR.find(4) << endl;
	cout << "find(5) = " << uFR.find(5) << " find(6) = " << uFR.find(6) << endl;

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