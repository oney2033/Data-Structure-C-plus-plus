#pragma once
#include<iostream>
#include<string>

class illegalParameterValue
{
public:
	illegalParameterValue(std::string theMessage = "Illegal parameter value")
	{
		message = theMessage;
	}
	void outputMessage() { std::cout << message << std::endl; }
private:
	std::string message;
};

class queempty
{
public:
	queempty(std::string theMessage = "Invalid operation on empty queue")
	{
		message = theMessage;
	}
	void outputMessage() { std::cout << message << std::endl; }
private:
	std::string message;
};