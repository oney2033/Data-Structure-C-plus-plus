#pragma once
struct positon
{
	int row,
		col;
	operator int()const { return row; }
};