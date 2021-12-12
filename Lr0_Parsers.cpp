// LR(0) Parsers build in 2021.12.08
// file name: Lr0_Parsers.cpp
// Edit by @Michael Zhou
#include <set>

#include "LR0_Parser.h"


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

Container::Container()
= default;

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
	FindContainer(&root);
	FindNext(&root, root.s);
	OutputProject(&root);
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
 * \brief 菜单、输入行号、输入表达式
 */
void Lr0Parsers::Run()
{
	PrintInfo();

	std::cout << "First, please enter the numbers of the sentences:" << std::endl;
	char buffer[1024]; // init input buffer
	while (true)
	{
		std::cin.getline(buffer, 1024);
		FLAG ifError = NORMAL;

		// 对输入检查是否是数字
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

	// 输入lr0语法
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
 * \param s 项目集规范族的编号
 */
void Lr0Parsers::FindNext(Container* container, int s)
{
	auto expression = container->containers;
	Container* node = nullptr; // 节点指针

	for (const auto& i : expression)
	{
		// 如果当前没有到表达式最后
		if (i.where != i.e->length)
		{
			char data = i.e->GetRight(static_cast<int>(i.where));
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

			// 如果不存在，那么添加一个新的节点放入项目集规范族的节点列表
			if (if_vn_exists == FALSE)
			{
				s++;
				node = new Container(s, data);
				container->nodes.push_back(node);
			}

			// 将目标表达式放入下一个项目集规范族，并将核向后移动
			Node next_node(i);
			next_node.where++;

			node->containers.push_back(next_node);
		}
	}
	for (auto value : container->nodes)
	{
		// 找到下一个项目集规范族的表达式补全
		FindContainer(value);

		// 递归进入每个节点
		FindNext(value, s);
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
		NARRAY idx = library.FindVn(node.e->GetRight(static_cast<int>(node.where)));
		for (const auto& value : idx)
		{
			container->containers.emplace_back(Node(&library.lib[value]));
		}
	}
	project_list.push_back(container); // 暂时没什么用
}

/**
 * \brief 输出每个项目集规范族的内容
 * \param container 规范族节点
 */
void Lr0Parsers::OutputProject(const Container* container)
{
	printf("I%d: %c\n", container->s, container->data);
	for (auto node : container->containers)
	{
		std::cout << node.e->GetLeft() << " -> ";
		for (unsigned i = 0; i < node.e->length; i++)
		{
			if (node.where == i)
			{
				std::cout << "@";
			}
			std::cout << node.e->right[i];
		}
		if (node.where == node.e->length)
		{
			std::cout << "@";
		}
		std::cout.put('\n');
	}
	for (auto node : container->nodes)
	{
		OutputProject(node);
	}
}

Lr0Parsers::~Lr0Parsers()
= default;
