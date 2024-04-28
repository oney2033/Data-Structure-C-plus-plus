#include<iostream>
#include"sortedChain.h"
#include"skipList.h"
#include"hashTable.h"
#include"HashChains.h"
#include"compress.h"
#include <fstream>
#include"decompress.h"
using namespace std;

int main(int argc,char* argv[])
{
	//��cmd�����н��в��ԣ����Ϊ.zzz�ĵ�
	
//	//����LZWѹ����
//	compress LZW;
//	LZW.setFiles(argc, argv);
//	LZW.LZWcompress();

	//��cmd�����н��в���,���Ϊ.txt�ĵ�
	// 
	//����LZW��ѹ����
	decompress LZWdecompress;
	LZWdecompress.setFiles(argc, argv);
	LZWdecompress.LZWdecompress();

#if 0
	//������ʽɢ�У�������ÿ��Ͱ�����������޼�¼
	hashChains<int, int> z(11);
	std::pair<int, int> p;
	// ���Բ���
	p.first = 2; p.second = 10;
	z.insert(p);
	p.first = 10; p.second = 50;
	z.insert(p);
	p.first = 24; p.second = 120;
	z.insert(p);
	p.first = 32; p.second = 160;
	z.insert(p);
	p.first = 3; p.second = 15;
	z.insert(p);
	p.first = 12; p.second = 60;
	z.insert(p);
	cout << "The dictionary is " << endl << z << endl;
	cout << "Its size is " << z.size() << endl;

	// ���Բ���
	cout << "Element associated with 2 is " << z.find(2)->second << endl;
	cout << "Element associated with 10 is " << z.find(10)->second << endl;
	cout << "Element associated with 12 is " << z.find(12)->second << endl;
#endif
#if 0
	//����ɢ�б�����̽���ʾ
	hashTable<int, int>z(11);
	std::pair<int, int>p;

	//���Բ��뺯��
	p.first = 2; p.second = 10;
	z.insert(p);
	p.first = 10; p.second = 50;
	z.insert(p);
	p.first = 24; p.second = 120;
	z.insert(p);
	p.first = 32; p.second = 160;
	z.insert(p);
	p.first = 3; p.second = 15;
	z.insert(p);
	p.first = 12; p.second = 60;
	z.insert(p);
	cout << "The dictionary is " << endl << z << endl;
	cout << "Its size is " << z.size() << endl;
	
	//���Բ��Һ���
	cout << "Element associated with 2 is " << z.find(2)->second << endl;
	cout << "Element associated with 10 is " << z.find(10)->second << endl;
	cout << "Element associated with 12 is " << z.find(12)->second << endl;
#endif

#if 0
	//���԰��ؼ��ֵ���������
	//���Բ��뺯��
	skipList<int, int>z(1000);
	std::pair<int, int>p;
	p.first = 2; p.second = 10;
	z.insert(p);
	p.first = 10; p.second = 50;
	z.insert(p);
	p.first = 6; p.second = 30;
	z.insert(p);
	p.first = 8; p.second = 40;
	z.insert(p);
	p.first = 1; p.second = 5;
	z.insert(p);
	p.first = 12; p.second = 60;
	z.insert(p);
	cout << "The dictionary is " << z << endl;
	cout << "Its size is " << z.size() << endl;

	// ���Բ��Һ���
	cout << "Element associated with 1 is " << z.find(1)->second << endl;
	cout << "Element associated with 6 is " << z.find(6)->second << endl;
	cout << "Element associated with 12 is " << z.find(12)->second << endl;

	//����ɾ������
	z.erase(1);
	z.erase(2);
	z.erase(6);
	z.erase(12);
	cout << "Deleted 1, 2, 6, 12" << endl;
	cout << "The dictionary is " << z << endl;
	cout << "Its size is " << z.size() << endl;
#endif

#if 0
	//���԰��ؼ��ִ������������
	sortedChain<int, int>z;
	std::pair<int, int>p;
	//���Բ���
	p.first = 2; p.second = 10;
	z.insert(p);
	p.first = 10; p.second = 50;
	z.insert(p);
	p.first = 6; p.second = 30;
	z.insert(p);
	p.first = 8; p.second = 40;
	z.insert(p);
	p.first = 1; p.second = 5;
	z.insert(p);
	p.first = 12; p.second = 60;
	z.insert(p);
	cout << "The chain is " << z << endl;
	cout << "Its size is " << z.size() << endl;

	//���Բ��Һ���
	cout << "Element associated with 1 is " << z.find(1)->second << endl;
	cout << "Element associated with 6 is " << z.find(6)->second << endl;
	cout << "Element associated with 12 is " << z.find(12)->second << endl;
	
	//����ɾ������
	z.erase(1);
	z.erase(2);
	z.erase(6);
	z.erase(12);
	cout << "Deleted 1, 2, 6, 12" << endl;
	cout << "The chain is " << z << endl;
	cout << "Its size is " << z.size() << endl;
#endif
}
