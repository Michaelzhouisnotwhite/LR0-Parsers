// LR(0) Parsers build in 2021.12.08
// file name: Lr0_Parsers.cpp
// Edit by @Michael Zhou
#include <set>

#include "LR0_Parser.h"
#include "utils.h"


/**
 * \brief 创建节点中的表达式内容，以类指针的形式存储，节省内存空间
 * \param e 表达式，来自表达式Libray
 */
Node::Node(Expression* e)
{
	this->e = e;
}

/**
 * \brief 复制构造函数
 * \param node copy source
 */
Node::Node(const Node& node)
{
	where = node.where;
	e = node.e;
}

bool Node::operator==(const Node& node) const
{
	if (where == node.where && !wcscmp(e->right, node.e->right) && e->left == node.e->left)
	{
		return true;
	}
	return false;
}

Container::Container()
= default;

Container::Container(const int s, const wchar_t data)
	: s(s),
	  data(data)
{
}

Container::Container(const Container& src)
{
	s = src.s;
	data = src.data;
	self_node = src.self_node;
	containers = src.containers;
	nodes = src.nodes;
}

std::vector<Container*>* Container::GetNext()
{
	return &nodes;
}

Container::~Container()
{
	for (auto node : nodes)
	{
		delete node;

		node = nullptr;
	}
}

template <class T>
void Row<T>::SetIndex(const std::vector<wchar_t>& vs)
{
	this->vs = vs;
	this->resize(vs.size());
}

template <class T>
auto Row<T>::at(const wchar_t vt)
{
	for (uint8_t i = 0; i < vs.size(); i++)
	{
		if (vt == vs[i])
		{
			return this->begin() + i;
		}
	}
	return this->end();
}

template <class T>
void Row<T>::at(const wchar_t vt, T value)
{
	for (uint8_t i = 0; i < vs.size(); i++)
	{
		if (vt == vs[i])
		{
			*(this->data() + i) = value;
		}
	}
}

template <class T>
std::vector<wchar_t> Row<T>::GetIndex()
{
	return vs;
}

void Action::Set(const std::vector<wchar_t>& vts, const int max_index)
{
	this->vts = vts;
	this->vts.push_back('#');

	table.resize(max_index + 1);
	type.resize(max_index + 1);
	for (auto& value : type)
	{
		value.SetIndex(this->vts);
	}

	for (auto& texts : table)
	{
		texts.SetIndex(this->vts);
		for (int& text : texts)
		{
			text = -1;
		}
	}
}

void Goto::Set(const std::vector<wchar_t>& vns, const int max_index)
{
	this->vns = vns;
	table.resize(max_index + 1);

	for (auto& value : table)
	{
		value.SetIndex(this->vns);
		for (int& text : value)
		{
			text = -1;
		}
	}
}

Lr0AnalysisTable::Lr0AnalysisTable()
= default;


Lr0Parsers::Lr0Parsers()
{
	Run();
	InitDfa();
	FindContainer(&root);
	FindNext(&root);
	GetAnalysisTableColRow(&root);
	OutputProject(&root);
	InitAnalysisTable();
	GetAnalysisTable(&root);
	InputAnalysis(CopyStr(L"abbce#"));
}

/**
 * \brief 菜单显示
 */
void Lr0Parsers::PrintInfo()
{
	std::string wrap = "\n";
	std::string info1 = "Please Enter a LR(0) grammar.";
	std::string info2 = "A line stands for one statement";
	std::string info3 = "type \"->\" refers to transfer to an sentences";
	std::cout << info1 << wrap;
	std::cout << info2 << wrap;
	std::cout << info3 << std::endl;
}


/**
 * \brief (This method is deqrated)菜单、输入行号、输入表达式
 */
void Lr0Parsers::Run()
{
	PrintInfo();

	std::wcout << "First, please enter the numbers of the sentences:" << std::endl;
	wchar_t buffer[1024]; // init input buffer
	while (true)
	{
		std::wcin.getline(buffer, 1024);
		FLAG ifError = NORMAL;

		// 对输入检查是否是数字
		for (int i = 0; i < static_cast<int>(wcslen(buffer)); i++)
		{
			if (!isdigit(buffer[i]))
			{
				std::wcout << "Error: the numbers of the sentence are not int" << std::endl;
				ifError = ERROR;
				break;
			}
		}
		if (ifError == NORMAL)
		{
			break;
		}
		std::wcout << "please enter again:" << std::endl;
	}

	wchar_t* tmp_buffer_end;
	long lines = wcstol(buffer, &tmp_buffer_end, 10);

	// 输入lr0语法
	std::wcout << "Enter the LR(0) Grammar:" << std::endl;
	int line_no = 1;
	while (lines)
	{
		std::wcout << "[" << line_no << "]" << " > ";
		std::wcin.getline(buffer, 1024);
		if (ExpressionParser::CheckExpression(buffer) == ERROR)
		{
			std::wcout << "Please enter this sentence again:\n";
			continue;
		}
		line_no++;

		// 将输入的表达式加工后添加进表达式内存空间
		library.Add(ExpressionParser(buffer));
		lines--;
	}
}

