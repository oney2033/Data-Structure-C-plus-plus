#pragma once
//�������� ���������ʵ��
#include"arrayqueue.h"
class railroadWithQueue
{
public:

	//�������ź���,��������ʱ����false
	bool railroad(int* inputOrder, int theNumberOfCars, int theNumberOfTrack)
	{
		numberOfcars = theNumberOfCars;
		numberOfTracks = theNumberOfTrack-1;//����һ��������Խ������

		track = new arrayqueue<int>[numberOfTracks + 1];//������[1-numberOfTrack]�Ļ�����
		
		int nextCarToOutput = 1;
		smallestCar = numberOfcars + 1;//û�г��ڻ�������
		
		//�������������
		for (int i = 1; i <= numberOfcars; i++)
		{
			if (inputOrder[i] == nextCarToOutput)
			{
				std::cout << "Move car " << inputOrder[i] << " from input "
					<< "track to output track" << std::endl;
				nextCarToOutput++;

				//�������
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


	//��������뻺������û�п��û�����ʱ����false
	bool putInHoldingTrack(int c)
	{
		//Ϊ����cѰ�����ʺϵĻ�����
		//��ʼ��
		int bestTrack = 0, //Ŀǰ����ʵĻ�����
			bestLast = 0;  //ȡbsetTrack�����ĳ���
		//ɨ�軺����
		for (int i = 1; i <= numberOfTracks; i++)
		{
			if (!track[i].empty())
			{//������i��Ϊ��
				int lastCar = track[i].back();
				if (c > lastCar && lastCar > bestLast)
				{
					//��������ʵĻ������ͺ��ʹ�������ĳ���
					bestLast = lastCar;
					bestTrack = i;
				}
			}
			else //������Ϊ��
				if (bestTrack == 0)
					bestTrack = i;
		}
		if (bestTrack == 0)
			return false;//û�п��õĻ�����
		//������c�Ƶ�bestTrack
		track[bestTrack].push(c);
		std::cout << "Move car " << c << " from input track "
			<< "to holding track " << bestTrack << std::endl;
		//���»������ϱ����С�ĳ���ͱ����С�ĳ������ĸ������
		if (c < smallestCar)
		{
			smallestCar = c;
			itsTrack = bestTrack;
		}
		return true;
	}

	//�������
	void outputFromHoldingTrack()
	{
		//������������������С�ĳ���
		track[itsTrack].pop();
		std::cout << "Move car " << smallestCar << " from holding track "
			<< itsTrack << " to output track" << std::endl;
		//ͨ��������ж��е�ǰ���ҵ��µ���С�����Լ��������ڹ��
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
	arrayqueue<int>* track; //����������
	int numberOfcars;       //�ж��ٸ�����
	int numberOfTracks;     //�ж��ٸ�������
	int smallestCar;        //�������ϱ����С�ĳ���
	int itsTrack;           //�����С�ĳ������ĸ������
};