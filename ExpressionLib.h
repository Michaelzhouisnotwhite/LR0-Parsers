// LR(0) Parsers build in 2021.12.09
// file name: ExpressionLib.h
// Edit by @Michael Zhou

#pragma once
#include "header.h"
#include "ExpressionParser.h"
/**
 * \brief 表达式library的基础单位
 */
class Expression
{
public:
	char left;
	char right[255]{};
	unsigned length;
	unsigned no;
	Expression(char left, const char* right, unsigned no);
	Expression(const Expression& src);
	char GetLeft() const;
	char GetRight(int index) const;
};

/**
 * \brief 表达式数据库
 */
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
