#pragma once
#include<string>
#include<iostream>

//�Ƿ�����ֵ
class illegalPamerterValue
{
public:
	illegalPamerterValue(std::string theMessage = "illegal pamerter value")
	{
		message = theMessage;
	}
	void outputMessage() { std::cout << message << std::endl; }
private:
	std::string message;
};

//�Ƿ�����
class illegalInputData
{
public:
	illegalInputData(std::string theMessage = "illegal data input")
	{
		message = theMessage;
	}
	void outputMessage() { std::cout << message << std::endl; }
private:
	std::string message;
};

//�Ƿ�����
class illegalIndex
{
public:
	illegalIndex(std::string theMessage = "illagal index")
	{
		message = theMessage;
	}
	void outputMessage() { std::cout << message << std::endl; }
private:
	std::string message;
};