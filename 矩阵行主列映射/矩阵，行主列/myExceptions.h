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
	void output() { std::cout << message << std::endl; }
private:
	std::string message;
};

class matrixSizeMismatch
{
public:
	matrixSizeMismatch(std::string theMessage = "The size of two matrix doesn't match")
	{
		message = theMessage;
	}
	void output() { std::cout << message << std::endl; }
private:
	std::string message;
};

class matrixIndexOutOfBounds
{
public:
	matrixIndexOutOfBounds(std::string theMessage = "Matrix Index out of Bounds")
	{
		message = theMessage;
	}
	void output() { std::cout << message << std::endl; }
private:
	std::string message;
};