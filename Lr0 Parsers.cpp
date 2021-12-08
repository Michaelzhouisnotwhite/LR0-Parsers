// LR(0) Parsers build in 2021.12.08
// file name: Lr0 Parsers.cpp
// Edit by @Michael Zhou
#include "parsers.h"

Expression::~Expression()
{
	delete[] right;
}

Expression::Expression(char* expression)
{
	int len = strlen(expression);
	int temp_run_count = 1;
	int right_cnt = 0;

	for (int i = 0; i < len; i++)
	{
		if (expression[i] == ' ')
		{
			continue;
		}
		if (temp_run_count > 0)
		{
			left = expression[i];
			temp_run_count--;
			continue;
		}
		if (expression[i] == '-' && expression[i + 1]++ == '>')
		{
			i += 1;
			continue;
		}
		right_cnt++;
	}
	right = new char[right_cnt+1];
	right[right_cnt] = '\0';
	char* expression_last_ptr = &expression[len - 1];
	for (int i =right_cnt - 1; i >=0; i--)
	{
		right[i] = *expression_last_ptr;
		expression_last_ptr--;
	}
}

char Expression::GetProject() const
{
	return right[where_project];
}

void ExpressionList::Add(Expression e)
{
	
}
