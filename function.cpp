// LR(0) Parsers build in 2021.12.08
// file name: function.cpp
// Edit by @Michael Zhou

#include "function.h"

void CopyStr(char* dst, const char* src)
{
	dst = new char[strlen(src) + 1];
	dst[strlen(src)] = '\0';
	for (int i = 0; i < static_cast<int>(strlen(src)); i++)
	{
		dst[i] = src[i];
	}
}


