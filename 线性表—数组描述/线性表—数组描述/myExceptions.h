#pragma once
#include<string>
#include<iostream>

//非法参数值
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

//非法输入
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

//非法索引
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