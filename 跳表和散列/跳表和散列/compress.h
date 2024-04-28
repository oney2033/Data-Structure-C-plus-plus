#pragma once
#include<fstream>
#include<iostream>
#include"HashChains.h"
#include<utility>
		

class compress
{
public:
	typedef	std::pair<const long, int>pairTpeye;
	
	//L-Z-Wѹ����
	void LZWcompress()
	{
		//����ͳ�ʼ�������ֵ�
		hashChains<long, int>h(DIVISOR);
		for (int i = 0; i < ALPHA; i++)
		{
			h.insert(pairTpeye(i, i));
		}
		int codesUsed = ALPHA;
		//�����ѹ��
		int c = in.get();//�����ļ��ĵ�һ���ַ�
		if (c != EOF)
		{
			long pcode = c;//ǰ׺����
			while ((c = in.get()) != EOF)
			{
				//�����ַ�C
				long theKey = (pcode << BYTE_SIZE) + c;
				//���ؼ���theKey�Ƿ����ֵ���
				pairTpeye* thePair = h.find(theKey);
				if (thePair == NULL)
				{
					//�ؼ���theKey���ڱ���
					output(pcode);
					if (codesUsed < MAX_CODES)//�����´���
						h.insert(pairTpeye((pcode << BYTE_SIZE) | c, codesUsed++));
					pcode = c;
				}
				else
					pcode = thePair->second;//�ؼ����ڱ���
			}
			//������Ĵ���
			output(pcode);
			if (bitsLeftOver)
				out.put(leftOver << EXCESS);
		}
		out.close();
		in.close();
	}

//�������������
	void setFiles(int argc, char* argv[])
	{
		char outputFile[50],  inputFile[54];
		//����Ƿ����ļ���
		if (argc >= 2)
			strcpy_s(inputFile, argv[1]);
		else
		{
			//û���ļ��������ļ���
			std::cout << "Enter name of file to compress" << std::endl;
			std::cin >> inputFile;	
		}
		//�򿪶������ļ�
		in.open(inputFile, std::ios::binary);
		if (in.fail())
		{
			std::cerr << "Cannot open " << inputFile << std::endl;
			exit(1);
		}
		strcpy_s(outputFile, inputFile);
		strcat_s(outputFile,".zzz");
		out.open(outputFile, std::ios::binary);
	}

	//���8λ����ʣ��λ����
	void output(long pcode)
	{
		int c, d;
		if (bitsLeftOver)
		{
			//ǰ����ʣ���λ
			d = int(pcode & MASK1);
			c = int(leftOver << EXCESS) | (pcode >> BYTE_SIZE);
			out.put(c);
			out.put(d);
			bitsLeftOver = false;
		}
		else
		{
			//ǰ��û��ʣ���λ
			leftOver = pcode & MASK2;
			c = int(pcode >> EXCESS);
			out.put(c);
			bitsLeftOver = true;
		}
	}

private:
	int leftOver;		//������Ĵ���λ
	bool bitsLeftOver = false;//false��ʾû�����µ�λ
	std::ifstream in;	//�����ļ�
	std::ofstream out;	//����ļ�

	//����
	const int
		DIVISOR = 4099,	//ɢ�к����ĳ���
		MAX_CODES = 4096, //2^12
		BYTE_SIZE = 8,    //
		EXCESS = 4, //	12-BYTE_SIZE
		ALPHA = 256,//	2^BYTE_SIZE
		MASK1 = 255,//	ALPHA - 1
		MASK2 = 15;//2^EXCESS -1
};