#pragma once
#include<string>
#include<iostream>
struct studentRecord
{
	int score;
	std::string* name;

	int operator !=(studentRecord x)const
	{
		return (score != x.score || name !=x.name);
	}
	
	operator int()const { return score; }
};
	std::ostream& operator<<(std::ostream& out, const studentRecord& x)
	{
		out << x.score << ' ' << *x.name << std::endl;
		return out;
	}