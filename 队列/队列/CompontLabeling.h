#pragma once
#include<iostream>
#include"make2Darray.h"
#include"arrayqueue.h"
#include"positon.h"

//图元识别，如果一个像素值左右相邻或上下相邻，两个相邻的图元元素就是同一图元的像素，当它们是同一图元的像素时进行标记
class CompontLabeling
{
public:
	//图元识别的函数
	void labelComponts()
	{
		//初始化数组offset
		positon offset[4];
		offset[0].row = 0; offset[0].col = 1;//右
		offset[1].row = 1; offset[1].col = 0;//下
		offset[2].row = 0; offset[2].col = -1;//左
		offset[3].row = -1; offset[3].col = 0;//上
		//初始化0值像素围墙
		for (int i = 0; i <= size + 1; i++)
		{
			pixel[0][i] = pixel[size + 1][i] = 0;//底部和顶部
			pixel[i][0] = pixel[i][size + 1] = 0;//左边和右边
		}
		int numOfNbrs = 4;//一个像素的相邻位置数
		//扫描所有像素，标记图元
		arrayqueue<positon>q;
		positon nbr, here;
		int id = 1;//图元的id
		for (int r = 1; r <= size; r++)//图像的行r
		{
			for (int c = 1; c <= size; c++)//图像的列c
			{
				if (pixel[r][c] == 1)
				{
					//新的图元
					pixel[r][c] = ++id;//赋值为下一个id
					here.row = r;
					here.col = c;

					while (true)
					{
						//检查剩下的图元
						for (int i = 0; i < numOfNbrs; i++)
						{
							nbr.row = here.row + offset[i].row;
							nbr.col = here.col + offset[i].col;
							if (pixel[nbr.row][nbr.col] == 1)
							{
								//像素是当前图元的一部分
								pixel[nbr.row][nbr.col] = id;
								q.push(nbr);
							}
						}
						//图元中任意未考察的像素
						if (q.empty())break;
						here = q.front();
						q.pop();
					}
				}
			}
		}
	}

	//输入函数
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

	//输出函数
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