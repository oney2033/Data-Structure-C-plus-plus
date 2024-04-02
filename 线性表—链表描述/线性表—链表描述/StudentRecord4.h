#pragma once
#include<iostream>
struct StudentRecord4
{
	int exam1, exam2, exam3;
	int name;

	operator int()const { return exam1; }
};
std::ostream& operator<<(std::ostream& out, const StudentRecord4& x)
{
	std::cout << x.name << ' ' << x.exam1 << ' ' << x.exam2
		<< ' ' << x.exam3 << std::endl;
	return out;
}