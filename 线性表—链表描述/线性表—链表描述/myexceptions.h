#pragma once
#include<iostream>
#include<string>
class illeagPamerterValue
{
public:
	illeagPamerterValue(std::string theMessage = "illegal pamerter value")
	{
		message = theMessage;
	}
	void output()
	{
		std::cout << message << std::endl;
	}
private:
	std::string message;
};

class illegalIndex
{
public:
	illegalIndex(std::string theMessgae = "Illegal index")
	{
		message = theMessgae;
	}
	void output()
	{
		std::cout << message << std::endl;
	}
private:
	std::string message;
};