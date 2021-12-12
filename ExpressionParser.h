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
	char left;
	SARRAY rightList;
	char* right = nullptr;

	explicit ExpressionParser(char *input);
	~ExpressionParser();

	SARRAY GetRight();
	char GetLeft() const;
	static FLAG CheckExpression(const char* expression);
};
