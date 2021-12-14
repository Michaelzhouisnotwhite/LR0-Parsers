// LR(0) Parsers build in 2021.12.14
// file name: IoProcess.h
// Edit by @Michael Zhou

#pragma once
#include "header.h"

class IoProcess
{
	std::ifstream infile;
	char file_path[1024] = "./config/Lr0_grammar";
	std::vector<char[1024]> buffer_list;
public:
	FLAG ReadFromFile();
	char* GetFilePath();
};
