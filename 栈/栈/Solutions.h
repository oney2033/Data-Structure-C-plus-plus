#pragma once
#include"arraystack.h"
#include<iostream>
#include<string>
#include"myExceptions.h"
#include"make2Darray.h"
class Solutions
{
	//�Թ�����,Ѱ���Թ�·������ջʵ��
private:
	struct position
	{
		int	row, col;
		operator int()const { return row; }
	};
	arraystack<position>* path;
	int** maze, //�Թ����ڲ�����
		size;  //�洢�Թ����к��еĴ�С
public:
	bool findpath()
	{
		//Ѱ��һ����(1,1)�������(size,size)��·��,����path��
		 path = new arraystack<position>;
		//��ʼ��ƫ����
		position offset[4];
		offset[0].row = 0; offset[0].col = 1;   // right
		offset[1].row = 1; offset[1].col = 0;   // down
		offset[2].row = 0; offset[2].col = -1;  // left
		offset[3].row = -1; offset[3].col = 0;  // up

		//��ʼ���Թ���Χ���ϰ�ǽ
		for (int i = 0; i <= size + 1; i++)
		{
			maze[0][1] = maze[size + 1][i] = 1;//���µ�ǽ
			maze[i][0] = maze[i][size + 1] = 1;//���ҵ�ǽ
		}

		position here;
		here.row = 1;
		here.col = 1;
		maze[1][1] = 1;//����Ϊ1����ֹ�ص����
		int option = 0;//��һ��Ҫ�ƶ��ķ���
		int lastOption = 3;//���Ҫ�ƶ��ķ���
		
		//����һ��·��
		while (here.row != size || here.col != size)
		{
			//û�е������
			//�ҵ�Ҫ�ƶ������ڵ�һ��
			int r, c;
			while (option <= lastOption)
			{
				r = here.row + offset[option].row;
				c = here.col + offset[option].col;
				if (maze[r][c] == 0)break;
				option++; //��һ��ѡ��
			}

			//���ڵ�һ���Ƿ��ܵ������
			if (option <= lastOption)
			{
				//�ƶ���maze[r][c]
				path->push(here);
				here.row = r;
				here.col = c;
				maze[r][c] = 1;//�߹�������Ϊ1����ֹ�ظ�����
				option = 0;
			}
			else
			{
				//û�и�����·�����ߣ�����
				if (path->empty())return false;
				position next = path->top();
				path->pop();
				//�ж��ƶ��ķ��򣬵������ʱ�������ƶ����������ʱ�������ƶ�
				if (next.row == here.row)
					option = 2 + next.col - here.col;
				else option = 3 + next.row - here.row;
				here = next;
			}
		}
		return true;
	}
	//�����Թ�
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
	//��ӡ·��
	void outputPath()
	{
		//·������
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
	//���ߵȼ�������
	void equivalence()
	{
		int n, //Ԫ�ظ���
			r; //��ϵ����
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
		//������ջ��ɵ����飬stack[0]����
		arraystack<int>* list = new arraystack<int>[n + 1];
		//����r����ϵ���洢�ڱ���
		int a, b;//(a,b)��һ����ϵ
		for (int i = 1; i <= r; i++)
		{
			std::cout << "Enter next relation/pair" << std::endl;
			std::cin >> a >> b;
			list[a].push(b);
			list[a].push(a);
		}
		//��ʼ��������ȼ���
		arraystack<int>unprocessedList;
		bool* out = new bool[n + 1];
		for (int i = 1; i <= n; i++)
			out[i] = false;

		//����ȼ���
		for (int i = 1; i <= n; i++)
		{
			if (!out[i])
			{
				//����һ������
				std::cout << "Next class is " << i << " ";
				out[i] = true;
				unprocessedList.push(i);
				//��unprocessedList��ȡ���ʣ��Ԫ��
				while (!unprocessedList.empty())
				{
					int j = unprocessedList.top();
					unprocessedList.pop();

					//��list[j]�е�Ԫ������ͬһ��
					while (!list[j].empty())
					{
						int q = list[j].top();
						list[j].pop();
						if (!out[q])//δ���
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
	//���غв������⣬��ջʵ��
	bool checkBox(int net[], int n)
	{
		//����[0..n-1]�ܽ����飬�����γ�����
		//n�ǹܽ�����

		arraystack<int>* st = new arraystack<int>(n);
		//˳ʱ��ɨ������
		for (int i = 0; i < n; i++)
		{
			//����ܽ�i
			if (!st->empty())
			{
				//���ջ�Ķ����ܽ�
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
		//�Ƿ���ʣ��Ĳ��ɲ��ߵĹܽ�
		if (st->empty())
		{
			//û��ʣ��Ĺܽ�
			std::cout << "Switch box is routable " << std::endl;
			return true;
		}
		std::cout << "Switch box is not routable " << std::endl;
		return false;
	}

	//�г���������,��ջʵ��
private:
	arraystack<int>* track;//����������
	int numberOfCars;	   //�ж��ٸ�����
	int numberOfTracks;	   //���ٸ�������
	int smallestCar;       //�ڻ������б����С�ĳ���
	int itsTrack;          //ͣ������С��ŵĳ���Ļ�����

public:
	bool railroad(int inputOrder[], int theNumberOfCars, int theNumberOfTracks)
	{
		//�ӳ�ʼ˳��ʼ���ų���
		//������ųɹ�������true�����򷵻�false
		numberOfCars = theNumberOfCars;
		numberOfTracks = theNumberOfTracks;

		//�������ڻ�������ջ
		track = new arraystack<int>[numberOfTracks + 1];

		int nextCarToOutput = 1;
		smallestCar = numberOfCars + 1;//���������޳���

		//���ų���
		for (int i = 1; i <= numberOfCars; i++)
		{
			if (inputOrder[i] == nextCarToOutput)
			{
				//������inputOrder[i]ֱ���Ƶ������
				std::cout << "Move car " << inputOrder[i]
					<< " from input track to output track" << std::endl;
				nextCarToOutput++;
				//�ӻ������������Ƶ������
				while (smallestCar == nextCarToOutput)
				{
					outputFromHoldingTrack();
					nextCarToOutput++;
				}
			}
			else
			{
				//������inputOrder[i]�ƶ���һ��������
				if (!putInHoldingTrack(inputOrder[i]))
				return false;
			}
		}
		return true;
	}

	void outputFromHoldingTrack()
	{
		//�������С�ĳ���ӻ������Ƶ������
		//��ջlistTrack��ɾ�������С�ĳ���
		track[itsTrack].pop();
		std::cout << "Move car " << smallestCar << "from holding"
			<< "track " << itsTrack << "to output track" << std::endl;
		//������е�ջ����Ѱ�ұ����С�ĳ������������ջitsTrack
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
		//������c�Ƶ���һ��������������false����û�п��õĻ��峵��ʱ
		//Ϊ����cѰ������ʵĳ�������ʼ��
		int bestTrack = 0;//Ŀǰ����ʵĻ�����
		int bestTop = numberOfCars + 1; //ȡbestTrack�ж����ĳ���

		//ɨ�軺����
		for (int i = 1; i <= numberOfTracks; i++)
			if (!track[i].empty())
			{
				//��������Ϊ��
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
		
		if (bestTrack == 0) return false;//û�п��õĹ��
		//������c�ƶ���bestTrack
		track[bestTrack].push(c);
		std::cout << "Move car " << c << " from input track "
			<< " to holding track" << bestTrack << std::endl;

		//�����Ҫ������smallestCar ��itsTrack
		if (c < smallestCar)
		{
			smallestCar = c;
			itsTrack = bestTrack;
		}
		return true;
	}

	//�ж�����ƥ��,����ڼ������ź͵ڼ�������ƥ��
public:
	void printMatchedPairs(std::string expr)
	{
		arraystack<int>s;
		int length = expr.length();
		//�����ַ�����Ѱ����������
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
					{//��ջ�г���ɾ��ƥ���������
						std::cout << s.top() << ' ' << i << std::endl;
						s.pop();
					}
					catch (stackEmpty)
					{//ջΪ�գ�û��ƥ���������
						std::cout << "No match for right parenthesis"
							<< "at" << i << std::endl;
					}
				}
			}
		}
		//�������ַ�����ջ��Ϊ�գ�ʣ����ջ�е������ǲ�ƥ���
		while (!s.empty())
		{
			std::cout << "No match for left parenthesis "
				<< "at " << s.top() << std::endl;
			s.pop();
		}
	}
};