#pragma once
#include"positon.h"
#include"make2Darray.h"
#include<iostream>
#include"arrayqueue.h"
//寻找电路布线的路径
class wrieRouter
{
public:
		//找到从起点到终点的最短路径。
		// 成功则返回 true，否则返回 false
	bool findPath()
	{
		if ((start.row == finish.row) && (start.col == finish.col))
		{
			pathLength = 0;
			return true;
		}
		//初始化偏移量
		positon offset[4];
		offset[0].row = 0; offset[0].col = 1;   // 右
		offset[1].row = 1; offset[1].col = 0;   // 下
		offset[2].row = 0; offset[2].col = -1;  // 左
		offset[3].row = -1; offset[3].col = 0;  // 上

		// 初始化网格周围的边界墙
		for (int i = 0; i <= size + 1; i++)
		{
			grid[0][i] = grid[size + 1][i] = 1;//顶部和底部
			grid[i][0] = grid[i][size + 1] = 1;//左边和右边
		}
		positon here = start;
		grid[start.row][start.col] = 2;//标记
		int numOfNbrs = 4;//一个方格的相邻位置数

		//对可到达的位置进行标记
		arrayqueue<positon>q;
		positon nbr;
		do
		{
			//给相邻位置做标记
			for (int i = 0; i < numOfNbrs; i++)
			{
				//检查相邻位置
				nbr.row = here.row + offset[i].row;
				nbr.col = here.col + offset[i].col;
				if (grid[nbr.row][nbr.col] == 0)
				{
					//对没标记的nbr做标记
					grid[nbr.row][nbr.col] = grid[here.row][here.col] + 1;
					if ((nbr.row == finish.row) && (nbr.col == finish.col))break;//标记完成
					//把后者插入队列
					q.push(nbr);
				}
			}
			//是否到达终点
			if((nbr.row == finish.row)&&
				(nbr.col == finish.col))break; //达到
			//终点不可到达，可以移到nbr吗
			if (q.empty())
				return false;   //路径不存在
			here = q.front();   //取下一个位置
			q.pop();
		} while (true);

		//构建路径
		pathLength = grid[finish.row][finish.col] - 2;
		path = new positon[pathLength];

		//从终点回溯
		here = finish;
		for (int j = pathLength - 1; j >= 0; j--)
		{
			path[j] = here;
			//寻找祖先位置
			for (int i = 0; i < numOfNbrs; i++)
			{
				nbr.row = here.row + offset[i].row;
				nbr.col = here.col + offset[i].col;
				if (grid[nbr.row][nbr.col] == j + 2)break;
			}
			here = nbr;	//移先祖先位置
		}
		return true;
	}

	//输出功能
	void outputPath()
	{
		std::cout << "The wire path is" << std::endl;
		for (int i = 0; i < pathLength; i++)
		{
			std::cout << path[i] << " " << path[i].col << std::endl;
		}
	}

	//输入功能
	void inputData()
	{
		//输入布线数据
		std::cout << "Enter grid size" << std::endl;
		std::cin >> size;

		std::cout << "Enter the start position" << std::endl;
		std::cin >> start.row >> start.col;

		std::cout << "Enter the finish positon" << std::endl;
		std::cin >> finish.row >> finish.col;
		
		//创建并输入接线网格
		make2Darray(grid, size + 2, size + 2);
		std::cout << "Enter the wiring grid in row-major order" << std::endl;
		for (int i = 1; i <= size; i++)
		{
			for (int j = 1; j <= size; j++)
				std::cin >> grid[i][j];
		}

	}


private:
	int** grid;		//2D 数组
	int size;		//网格中的行数和列数
	int pathLength; //最短导线路径长度
	arrayqueue<positon>q; //未扩展的到达位置队列
	positon start,		//开始位置
			finish;		//结束位置
	positon* path;	//最短路径
};