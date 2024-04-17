#pragma once
#include<iostream>
#include"make2Darray.h"
#include"arrayqueue.h"
#include"positon.h"

//ͼԪʶ�����һ������ֵ�������ڻ��������ڣ��������ڵ�ͼԪԪ�ؾ���ͬһͼԪ�����أ���������ͬһͼԪ������ʱ���б��
class CompontLabeling
{
public:
	//ͼԪʶ��ĺ���
	void labelComponts()
	{
		//��ʼ������offset
		positon offset[4];
		offset[0].row = 0; offset[0].col = 1;//��
		offset[1].row = 1; offset[1].col = 0;//��
		offset[2].row = 0; offset[2].col = -1;//��
		offset[3].row = -1; offset[3].col = 0;//��
		//��ʼ��0ֵ����Χǽ
		for (int i = 0; i <= size + 1; i++)
		{
			pixel[0][i] = pixel[size + 1][i] = 0;//�ײ��Ͷ���
			pixel[i][0] = pixel[i][size + 1] = 0;//��ߺ��ұ�
		}
		int numOfNbrs = 4;//һ�����ص�����λ����
		//ɨ���������أ����ͼԪ
		arrayqueue<positon>q;
		positon nbr, here;
		int id = 1;//ͼԪ��id
		for (int r = 1; r <= size; r++)//ͼ�����r
		{
			for (int c = 1; c <= size; c++)//ͼ�����c
			{
				if (pixel[r][c] == 1)
				{
					//�µ�ͼԪ
					pixel[r][c] = ++id;//��ֵΪ��һ��id
					here.row = r;
					here.col = c;

					while (true)
					{
						//���ʣ�µ�ͼԪ
						for (int i = 0; i < numOfNbrs; i++)
						{
							nbr.row = here.row + offset[i].row;
							nbr.col = here.col + offset[i].col;
							if (pixel[nbr.row][nbr.col] == 1)
							{
								//�����ǵ�ǰͼԪ��һ����
								pixel[nbr.row][nbr.col] = id;
								q.push(nbr);
							}
						}
						//ͼԪ������δ���������
						if (q.empty())break;
						here = q.front();
						q.pop();
					}
				}
			}
		}
	}

	//���뺯��
	void inputImage()
	{
		std::cout << "Enter image size" << std::endl;
		std::cin >> size;
		make2Darray(pixel, size + 2, size + 2);
		std::cout << "Enter the pixel array in row-major order" << std::endl;
		for (int i = 1; i <= size; i++)
			for (int j = 1; j <= size; j++)
				std::cin >> pixel[i][j];
	}

	//�������
	void outputImage()
	{
		std::cout << "The labeled image is" <<std::endl;
		for (int i = 1; i <= size; i++)
		{
			for (int j = 1; j <= size; j++)
				std::cout << pixel[i][j] << "  ";
			std::cout << std::endl;
		}
	}
private:
	int** pixel;
	int size;
};