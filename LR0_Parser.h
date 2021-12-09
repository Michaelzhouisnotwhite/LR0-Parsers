// LR(0) Parsers build in 2021.12.09
// file name: LR0_Parser.h
// Edit by @Michael Zhou

#pragma once
#include "ExpressionLib.h"

class Node
{
public:
	int where =0;
	Expression e;
	explicit Node(Expression e);
};
class Container
{
public:
	int s = 0;
	char data{};

	std::vector<Node> nodes;
	std::vector<Container*> containers;
};

class Lr0Parsers
{
	ExpressionLib library;
	Container root;
public:
	Lr0Parsers();
	static void PrintInfo();
	void Run();
	void Parsing();
	void Lr0Tree(Container **node);
};
