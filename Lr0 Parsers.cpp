// LR(0) Parsers build in 2021.12.08
// file name: Lr0 Parsers.cpp
// Edit by @Michael Zhou
#include <iostream>

#include "parsers.h"
#define ERROR (-1)
#define NORMAL 1

Expression::~Expression()
{
	delete[] right;
}

Expression::Expression(char* expression)
{
	int len = strlen(expression);
	int right_cnt = 0;
	where_project = 0;

	this->left = expression[0];

	for (int i = 1; i < len; i++)
	{
		if (expression[i] == ' ')
		{
			continue;
		}
		// if (temp_run_count > 0)
		// {
		// 	left = expression[i];
		// 	temp_run_count--;
		// 	continue;
		// }
		if (expression[i] == '-' && expression[i + 1]++ == '>')
		{
			i += 1;
			continue;
		}
		right_cnt++;
	}
	right = new char[right_cnt + 1];
	right[right_cnt] = '\0';
	char* expression_last_ptr = &expression[len - 1];
	for (int i = right_cnt - 1; i >= 0; i--)
	{
		right[i] = *expression_last_ptr;
		expression_last_ptr--;
	}
}

Expression::Expression(const Expression& source)
{
	left = source.left;
	right = source.right;
	where_project = source.where_project;
}

char Expression::GetProject() const
{
	return right[where_project];
}

char Expression::GetLeft() const
{
	return left;
}

void Expression::NextProject()
{
	where_project++;
}

int Expression::CheckExpression(char* expression)
{
	int left_cnt = 0;
	for (int i = 0; i < static_cast<int>(strlen(expression)); i ++)
	{
		left_cnt++;
		if (expression[i] == '-' && expression[i + 1]++ == '>')
		{
			break;
		}
	}
	if (left_cnt > 1)
	{
		std::cout << "its not a grammar based on LR(0)!" << std::endl;
		return ERROR;
	}
	return NORMAL;
}

void ExpressionList::Add(const Expression e)
{
	eList.push_back(e);
}

ARRAY ExpressionList::Find(const char non_terminal) const
{
	ARRAY temp_arr;
	for (int i = 0; i < static_cast<int>(eList.size()); i ++)
	{
		if (non_terminal == eList[i].GetLeft())
		{
			temp_arr.push_back(i);
		}
	}
	return temp_arr;
}

Node::Node(const Expression& e)
{
	node.push_back(e);
}

void Node::Contain(const Expression& e)
{
	node.push_back(e);
}

void Node::Goto(const Expression& e)
{
	node.push_back(e);
}
