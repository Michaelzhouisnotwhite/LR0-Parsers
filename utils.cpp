// LR(0) Parsers build in 2021.12.09
// file name: utils.cpp
// Edit by @Michael Zhou
#include "utils.h"

SplitStr::SplitStr(char* src, const char c): src(src)
{
	std::vector<char*> dst;
	int l = 0;

	for (int i = 0; i < static_cast<int>(strlen(src)); i++)
	{
		if (src[i] == c)
		{
			poses.emplace_back(Pos(l, i - 1));
			l = i + 1;
		}
	}
	poses.emplace_back(Pos(l, static_cast<int>(strlen(src)) - 1));
}

int SplitStr::NSubStrs() const
{
	return poses.size();
}

void SplitStr::SubStr(char** dst, const int no) const
{
	Pos temp = poses[no];
	int length = temp.right - temp.left + 2;
	*dst = new char[length];
	char *ddst = *dst;
	ddst[length - 1] = '\0';
	for (unsigned i = 0; i < strlen(ddst); i++)
	{
		ddst[i] = src[i + temp.left];
	}
}

char* SplitStr::SubStr(const int no) const
{
	Pos temp = poses[no];
	int length = temp.right - temp.left + 2;
	auto dst = new char[length];
	dst[length - 1] = '\0';
	for (unsigned i = 0; i < strlen(dst); i++)
	{
		dst[i] = src[i + temp.left];
	}
	return dst;
}
