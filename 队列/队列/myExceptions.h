#pragma once
#include<iostream>
#include<string>
class illegalParameterVaule
{
public:
	illegalParameterVaule(std::string themessage = "illegal parameter value")
	{
		message = themessage;
	}
	void output() { std::cout << message << std::endl; }
private:
	std::string message;
};

class queueempty
{
public:
	queueempty(std::string themessage = "stack empty")
	{
		message = themessage;
	}
	void output() { std::cout << message << std::endl; }
private:
	std::string message;
};