#pragma once
//车厢重排 用数组队列实现
#include"arrayqueue.h"
class railroadWithQueue
{
public:

	//车厢重排函数,不能重排时返回false
	bool railroad(int* inputOrder, int theNumberOfCars, int theNumberOfTrack)
	{
		numberOfcars = theNumberOfCars;
		numberOfTracks = theNumberOfTrack-1;//保持一个轨道打开以进行输出

		track = new arrayqueue<int>[numberOfTracks + 1];//创建从[1-numberOfTrack]的缓冲轨道
		
		int nextCarToOutput = 1;
		smallestCar = numberOfcars + 1;//没有车在缓冲轨道中
		
		//将车厢进行重排
		for (int i = 1; i <= numberOfcars; i++)
		{
			if (inputOrder[i] == nextCarToOutput)
			{
				std::cout << "Move car " << inputOrder[i] << " from input "
					<< "track to output track" << std::endl;
				nextCarToOutput++;

				//继续输出
				while (smallestCar == nextCarToOutput)
				{
					outputFromHoldingTrack();
					nextCarToOutput++;
				}
			}
			else
			{
				if (!putInHoldingTrack(inputOrder[i]))
					return false;
			}
		}
		return true;
	}


	//将车厢调入缓冲轨道，没有可用缓冲轨道时返回false
	bool putInHoldingTrack(int c)
	{
		//为车厢c寻找最适合的缓冲轨道
		//初始化
		int bestTrack = 0, //目前最合适的缓冲轨道
			bestLast = 0;  //取bsetTrack中最后的车厢
		//扫描缓冲轨道
		for (int i = 1; i <= numberOfTracks; i++)
		{
			if (!track[i].empty())
			{//缓冲轨道i不为空
				int lastCar = track[i].back();
				if (c > lastCar && lastCar > bestLast)
				{
					//更新最合适的缓冲轨道和合适轨道中最大的车厢
					bestLast = lastCar;
					bestTrack = i;
				}
			}
			else //缓冲轨道为空
				if (bestTrack == 0)
					bestTrack = i;
		}
		if (bestTrack == 0)
			return false;//没有可用的缓冲轨道
		//将车厢c移到bestTrack
		track[bestTrack].push(c);
		std::cout << "Move car " << c << " from input track "
			<< "to holding track " << bestTrack << std::endl;
		//更新缓冲轨道上编号最小的车厢和编号最小的车厢在哪个轨道上
		if (c < smallestCar)
		{
			smallestCar = c;
			itsTrack = bestTrack;
		}
		return true;
	}

	//输出函数
	void outputFromHoldingTrack()
	{
		//将缓冲轨道上输出编号最小的车厢
		track[itsTrack].pop();
		std::cout << "Move car " << smallestCar << " from holding track "
			<< itsTrack << " to output track" << std::endl;
		//通过检查所有队列的前端找到新的最小车厢以及车厢所在轨道
		smallestCar = numberOfcars + 2;
		for (int i = 1; i <= numberOfTracks; i++)
		{
			if (!track[i].empty() && track[i].front() < smallestCar)
			{
				smallestCar = track[i].front();
				itsTrack = i;
			}
		}
	}
private:
	arrayqueue<int>* track; //缓冲轨道数组
	int numberOfcars;       //有多少个车厢
	int numberOfTracks;     //有多少个缓冲轨道
	int smallestCar;        //缓冲轨道上编号最小的车厢
	int itsTrack;           //编号最小的车厢在哪个轨道上
};