// LR(0) Parsers build in 2021.12.09
// file name: ExpressionLib.cpp
// Edit by @Michael Zhou
#include "ExpressionLib.h"

Expression::Expression(const char left, const char* right, const unsigned no)
	: left(left),
	  right{},
	  length(0),
	  no(no)
{
	strcpy_s(this->right, right);
	length = strlen(right);
}

Expression::Expression(const Expression& src)
{
	left = src.left;
	strcpy_s(right, src.right);
	length = src.length;
	no = src.no;
}

char Expression::GetLeft()
{
	return left;
}

char Expression::GetRight(const int index) const
{
	return right[index];
}

ExpressionLib::ExpressionLib() = default;

void ExpressionLib::Add(ExpressionParser e)
{
	for (auto right : e.GetRight())
	{
		if (counter == 0)
		{
			auto temp = new char[2];
			temp[1] = '\0';
			temp[0] = e.GetLeft();
			lib.emplace_back(Expression('\'', temp, counter));
			delete[] temp;
			counter += 1;
		}

		lib.emplace_back(Expression(e.GetLeft(), right, counter));
		counter++;
	}
	int tmp_equal = 0;
	for (char vn : vn_set)
	{
		if (vn == e.GetLeft())
		{
			tmp_equal = 1;
		}
	}
	if (!tmp_equal)
	{
		vn_set.push_back(e.GetLeft());
	}
}

// int ExpressionLib::IfVn(char charactor)
// {
// 	for (char vn : vn_set)
// 	{
// 		if (vn == charactor)
// 	}
// }

NARRAY ExpressionLib::FindVn(const char non_terminal) const
{
	NARRAY arr;
	for (unsigned i = 0; i < lib.size(); i++)
	{
		if (lib[i].left == non_terminal)
		{
			arr.push_back(i);
		}
	}
	return arr;
}

Expression ExpressionLib::GetStart()
{
	return lib[0];
}
