#pragma once
#include<fstream>
#include<iostream>
#include<utility>

//LZW��ѹ����
class decompress
{
private:
	//��̬����
	static const int MAX_CODES = 4096,//2^12
		BYTE_SIZE = 8,
		EXCESS = 4,		//12 - BYTE_SIZE
		ALPHA = 256,	//2^BYTE_SIZE
		MASK = 15;		//2^EXCESS - 1

	typedef std::pair<int, char> pairType;
public:
	
	//LZW��ѹ����
	void LZWdecompress()
	{//��ѹһ��ѹ���ļ�
		int codesUsed = ALPHA;//��ǰ����codeUsed
		//����ͽ�ѹ��
		int pcode,//ǰ��Ĵ���
			ccode;//��ǰ�Ĵ���
		if (getCode(pcode))
		{//�ļ�����
			s[0] = pcode;//ȡpcode�Ĵ���
			out.put(s[0]);//���pcode�Ĵ�
			size = 0;//s[size]�����һ��������ĵ�һ���ַ�

			while (getCode(ccode))
			{// ��һ������
				if (ccode < codesUsed)
				{// ȷ������
					output(ccode);
					if (codesUsed < MAX_CODES)
					{// �����´���
						ht[codesUsed].first = pcode;
						ht[codesUsed++].second = s[size];
					}
				}
				else
				{// ���������û�ж���Ĵ���
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
		//ȷ���ļ���
		char outputFile[50], inputFile[54];
		//�鿴�Ƿ��ṩ���ļ���
		if (argc == 2)
			strcpy_s(outputFile, argv[1]);
		else
		{
			//û���ṩ�ļ���
			std::cout << "Enter name of file to decompress" << std::endl;
			std::cout << "Omit the extension .zzz" << std::endl;
			std::cin >> outputFile;
		}
		strcpy_s(inputFile, outputFile);
		strcat_s(inputFile, ".zzz");
		
		//�Զ����Ƶ���ʽ���ļ�
		in.open(inputFile, std::ios::binary);
		if (in.fail())
		{
			std::cerr << "Cannot open " << inputFile << std::endl;
			exit(1);
		}
		out.open(outputFile, std::ios::binary);
	}

	bool getCode(int& code)
	{//��ѹ���ļ��е���һ���������code
		//��������д��룬����false
		int c, d;
		if ((c = in.get()) == EOF)
			return false;//�����д���
		//���ǰ���Ƿ���ʣ��λ������У���������
		if (bitsLeftOver)
			code = (leftOver << BYTE_SIZE) | c;
		else
		{//û��ʣ���λ����Ҫ�ټ�4λ�Դ������
			d = in.get();//����8λ
			code = (c << EXCESS) | (d >> EXCESS);
			leftOver = d & MASK;
		}
		bitsLeftOver = !bitsLeftOver;
		return true;

	}

	void output(int code)
	{
		//���������Ӧ���ַ���
		size = -1;
		while (code >= ALPHA)
		{//�ֵ�ĺ�׺
			s[++size] = ht[code].second;
			code = ht[code].first;
		}
		s[++size] = code;
		//��ѹ�����ַ���s[size]...s[0]��
		for (int i = size; i >= 0; i--)
			out.put(s[i]);
	}

private:
	pairType ht[MAX_CODES]; //�ֵ�
	char s[MAX_CODES];		//�����ؽ��ı�
	int size;				//�ع��ı��Ĵ�С
	int leftOver;			//��û����Ĵ���λ
	bool bitsLeftOver = false;//false��ʾû��ʣ���λû�����
	std::ifstream in;		//�����ļ�
	std::ofstream out;		//����ļ�
};
