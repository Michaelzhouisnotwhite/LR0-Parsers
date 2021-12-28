#include "IoProcess.h"

FLAG IoProcess::ReadFromFile()
{
	infile.open(file_path, std::ios::in);
	wchar_t buffer[1024];
	if (!infile.is_open())
	{
		return ERROR;
	}
	// while (infile.getline(buffer, sizeof(buffer)))
	// {
	// 	auto tmp = CopyStr(buffer);
	// 	buffer_list.push_back(tmp);
	// }
	return NORMAL;
}

wchar_t* IoProcess::GetFilePath()
{
	return file_path;
}

int IoProcess::GetFileLines() const
{
	return buffer_list.size();
}

wchar_t* IoProcess::GetLine()
{
	return *buffer_list_point++;
}

IoProcess::~IoProcess()
{
	for (auto value : buffer_list)
	{
		delete[] value;
	}
}
