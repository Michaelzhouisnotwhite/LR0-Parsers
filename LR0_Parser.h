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
	bool operator==(const Node& node) const;                  
};

struct IsSelf
{
	bool self = true;
	wchar_t data{};

	IsSelf(const bool self, const wchar_t data): self(self), data(data)
	{
	}
};

/**
 * \brief 项目集规范族的容器
 */
class Container
{
public:
	int s = 0; // 项目集规范族的行号
	wchar_t data{};
	IsSelf self_node{false, {}};
	std::vector<Node> containers;
	std::vector<Container*> nodes; // 下一个项目集规范族的节点
	Container();

	/* 构造函数 */
	explicit Container(int s, wchar_t data);
	Container(const Container& src);

	std::vector<Container*>* GetNext();
	~Container();
};

template <class T>
class Row : public std::vector<T>
{
public:
	std::vector<wchar_t> vs;
	void SetIndex(const std::vector<wchar_t>& vs);
	auto at(wchar_t vt);
	void at(wchar_t vt, T value);
	std::vector<wchar_t> GetIndex();
};

class Action
{
public:
	static constexpr wchar_t S = 'S';
	static constexpr wchar_t R = 'r';
	static constexpr wchar_t E = 'a';

	static constexpr int ACC = -99;
	std::vector<wchar_t> vts;
	std::vector<Row<int>> table;
	std::vector<Row<wchar_t>> type;
	void Set(const std::vector<wchar_t>& vts, int max_index);
};

class Goto
{
public:
	std::vector<wchar_t> vns;
	std::vector<Row<int>> table;
	void Set(const std::vector<wchar_t>& vns, int max_index);
};

class Lr0AnalysisTable
{
public:
	Action tAction;
	Goto tGoto;

	int max_index = 0;
	std::set<wchar_t> vt_set;
	std::set<wchar_t> vn_set;

	Lr0AnalysisTable();
};

/**
 * \brief LR0文法分析器
 */
class Lr0Parsers
{
	
	int s = 0;
public:
	ExpressionLib library; // 所有的表达式存储
	Container root; // 根节点


	std::vector<int> state_stack;
	std::vector<wchar_t> symbol_stack;
	std::vector<int> action_stack;
	std::vector<wchar_t> type_stack;
	std::vector<int> goto_stack;



	Lr0AnalysisTable T;

	std::vector<std::vector<int>> state_history;
	std::vector<std::vector<wchar_t>> symbol_history;
	std::vector<std::vector<wchar_t>> input_history;
	Lr0Parsers();


	static void PrintInfo();
	void Run(); // deprated method
	void InitDfa();

	void FindNext(Container* container);
	void FindContainer(Container* container);

	static Container* FindSameContainer(const Container* container, const Node& node);

	static void OutputProject(const Container* container);

	~Lr0Parsers();

	void GetAnalysisTableColRow(const Container* next);

	void InitAnalysisTable();
	void GetAnalysisTable(Container* next);

	void InputAnalysis(const wchar_t* input);

	void PopStack();
	void RecordStack();
};
