// LR(0) Parsers build in 2021.12.08
// file name: ExpressionParser.h
// Edit by @Michael Zhou

#pragma once
#include "header.h"

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
	static int CheckExpression(const char* expression);
};
