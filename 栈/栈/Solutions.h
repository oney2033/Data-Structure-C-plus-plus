#pragma once
#include"arraystack.h"
#include<iostream>
#include<string>
#include"myExceptions.h"
#include"make2Darray.h"
class Solutions
{
	//迷宫老鼠,寻找迷宫路径，用栈实现
private:
	struct position
	{
		int	row, col;
		operator int()const { return row; }
	};
	arraystack<position>* path;
	int** maze, //迷宫的内部构造
		size;  //存储迷宫的行和列的大小
public:
	bool findpath()
	{
		//寻找一条从(1,1)到达出口(size,size)的路径,存在path里
		 path = new arraystack<position>;
		//初始化偏移量
		position offset[4];
		offset[0].row = 0; offset[0].col = 1;   // right
		offset[1].row = 1; offset[1].col = 0;   // down
		offset[2].row = 0; offset[2].col = -1;  // left
		offset[3].row = -1; offset[3].col = 0;  // up

		//初始化迷宫周围的障碍墙
		for (int i = 0; i <= size + 1; i++)
		{
			maze[0][1] = maze[size + 1][i] = 1;//上下的墙
			maze[i][0] = maze[i][size + 1] = 1;//左右的墙
		}

		position here;
		here.row = 1;
		here.col = 1;
		maze[1][1] = 1;//设置为1，防止回到入口
		int option = 0;//下一步要移动的方向
		int lastOption = 3;//最后要移动的方向
		
		//搜索一条路径
		while (here.row != size || here.col != size)
		{
			//没有到达出口
			//找到要移动到相邻的一步
			int r, c;
			while (option <= lastOption)
			{
				r = here.row + offset[option].row;
				c = here.col + offset[option].col;
				if (maze[r][c] == 0)break;
				option++; //下一个选择
			}

			//相邻的一步是否能到达出口
			if (option <= lastOption)
			{
				//移动到maze[r][c]
				path->push(here);
				here.row = r;
				here.col = c;
				maze[r][c] = 1;//走过的设置为1，防止重复访问
				option = 0;
			}
			else
			{
				//没有附近的路可以走，返回
				if (path->empty())return false;
				position next = path->top();
				path->pop();
				//判断移动的方向，当行相等时，上下移动，当列相等时，左右移动
				if (next.row == here.row)
					option = 2 + next.col - here.col;
				else option = 3 + next.row - here.row;
				here = next;
			}
		}
		return true;
	}
	//输入迷宫
	void inputMaze()
	{
		std::cout << "Enter maze size" << std::endl;
		std::cin >> size;
		make2Darray(maze, size + 2, size + 2);
		std::cout << "Enter maze in row major order" << std::endl;
		for (int i = 1; i <= size; i++)
			for (int j = 1; j <= size; j++)
				std::cin >> maze[i][j];
	}
	//打印路径
	void outputPath()
	{
		//路径存在
		std::cout << "The path is" << std::endl;
		position here;
		while (!path->empty())
		{
			here = path->top();
			path->pop();
			std::cout << here.row << ' ' << here.col << std::endl;
		}
	}

public:
	//离线等价类问题
	void equivalence()
	{
		int n, //元素个数
			r; //关系个数
		std::cout << "Enter number of elements" << std::endl;
		std::cin >> n;
		if (n < 2)
		{
			std::ostringstream s;
			s << "Too few elements";
			throw illegalParameterValue(s.str());
			
		}
		std::cout << "Enter number of relations" << std::endl;
		std::cin >> r;
		if (r < 1)
		{
			std::ostringstream s;
			s << "Too few relations";
			throw illegalParameterValue(s.str());
		}
		//建立空栈组成的数组，stack[0]不用
		arraystack<int>* list = new arraystack<int>[n + 1];
		//输入r个关系，存储在表中
		int a, b;//(a,b)是一个关系
		for (int i = 1; i <= r; i++)
		{
			std::cout << "Enter next relation/pair" << std::endl;
			std::cin >> a >> b;
			list[a].push(b);
			list[a].push(a);
		}
		//初始化以输出等价类
		arraystack<int>unprocessedList;
		bool* out = new bool[n + 1];
		for (int i = 1; i <= n; i++)
			out[i] = false;

		//输出等价类
		for (int i = 1; i <= n; i++)
		{
			if (!out[i])
			{
				//启动一个新类
				std::cout << "Next class is " << i << " ";
				out[i] = true;
				unprocessedList.push(i);
				//从unprocessedList中取类的剩余元素
				while (!unprocessedList.empty())
				{
					int j = unprocessedList.top();
					unprocessedList.pop();

					//表list[j]中的元素属于同一类
					while (!list[j].empty())
					{
						int q = list[j].top();
						list[j].pop();
						if (!out[q])//未输出
						{
							std::cout << q << " ";
							out[q] = true;
							unprocessedList.push(q);
						}
					}
				}
			}
			std::cout << std::endl;
		}
		std::cout << "End of list equivalence classes " << std::endl;
		delete[]out;
	}
public:
	//开关盒布线问题，用栈实现
	bool checkBox(int net[], int n)
	{
		//数组[0..n-1]管脚数组，用于形成网组
		//n是管脚数量

		arraystack<int>* st = new arraystack<int>(n);
		//顺时针扫描网组
		for (int i = 0; i < n; i++)
		{
			//处理管脚i
			if (!st->empty())
			{
				//检查栈的顶部管脚
				if (net[i] == net[st->top()])
				{
					st->pop();
				}
				else
				{
					st->push(i);
				}
			}
			else
			{
				st->push(i);
			}
		}
		//是否有剩余的不可布线的管脚
		if (st->empty())
		{
			//没有剩余的管脚
			std::cout << "Switch box is routable " << std::endl;
			return true;
		}
		std::cout << "Switch box is not routable " << std::endl;
		return false;
	}

