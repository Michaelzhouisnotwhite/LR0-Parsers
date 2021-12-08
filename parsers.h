// LR(0) Parsers build in 2021.12.08
// file name: parsers.h
// Edit by @Michael Zhou

#pragma once
#include <string>
#include <vector>
#define ARRAY std::vector<int>

void ExpressionSplit(char * expression);
void CopyStr(char* dst, const char* src);
std::vector<char*> SplitStr(const char* src, char c);
class Expression
{
public:
	char left;
	char* right = nullptr;
	int where_project = 0;

	Expression(const Expression &source);
	explicit Expression(char left, const char* right, int where_project);
	explicit Expression(char* expression);

	~Expression();
	// void Processing();
	char GetProject() const;
	char GetLeft() const;

	void NextProject();

	static int CheckExpression(const char* expression);
};


class ExpressionList
{
	std::vector<Expression> eList;
public:
	ExpressionList() = default;
	void Add(const Expression& e);
	ARRAY Find(char non_terminal) const;
};

class Node
{
	std::vector<Expression> node;
public:
	explicit Node(const Expression& e);
	void Contain(const Expression& e);
	void Goto(const Expression& e);
};

// ReSharper disable once CppInconsistentNaming
class LR0Parsers
{
public:
	;

};