/**
 * \brief 初始化自动机
 */
void Lr0Parsers::InitDfa()
{
	// 新建一个S'->S节点
	root.containers.emplace_back(Node(&library.lib[0]));
}

/**
 * \brief 找到项目集规范族的各个节点
 * \param container 当前项目集规范族
 */
void Lr0Parsers::FindNext(Container* container)
{
	auto expression = container->containers;
	for (const auto& i : expression)
	{
		// 如果当前没有到表达式最后
		if (i.where != i.e->length)
		{
			Container* node = nullptr; // 节点指针
			wchar_t data = i.e->GetRight(static_cast<int>(i.where));
			int if_vn_exists = FALSE;


			// 创建节点时，检查节点是否已经存在，如果存在节点指针node拿出来
			for (auto value : container->nodes)
			{
				if (value->data == data)
				{
					if_vn_exists = TRUE;
					node = value;
					break;
				}
			}


			// 将目标表达式放入下一个项目集规范族，并将核向后移动
			Node next_node(i);
			next_node.where++;
			if (next_node == expression[0])
			{
				container->self_node.self = true;
				container->self_node.data = data;
			}
			else
			{
				// 如果不存在，那么添加一个新的节点放入项目集规范族的节点列表
				// 同时添加的时候查看有没有相同的项目集规范族
				if (if_vn_exists == FALSE)
				{
					node = FindSameContainer(&root, next_node);
					if (node == nullptr)
					{
						s++;
						node = new Container(s, data);
						node->containers.push_back(next_node);
						container->nodes.push_back(node);
					}
				}
				else
				{
					node->containers.push_back(next_node);
				}
			}
		}
		else
		{
			break;
		}
	}
	for (auto value : container->nodes)
	{
		// 找到下一个项目集规范族的表达式补全
		FindContainer(value);

		// 递归进入每个节点
		FindNext(value);
	}
}

/**
 * \brief 找到项目集规范族的所有表达式
 * \param container 项目集规范族指针
 */
void Lr0Parsers::FindContainer(Container* container)
{
	for (const Node& node : container->containers)
	{
		if (node.where != node.e->length)
		{
			NARRAY idx = library.FindVn(node.e->GetRight(static_cast<int>(node.where)));
			for (const auto& value : idx)
			{
				container->containers.emplace_back(Node(&library.lib[value]));
			}
		}
		else
		{
			break;
		}
	}
}

/**
 * \brief 查看有没有相同的节点，进行合并
 * \param container 递归节点
 * \param node 待添加的节点
 * \return 项目集规范指针
 */
Container* Lr0Parsers::FindSameContainer(const Container* container, const Node& node)
{
	Container* tmp = nullptr;
	for (auto& element : container->nodes)
	{
		if (element->containers[0] == node)
		{
			return new Container(*element);
		}
		tmp = FindSameContainer(element, node);
		if (tmp != nullptr)
		{
			break;
		}
	}
	return tmp;
}

/**
 * \brief 输出每个项目集规范族的内容
 * \param container 规范族节点
 */
void Lr0Parsers::OutputProject(const Container* container)
{
	wprintf(L"I%d: %c\n", container->s, container->data);
	for (const auto& node : container->containers)
	{
		std::wcout << node.e->GetLeft() << " -> ";
		for (unsigned i = 0; i < node.e->length; i++)
		{
			if (node.where == i)
			{
				std::wcout << "@";
			}
			std::wcout << node.e->right[i];
		}
		if (node.where == node.e->length)
		{
			std::wcout << "@";
		}
		std::wcout.put('\n');
	}
	for (const auto& node : container->nodes)
	{
		OutputProject(node);
	}
}

Lr0Parsers::~Lr0Parsers()
{
}

