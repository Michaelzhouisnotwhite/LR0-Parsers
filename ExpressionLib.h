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
	wchar_t left;
	wchar_t right[255]{};
	unsigned length;
	unsigned no;
	Expression(wchar_t left, const wchar_t* right, unsigned no);
	Expression(const Expression& src);
	wchar_t GetLeft() const;
	wchar_t GetRight(int index) const;

	bool operator==(const Expression& exp) const;
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
	std::vector<wchar_t> vn_set;
public:
	ExpressionLib();
	void Add(ExpressionParser e);
	// int IfVn(wchar_t charactor);
	NARRAY FindVn(wchar_t non_terminal) const;
	Expression GetStart();
};
