// LR(0) Parsers build in 2021.12.09
// file name: ExpressionLib.cpp
// Edit by @Michael Zhou
#include "ExpressionLib.h"

#include "utils.h"

Expression::Expression(const wchar_t left, const wchar_t* right, const unsigned no)
	: left(left),
	  length(0),
	  no(no)
{
	wcscpy_s(this->right, right);
	length = wcslen(right);
}

/**
 * \brief 拷贝构造函数
 * \param src copy source
 */
Expression::Expression(const Expression& src)
{
	left = src.left;
	wcscpy_s(right, src.right);
	length = src.length;
	no = src.no;
}

/**
 * \brief 返回表达式左边符号
 * \return 表达式左边的Vn
 */
wchar_t Expression::GetLeft() const
{
	return left;
}

/**
 * \brief 返回表达式右边的指定符号
 * \param index 核的位置（索引）
 * \return 符号
 */
wchar_t Expression::GetRight(const int index) const
{
	return right[index];
}

bool Expression::operator==(const Expression& exp) const
{
	if (!wcscmp(exp.right, right) && left == exp.left)
	{
		return true;
	}
	return false;
}

ExpressionLib::ExpressionLib() = default;

/**
 * \brief 从表达式解析器中添加一个表达式
 * \param e 表达式解析器（类）
 */
void ExpressionLib::Add(ExpressionParser e)
{
	// 如果是第一条表达式，那么添加一条 S'->S
	for (auto right : e.GetRight())
	{
		if (counter == 0)
		{
			
			auto temp = new wchar_t[2];
			temp[1] = '\0';
			temp[0] = e.GetLeft();
			lib.emplace_back(Expression('`', temp, counter));
			delete[] temp;
			counter += 1;
		}

		lib.emplace_back(Expression(e.GetLeft(), right, counter));
		counter++;
	}
	// 表达式集合（暂时没有用）
	int tmp_equal = 0;
	for (wchar_t vn : vn_set)
	{
		if (vn == e.GetLeft())
		{
			tmp_equal = 1;
		}
	}
	if (!tmp_equal)
	{
		vn_set.push_back(e.GetLeft());
	}
}


/**
 * \brief 找到由这个符号产生的表达式
 * \param non_terminal 符号
 * \return 由这个符号产生的表达式索引列表
 */
NARRAY ExpressionLib::FindVn(const wchar_t non_terminal) const
{
	NARRAY arr;
	for (unsigned i = 0; i < lib.size(); i++)
	{
		if (lib[i].left == non_terminal)
		{
			arr.push_back(i);
		}
	}
	return arr;
}

/**
 * \brief 第一条表达式
 * \return Expression
 */
Expression ExpressionLib::GetStart()
{
	return lib[0];
}