	//列车车厢重排,用栈实现
private:
	arraystack<int>* track;//缓冲轨道数组
	int numberOfCars;	   //有多少个车厢
	int numberOfTracks;	   //多少个缓冲轨道
	int smallestCar;       //在缓冲轨道中编号最小的车厢
	int itsTrack;          //停靠着最小编号的车厢的缓冲轨道

public:
	bool railroad(int inputOrder[], int theNumberOfCars, int theNumberOfTracks)
	{
		//从初始顺序开始重排车厢
		//如果重排成功，返回true，否则返回false
		numberOfCars = theNumberOfCars;
		numberOfTracks = theNumberOfTracks;

		//创建用于缓冲轨道的栈
		track = new arraystack<int>[numberOfTracks + 1];

		int nextCarToOutput = 1;
		smallestCar = numberOfCars + 1;//缓冲轨道中无车厢

		//重排车厢
		for (int i = 1; i <= numberOfCars; i++)
		{
			if (inputOrder[i] == nextCarToOutput)
			{
				//将车厢inputOrder[i]直接移到出轨道
				std::cout << "Move car " << inputOrder[i]
					<< " from input track to output track" << std::endl;
				nextCarToOutput++;
				//从缓冲轨道将车厢移到出轨道
				while (smallestCar == nextCarToOutput)
				{
					outputFromHoldingTrack();
					nextCarToOutput++;
				}
			}
			else
			{
				//将车厢inputOrder[i]移动到一个缓冲轨道
				if (!putInHoldingTrack(inputOrder[i]))
				return false;
			}
		}
		return true;
	}

	void outputFromHoldingTrack()
	{
		//将编号最小的车厢从缓冲轨道移到出轨道
		//从栈listTrack中删除编号最小的车厢
		track[itsTrack].pop();
		std::cout << "Move car " << smallestCar << "from holding"
			<< "track " << itsTrack << "to output track" << std::endl;
		//检查所有的栈顶，寻找编号最小的车厢和它所属的栈itsTrack
		smallestCar = numberOfCars + 2;
		for (int i = 1; i <= numberOfTracks; i++)
		{
			if (!track[i].empty() && (track[i].top() < smallestCar))
			{
				smallestCar = track[i].top();
				itsTrack=i;
			}
		}
	}

	bool putInHoldingTrack(int c)
	{
		//将车厢c移到到一个缓冲轨道，返回false，当没有可用的缓冲车道时
		//为车厢c寻找最合适的车道，初始化
		int bestTrack = 0;//目前最合适的缓冲轨道
		int bestTop = numberOfCars + 1; //取bestTrack中顶部的车厢

		//扫描缓冲轨道
		for (int i = 1; i <= numberOfTracks; i++)
			if (!track[i].empty())
			{
				//缓冲轨道不为空
				int topCar = track[i].top();
				if (c < topCar && topCar < bestTop)
				{
					bestTop = topCar;
					bestTrack = i;
				}
			}
			else
			{
				if (bestTrack == 0)bestTrack = i;
			}
		
		if (bestTrack == 0) return false;//没有可用的轨道
		//将车厢c移动到bestTrack
		track[bestTrack].push(c);
		std::cout << "Move car " << c << " from input track "
			<< " to holding track" << bestTrack << std::endl;

		//如果需要，更新smallestCar 和itsTrack
		if (c < smallestCar)
		{
			smallestCar = c;
			itsTrack = bestTrack;
		}
		return true;
	}

	//判断括号匹配,输出第几个括号和第几个括号匹配
public:
	void printMatchedPairs(std::string expr)
	{
		arraystack<int>s;
		int length = expr.length();
		//遍历字符串，寻找左右括号
		for (int i = 0; i < length; i++)
		{
			if (expr[i] == '(')
			{
				s.push(i);
			}
			else
			{
				if (expr[i] == ')')
				{
					try
					{//从栈中尝试删除匹配的左括号
						std::cout << s.top() << ' ' << i << std::endl;
						s.pop();
					}
					catch (stackEmpty)
					{//栈为空，没有匹配的左括号
						std::cout << "No match for right parenthesis"
							<< "at" << i << std::endl;
					}
				}
			}
		}
		//遍历完字符串后，栈不为空，剩余在栈中的括号是不匹配的
		while (!s.empty())
		{
			std::cout << "No match for left parenthesis "
				<< "at " << s.top() << std::endl;
			s.pop();
		}
	}
};