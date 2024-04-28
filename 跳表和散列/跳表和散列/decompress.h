#pragma once
#include<fstream>
#include<iostream>
#include<utility>

//LZW解压缩器
class decompress
{
private:
	//静态常量
	static const int MAX_CODES = 4096,//2^12
		BYTE_SIZE = 8,
		EXCESS = 4,		//12 - BYTE_SIZE
		ALPHA = 256,	//2^BYTE_SIZE
		MASK = 15;		//2^EXCESS - 1

	typedef std::pair<int, char> pairType;
public:
	
	//LZW解压缩器
	void LZWdecompress()
	{//解压一个压缩文件
		int codesUsed = ALPHA;//当前代码codeUsed
		//输入和解压缩
		int pcode,//前面的代码
			ccode;//当前的代码
		if (getCode(pcode))
		{//文件不空
			s[0] = pcode;//取pcode的代码
			out.put(s[0]);//输出pcode的串
			size = 0;//s[size]是最后一个输出串的第一个字符

			while (getCode(ccode))
			{// 又一个代码
				if (ccode < codesUsed)
				{// 确定代码
					output(ccode);
					if (codesUsed < MAX_CODES)
					{// 建立新代码
						ht[codesUsed].first = pcode;
						ht[codesUsed++].second = s[size];
					}
				}
				else
				{// 特殊情况，没有定义的代码
					ht[codesUsed].first = pcode;
					ht[codesUsed++].second = s[size];
					output(ccode);
				}
				pcode = ccode;
			}
		}
		out.close();
		in.close();
	}

	void setFiles(int argc, char* argv[])
	{
		//确定文件名
		char outputFile[50], inputFile[54];
		//查看是否提供了文件名
		if (argc == 2)
			strcpy_s(outputFile, argv[1]);
		else
		{
			//没有提供文件名
			std::cout << "Enter name of file to decompress" << std::endl;
			std::cout << "Omit the extension .zzz" << std::endl;
			std::cin >> outputFile;
		}
		strcpy_s(inputFile, outputFile);
		strcat_s(inputFile, ".zzz");
		
		//以二进制的形式打开文件
		in.open(inputFile, std::ios::binary);
		if (in.fail())
		{
			std::cerr << "Cannot open " << inputFile << std::endl;
			exit(1);
		}
		out.open(outputFile, std::ios::binary);
	}

	bool getCode(int& code)
	{//把压缩文件中的下一个代码存入code
		//如果不再有代码，返回false
		int c, d;
		if ((c = in.get()) == EOF)
			return false;//不再有代码
		//检查前面是否还有剩余位，如果有，进行连接
		if (bitsLeftOver)
			code = (leftOver << BYTE_SIZE) | c;
		else
		{//没有剩余的位，需要再加4位以凑足代码
			d = in.get();//另外8位
			code = (c << EXCESS) | (d >> EXCESS);
			leftOver = d & MASK;
		}
		bitsLeftOver = !bitsLeftOver;
		return true;

	}

	void output(int code)
	{
		//输出与代码对应的字符串
		size = -1;
		while (code >= ALPHA)
		{//字典的后缀
			s[++size] = ht[code].second;
			code = ht[code].first;
		}
		s[++size] = code;
		//解压缩的字符是s[size]...s[0]；
		for (int i = size; i >= 0; i--)
			out.put(s[i]);
	}

private:
	pairType ht[MAX_CODES]; //字典
	char s[MAX_CODES];		//用于重建文本
	int size;				//重构文本的大小
	int leftOver;			//还没输出的代码位
	bool bitsLeftOver = false;//false表示没有剩余的位没有输出
	std::ifstream in;		//输入文件
	std::ofstream out;		//输出文件
};
