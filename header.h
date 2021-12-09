// LR(0) Parsers build in 2021.12.08
// file name: header.h
// Edit by @Michael Zhou

#pragma once
#include <iostream>
#include <cctype>
#include <vector>
#include <string>

#define ERROR (-1)
#define NORMAL 1
#define NARRAY std::vector<int>
#define SARRAY std::vector<char*>
#define FLAG int

struct Pos
{
	int left;
	int right;
};

