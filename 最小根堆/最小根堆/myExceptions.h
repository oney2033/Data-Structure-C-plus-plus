#pragma once
#include<string>
#include<iostream>

class illeagalParameterValue
{
public:
	illeagalParameterValue(std::string theMessage = "illeagal parameter value")
	{
		message = theMessage;
	}
	void output() { std::cout << message << std::endl; }
private:
	std::string message;
};

class queueEmpty
{
public:
	queueEmpty(std::string theMessage = "queue is empty")
	{
		message = theMessage;
	}
	void output() { std::cout << message << std::endl; }
private:
	std::string message;
};