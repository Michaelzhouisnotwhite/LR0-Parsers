// LR(0) Parsers build in 2021.12.09
// file name: LR0_Parser.h
// Edit by @Michael Zhou

#pragma once
#include "ExpressionLib.h"

/**
 * \brief 表达式节点，因为每个表达式都有一个核
 */
class Node
{
public:
	unsigned where = 0;
	Expression* e = nullptr;
	explicit Node(Expression* e);
	Node(const Node& node);
};

/**
 * \brief 项目集规范族的容器
 */
class Container
{
public:
	int s = 0; // 项目集规范族的行号
	char data{};

	std::vector<Node> containers;
	std::vector<Container*> nodes; // 下一个项目集规范族的节点
	Container();

	/* 构造函数 */
	explicit Container(int s, char data);
	~Container();
};

/**
 * \brief LR0文法分析器
 */
class Lr0Parsers
{
	ExpressionLib library; // 所有的表达式存储
	Container root; // 根节点
	std::vector<Container*> project_list; //
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
