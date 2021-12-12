// LR(0) Parsers build in 2021.12.09
// file name: utils.h
// Edit by @Michael Zhou

#pragma once
#include "header.h"
/**
 * \brief 拆分字符串
 */
class SplitStr
{
	char* src;
	
	struct Pos
	{
		int left;
		int right;
		Pos(const int left, const int right):left(left), right(right){}
	};
	std::vector<Pos> poses;
public:
	explicit SplitStr(char* src, char c);
	int NSubStrs() const;
	void SubStr(char** dst, int no) const;
	char* SubStr(int no) const;
	
};