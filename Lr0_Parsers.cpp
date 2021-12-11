// LR(0) Parsers build in 2021.12.08
// file name: Lr0_Parsers.cpp
// Edit by @Michael Zhou
#include <set>

#include "LR0_Parser.h"


Node::Node(Expression* e)
{
	this->e = e;
}

Node::Node(const Node& node)
{
	where = node.where;
	e = node.e;
}

Container::Container(const int s, const char data)
	: s(s),
	  data(data)
{
}

Container::~Container()
{
	for (auto node : nodes)
	{
		delete node;
	}
}

Lr0Parsers::Lr0Parsers()
{
	Run();
	InitDfa();
}

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


void Lr0Parsers::Run()
{
	PrintInfo();

	std::cout << "First, please enter the numbers of the sentences:" << std::endl;
	char buffer[1024]; // init input buffer
	while (true)
	{
		std::cin.getline(buffer, 1024);
		FLAG ifError = NORMAL;
		for (int i = 0; i < static_cast<int>(strlen(buffer)); i++)
		{
			if (!isdigit(buffer[i]))
			{
				std::cout << "Error: the numbers of the sentence are not int" << std::endl;
				ifError = ERROR;
				break;
			}
		}
		if (ifError == NORMAL)
		{
			break;
		}
		std::cout << "please enter again:" << std::endl;
	}

	char* tmp_buffer_end;
	long lines = strtol(buffer, &tmp_buffer_end, 10);

	std::cout << "Enter the LR(0) Grammar:" << std::endl;
	int line_no = 1;
	while (lines)
	{
		std::cout << "[" << line_no << "]" << " > ";
		std::cin.getline(buffer, 1024);
		if (ExpressionParser::CheckExpression(buffer) == ERROR)
		{
			std::cout << "Please enter this sentence again:\n";
			continue;
		}
		line_no++;
		library.Add(ExpressionParser(buffer));
		lines--;
	}
}

void Lr0Parsers::InitDfa()
{
	root.containers.emplace_back(Node(&library.lib[0]));
	FindContainer(&root);
	FindNext(&root);
}

void Lr0Parsers::FindNext(Container* container)
{
	auto expression = container->containers;
	std::vector<char> vt_list;
	std::vector<char> vn_list;
	Container* node = nullptr;
	int container_s = container->s;
	for (const auto& i : expression)
	{
		if (i.where != i.e->length)
		{
			char data = i.e->GetRight(static_cast<int>(i.where));
			int if_vn_exists = -1;
			for (auto value : container->nodes)
			{
				if (value->data == data)
				{
					if_vn_exists = 1;
					node = value;
					break;
				}
			}
			if (if_vn_exists == -1)
			{
				container_s++;
				node = new Container(container_s, data);
				container->nodes.push_back(node);
			}
			Node next_node(i);
			next_node.where++;
			node->containers.push_back(next_node);
			FindContainer(node);
			// FindNext(node);
		}
	}
	for (auto value : container->nodes)
	{
		FindNext(value);
	}
}

void Lr0Parsers::FindContainer(Container* container)
{
	for (const Node& node : container->containers)
	{
		NARRAY idx = library.FindVn(node.e->GetRight(static_cast<int>(node.where)));
		for (const auto& value : idx)
		{
			container->containers.emplace_back(Node(&library.lib[value]));
		}
	}
	// FindNext(container);
}

Lr0Parsers::~Lr0Parsers()
= default;
