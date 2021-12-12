// LR(0) Parsers build in 2021.12.09
// file name: ExpressionParser.cpp
// Edit by @Michael Zhou
#include "ExpressionParser.h"
#include "utils.h"

/**
 * \brief 将输入缓冲区的表达式加工成可用数据结构（左右分开）
 * \param input 输入缓冲区
 */
ExpressionParser::ExpressionParser(char* input)
{
	int len = strlen(input);
	int right_cnt = 0;
	int tmp_left_count = 1;

	for (int i = 0; i < len; i++)
	{
		if (input[i] == ' ')
		{
			continue;
		}
		if (tmp_left_count)
		{
			this->left = input[i];
			tmp_left_count--;
			continue;
		}
		if (input[i] == '-' || input[i] == '>')
		{
			// i += 1;
			continue;
		}
		right_cnt++;
	}
	right = new char[right_cnt + 1];
	right[right_cnt] = '\0';
	char* expression_last_ptr = &input[len - 1];
	int k = right_cnt - 1;
	while (k >= 0)
	{
		if (*expression_last_ptr != ' ')
		{
			right[k] = *expression_last_ptr;
			k--;
		}
		expression_last_ptr--;
	}

	// 如果有“|”符号，那么分开成两个表达式
	SplitStr str(right, '|');
	for (int i = 0; i < str.NSubStrs(); i++)
	{
		rightList.push_back(str.SubStr(i));
	}
}

ExpressionParser::~ExpressionParser()
{
	delete[] right;
	for (auto value : rightList)
	{
		delete[] value;
	}
}

SARRAY ExpressionParser::GetRight()
{
	return rightList;
}

char ExpressionParser::GetLeft() const
{
	return left;
}

/**
 * \brief 判断输入是否符合LR0表达式
 * \param expression 输入缓冲区字符串
 * \return 是否是LR0文法表达式
 */
FLAG ExpressionParser::CheckExpression(const char* expression)
{
	int left_cnt = 0;
	for (int i = 0; i < static_cast<int>(strlen(expression)); i ++)
	{
		if (expression[i] == ' ')
		{
			continue;
		}
		if (expression[i] == '-' && expression[i + 1] == '>')
		{
			break;
		}
		left_cnt++;
	}
	if (left_cnt > 1)
	{
		std::cout << "its not a grammar based on LR(0)!" << std::endl;
		return ERROR;
	}
	return NORMAL;
}
