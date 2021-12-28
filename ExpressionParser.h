// LR(0) Parsers build in 2021.12.08
// file name: ExpressionParser.h
// Edit by @Michael Zhou

#pragma once
#include "header.h"

/**
 * \brief 表达式解析器
 */
class ExpressionParser
{
public:
	wchar_t left;
	SARRAY rightList;
	wchar_t* right = nullptr;

	explicit ExpressionParser(wchar_t *input);
	~ExpressionParser();

	SARRAY GetRight();
	wchar_t GetLeft() const;
	static FLAG CheckExpression(const wchar_t* expression);
};
