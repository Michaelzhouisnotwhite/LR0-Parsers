// LR(0) Parsers build in 2021.12.14
// file name: IoProcess.h
// Edit by @Michael Zhou

#pragma once
#include "header.h"
#include "utils.h"
class IoProcess
{
	std::ifstream infile;
	wchar_t file_path[1024] = L"./config/grammar.txt";
	std::vector<wchar_t*> buffer_list;
	std::vector<wchar_t*>::iterator buffer_list_point;
public:
	FLAG ReadFromFile();
	wchar_t* GetFilePath();
	int GetFileLines() const;
	wchar_t* GetLine();
	~IoProcess();
};
