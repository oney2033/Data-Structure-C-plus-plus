#pragma once
#include"positon.h"
#include"make2Darray.h"
#include<iostream>
#include"arrayqueue.h"
//Ѱ�ҵ�·���ߵ�·��
class wrieRouter
{
public:
		//�ҵ�����㵽�յ�����·����
		// �ɹ��򷵻� true�����򷵻� false
	bool findPath()
	{
		if ((start.row == finish.row) && (start.col == finish.col))
		{
			pathLength = 0;
			return true;
		}
		//��ʼ��ƫ����
		positon offset[4];
		offset[0].row = 0; offset[0].col = 1;   // ��
		offset[1].row = 1; offset[1].col = 0;   // ��
		offset[2].row = 0; offset[2].col = -1;  // ��
		offset[3].row = -1; offset[3].col = 0;  // ��

		// ��ʼ��������Χ�ı߽�ǽ
		for (int i = 0; i <= size + 1; i++)
		{
			grid[0][i] = grid[size + 1][i] = 1;//�����͵ײ�
			grid[i][0] = grid[i][size + 1] = 1;//��ߺ��ұ�
		}
		positon here = start;
		grid[start.row][start.col] = 2;//���
		int numOfNbrs = 4;//һ�����������λ����

		//�Կɵ����λ�ý��б��
		arrayqueue<positon>q;
		positon nbr;
		do
		{
			//������λ�������
			for (int i = 0; i < numOfNbrs; i++)
			{
				//�������λ��
				nbr.row = here.row + offset[i].row;
				nbr.col = here.col + offset[i].col;
				if (grid[nbr.row][nbr.col] == 0)
				{
					//��û��ǵ�nbr�����
					grid[nbr.row][nbr.col] = grid[here.row][here.col] + 1;
					if ((nbr.row == finish.row) && (nbr.col == finish.col))break;//������
					//�Ѻ��߲������
					q.push(nbr);
				}
			}
			//�Ƿ񵽴��յ�
			if((nbr.row == finish.row)&&
				(nbr.col == finish.col))break; //�ﵽ
			//�յ㲻�ɵ�������Ƶ�nbr��
			if (q.empty())
				return false;   //·��������
			here = q.front();   //ȡ��һ��λ��
			q.pop();
		} while (true);

		//����·��
		pathLength = grid[finish.row][finish.col] - 2;
		path = new positon[pathLength];

		//���յ����
		here = finish;
		for (int j = pathLength - 1; j >= 0; j--)
		{
			path[j] = here;
			//Ѱ������λ��
			for (int i = 0; i < numOfNbrs; i++)
			{
				nbr.row = here.row + offset[i].row;
				nbr.col = here.col + offset[i].col;
				if (grid[nbr.row][nbr.col] == j + 2)break;
			}
			here = nbr;	//��������λ��
		}
		return true;
	}

	//�������
	void outputPath()
	{
		std::cout << "The wire path is" << std::endl;
		for (int i = 0; i < pathLength; i++)
		{
			std::cout << path[i] << " " << path[i].col << std::endl;
		}
	}

	//���빦��
	void inputData()
	{
		//���벼������
		std::cout << "Enter grid size" << std::endl;
		std::cin >> size;

		std::cout << "Enter the start position" << std::endl;
		std::cin >> start.row >> start.col;

		std::cout << "Enter the finish positon" << std::endl;
		std::cin >> finish.row >> finish.col;
		
		//�����������������
		make2Darray(grid, size + 2, size + 2);
		std::cout << "Enter the wiring grid in row-major order" << std::endl;
		for (int i = 1; i <= size; i++)
		{
			for (int j = 1; j <= size; j++)
				std::cin >> grid[i][j];
		}

	}


private:
	int** grid;		//2D ����
	int size;		//�����е�����������
	int pathLength; //��̵���·������
	arrayqueue<positon>q; //δ��չ�ĵ���λ�ö���
	positon start,		//��ʼλ��
			finish;		//����λ��
	positon* path;	//���·��
};