void Lr0Parsers::GetAnalysisTableColRow(const Container* next)
{
	for (auto node : next->nodes)
	{
		if (library.FindVn(node->data).empty())
		{
			T.vt_set.insert(node->data);
		}
		else
		{
			T.vn_set.insert(node->data);
		}
		if (s > T.max_index)
		{
			T.max_index = s;
		}
		GetAnalysisTableColRow(node);
	}
}

void Lr0Parsers::InitAnalysisTable()
{
	T.tAction.Set(std::vector<wchar_t>(T.vt_set.begin(), T.vt_set.end()), T.max_index);
	T.tGoto.Set(std::vector<wchar_t>(T.vn_set.begin(), T.vn_set.end()), T.max_index);
}

void Lr0Parsers::GetAnalysisTable(Container* next)
{
	int isFind = -1;
	auto tmp_a = &T.tAction.table[next->s];
	auto tmp_atype = &T.tAction.type[next->s];
	if (next->containers[0].e->GetLeft() == '`' && next->containers[0].where == next->containers[0].e->length)
	{
		tmp_a->at('#', Action::ACC);
		tmp_atype->at('#', Action::E);
	}
	else if (next->containers[0].e->length == next->containers[0].where)
	{
		for (auto& tmp : *tmp_a)
		{
			for (auto& i : library.lib)
			{
				if (next->containers[0].e == &i)
				{
					tmp = i.no;
					break;
				}
			}
		}
		for (auto& c : *tmp_atype)
		{
			c = Action::R;
		}
	}
	else
	{
		auto tmp_b = &T.tGoto.table[next->s];
		if (next->self_node.self)
		{
			auto iter = T.vt_set.find(next->self_node.data);
			if (iter != T.vt_set.end())
			{
				isFind = 1;
			}
			iter = T.vn_set.find(next->self_node.data);
			if (iter != T.vn_set.end())
			{
				isFind = 2;
			}

			if (isFind == 1)
			{
				tmp_a->at(next->self_node.data, next->s);
				tmp_atype->at(next->data, Action::S);
			}
			else if (isFind == 2)
			{
				tmp_b->at(next->self_node.data, next->s);
			}
		}

		for (auto node : *(next->GetNext()))
		{
			auto iter = T.vt_set.find(node->data);
			if (iter != T.vt_set.end())
			{
				isFind = 1;
			}
			iter = T.vn_set.find(node->data);
			if (iter != T.vn_set.end())
			{
				isFind = 2;
			}

			if (isFind == 1)
			{
				tmp_a->at(node->data, node->s);
				tmp_atype->at(node->data, Action::S);
			}
			else if (isFind == 2)
			{
				tmp_b->at(node->data, node->s);
			}
			GetAnalysisTable(node);
		}
	}
}

void Lr0Parsers::InputAnalysis(const wchar_t* input)
{
	symbol_stack.push_back('#');
	state_stack.push_back(0);
	int p = 0;
	while (true)
	{
		action_stack.push_back(*T.tAction.table[state_stack.back()].at(input[p]));
		state_history.push_back(state_stack);
		symbol_history.push_back(symbol_stack);

		std::vector<wchar_t> tmp;
		for (int i = p; i < wcslen(input); i++)
		{
			tmp.push_back(input[i]);
		}
		input_history.push_back(tmp);


		if (action_stack.back() == Action::ACC || action_stack.back() == -1)
		{
			type_stack.push_back(Action::E);
			goto_stack.push_back(-1);

			break;
		}
		if (*T.tAction.type[state_stack.back()].at(input[p]) == Action::S)
		{
			state_stack.push_back(*T.tAction.table[state_stack.back()].at(input[p]));
			symbol_stack.push_back(input[p]);
			goto_stack.push_back(-1);
			type_stack.push_back(Action::S);
			p++;
		}
		else if (*T.tAction.type[state_stack.back()].at(input[p]) == Action::R)
		{
			type_stack.push_back(Action::R);
			PopStack();
		}
	}
	delete[] input;
}

void Lr0Parsers::PopStack()
{
	int no = action_stack.back();
	int pop_nums = 0;
	wchar_t target = 0;
	for (const auto& value : library.lib)
	{
		if (no == static_cast<int>(value.no))
		{
			target = value.GetLeft();
			pop_nums = static_cast<int>(value.length);
			break;
		}
	}
	for (int i = pop_nums; i > 0; --i)
	{
		symbol_stack.pop_back();
		state_stack.pop_back();
	}
	symbol_stack.push_back(target);
	goto_stack.push_back(*T.tGoto.table[state_stack.back()].at(target));
	state_stack.push_back(goto_stack.back());
}

void Lr0Parsers::RecordStack()
{
}
