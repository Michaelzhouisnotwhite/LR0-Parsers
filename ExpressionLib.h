// LR(0) Parsers build in 2021.12.09
// file name: ExpressionLib.h
// Edit by @Michael Zhou

#pragma once
#include "header.h"
#include "ExpressionParser.h"
class Expression
{
public:
	char left;
	char right[255]{};
	unsigned length;
	unsigned no;
	Expression(char left, const char* right, unsigned no);
	Expression(const Expression& src);
	char GetLeft();
	char GetRight(int index) const;
};

class ExpressionLib
{
public:
	std::vector<Expression> lib;
private:
	int counter = 0;
	std::vector<char> vn_set;
public:
	ExpressionLib();
	void Add(ExpressionParser e);
	// int IfVn(char charactor);
	NARRAY FindVn(char non_terminal) const;
	Expression GetStart();
};
