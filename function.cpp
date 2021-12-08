// LR(0) Parsers build in 2021.12.08
// file name: function.cpp
// Edit by @Michael Zhou
#include <iostream>
#include <cctype>
#include "header.h"
#define ERROR (-1)
#define NORMAL 1

void PrintInfo()
{
	std::string wrap = "\n";
	std::string info1 = "Please Enter a LR(0) grammar.";
	std::string info2 = "A line stands for one statement";
	std::string info3 = "type \"->\" refers to transfer to an sentences";
	std::cout << info1 << wrap;
	std::cout << info2 << wrap;
	std::cout << info3 << std::endl;
}

void Run()
{
	PrintInfo();

	std::cout << "First, please enter the numbers of the sentences:" << std::endl;
	char buffer[1024]; // init input buffer
	while (true)
	{
		std::cin >> buffer;
		int ifError = NORMAL;
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
	ExpressionList elist;
	while (lines)
	{
		std::cin >> buffer;
		if (Expression::CheckExpression(buffer) == ERROR)
		{
			std::cout << "Please enter this sentence again:\n";
			continue;
		}
		elist.Add(Expression(buffer));
		lines--;
	}
}
