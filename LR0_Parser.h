// LR(0) Parsers build in 2021.12.09
// file name: LR0_Parser.h
// Edit by @Michael Zhou

#pragma once
#include "ExpressionLib.h"

class Node
{
public:
	unsigned where = 0;
	Expression *e = nullptr;
	explicit Node(Expression *e);
	Node(const Node& node);
};

class Container
{
public:
	int s = 0;
	char data{};


	std::vector<Node> containers;
	std::vector<Container*> nodes;
	Container()=default;
	explicit Container(int s, char data);
	~Container();
};

class Lr0Parsers
{
	ExpressionLib library;
	Container root;
	std::vector<Container*> project_list;
public:
	Lr0Parsers();
	static void PrintInfo();
	void Run();
	void InitDfa();

	void FindNext(Container* container, int s);
	void FindContainer(Container* container);

	static void OutputProject(const Container* container);

	~Lr0Parsers();
};
