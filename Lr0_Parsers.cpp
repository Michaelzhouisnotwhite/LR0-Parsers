// LR(0) Parsers build in 2021.12.08
// file name: Lr0_Parsers.cpp
// Edit by @Michael Zhou
#include "LR0_Parser.h"


Node::Node(const Expression e)
{
	this->e = e;
}

Lr0Parsers::Lr0Parsers()
{
	Run();
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

void Lr0Parsers::Parsing()
{
	root.nodes.emplace_back(Node(library.lib[0]));
	for (auto value : library.lib)
	{
		if (value.GetRight())
		{
			
		}
	}
}

