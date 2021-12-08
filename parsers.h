// LR(0) Parsers build in 2021.12.08
// file name: parsers.h
// Edit by @Michael Zhou

#pragma once
#include <string>
#include <vector>

class Expression
{
	char left;
	char* right = nullptr;
	int where_project = 0;
public:
	explicit Expression(char* expression);
	~Expression();
	// void Processing();
	char GetProject() const;
};


class ExpressionList
{
	std::vector<Expression> eList;
public:
	ExpressionList() = default;
	void Add(Expression e);

};

class Node
{
public:
};

// ReSharper disable once CppInconsistentNaming
class LR0Tree
{
public:
};
