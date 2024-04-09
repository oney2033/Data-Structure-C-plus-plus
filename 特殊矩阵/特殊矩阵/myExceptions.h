#pragma once
#include<iostream>
#include<string>

class illeagParameterVaule
{
public:
	illeagParameterVaule(std::string theMessage = "illeag parameter value")
	{
		message = theMessage;
	}
	void output() { std::cout << message << std::endl; }
private:
	std::string message;
};

class illeaglIndex
{
public:
	illeaglIndex(std::string theMessage = "illeagl index")
	{
		message = theMessage;
	}
	void output() { std::cout << message << std::endl; }
private:
	std::string message;
};

class matrixIndexOutofBounds
{
public:
	matrixIndexOutofBounds(std::string theMessage = "matrix index outof bounds")
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
	matrixSizeMismatch(std::string theMessage = "matrix size mismatch")
	{
		message = theMessage;
	}
	void output() { std::cout << message << std::endl; }
private:
	std::string message;
};