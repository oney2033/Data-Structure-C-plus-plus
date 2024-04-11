#pragma once
#include<iostream>
#include<string>
class illegalParameterValue
{
public:
	illegalParameterValue(std::string theMessage = "illeagl parameter value")
	{
		message = theMessage;
	}
	void output() { std::cout << message << std::endl; }
private:
	std::string message;
};

class stackEmpty
{
public:
	stackEmpty(std::string theMessage = "stack empty")
	{
		message = theMessage;
	}
	void output() { std::cout << message << std::endl; }

private:
	std::string message;
};