// LR(0) Parsers build in 2021.12.09
// file name: utils.h
// Edit by @Michael Zhou

#pragma once
#include "header.h"
#define CRTDBG_MAP_ALLOC

#include <crtdbg.h>
#include <cstdlib>
inline void EnableMemLeakCheck()
{
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
}

void CopyStr(wchar_t** dst, const wchar_t* src);
wchar_t *CopyStr(const wchar_t* src);
/**
 * \brief 拆分字符串
 */
class SplitStr
{
	wchar_t* src;
	
	struct Pos
	{
		int left;
		int right;
		Pos(const int left, const int right):left(left), right(right){}
	};
	std::vector<Pos> poses;
public:
	explicit SplitStr(wchar_t* src, wchar_t c);
	int NSubStrs() const;
	void SubStr(wchar_t** dst, int no) const;
	wchar_t* SubStr(int no) const;
	
};