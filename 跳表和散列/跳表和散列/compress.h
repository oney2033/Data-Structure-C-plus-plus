#pragma once
#include<fstream>
#include<iostream>
#include"HashChains.h"
#include<utility>
		

class compress
{
public:
	typedef	std::pair<const long, int>pairTpeye;
	
	//L-Z-W压缩器
	void LZWcompress()
	{
		//定义和初始化代码字典
		hashChains<long, int>h(DIVISOR);
		for (int i = 0; i < ALPHA; i++)
		{
			h.insert(pairTpeye(i, i));
		}
		int codesUsed = ALPHA;
		//输入和压缩
		int c = in.get();//输入文件的第一个字符
		if (c != EOF)
		{
			long pcode = c;//前缀代码
			while ((c = in.get()) != EOF)
			{
				//处理字符C
				long theKey = (pcode << BYTE_SIZE) + c;
				//检查关键字theKey是否在字典中
				pairTpeye* thePair = h.find(theKey);
				if (thePair == NULL)
				{
					//关键字theKey不在表中
					output(pcode);
					if (codesUsed < MAX_CODES)//建立新代码
						h.insert(pairTpeye((pcode << BYTE_SIZE) | c, codesUsed++));
					pcode = c;
				}
				else
					pcode = thePair->second;//关键字在表中
			}
			//输出最后的代码
			output(pcode);
			if (bitsLeftOver)
				out.put(leftOver << EXCESS);
		}
		out.close();
		in.close();
	}

//建立输入输出流
	void setFiles(int argc, char* argv[])
	{
		char outputFile[50],  inputFile[54];
		//检查是否有文件名
		if (argc >= 2)
			strcpy_s(inputFile, argv[1]);
		else
		{
			//没有文件，输入文件名
			std::cout << "Enter name of file to compress" << std::endl;
			std::cin >> inputFile;	
		}
		//打开二进制文件
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

	//输出8位，把剩余位保存
	void output(long pcode)
	{
		int c, d;
		if (bitsLeftOver)
		{
			//前面有剩余的位
			d = int(pcode & MASK1);
			c = int(leftOver << EXCESS) | (pcode >> BYTE_SIZE);
			out.put(c);
			out.put(d);
			bitsLeftOver = false;
		}
		else
		{
			//前面没有剩余的位
			leftOver = pcode & MASK2;
			c = int(pcode >> EXCESS);
			out.put(c);
			bitsLeftOver = true;
		}
	}

private:
	int leftOver;		//待输出的代码位
	bool bitsLeftOver = false;//false表示没有余下的位
	std::ifstream in;	//输入文件
	std::ofstream out;	//输出文件

	//常量
	const int
		DIVISOR = 4099,	//散列函数的除数
		MAX_CODES = 4096, //2^12
		BYTE_SIZE = 8,    //
		EXCESS = 4, //	12-BYTE_SIZE
		ALPHA = 256,//	2^BYTE_SIZE
		MASK1 = 255,//	ALPHA - 1
		MASK2 = 15;//2^EXCESS -1
};