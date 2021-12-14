#include "IoProcess.h"

FLAG IoProcess::ReadFromFile()
{
	infile.open(file_path, std::ios::in);
	char buffer[1204];
	if (!infile.is_open())
	{
		return ERROR;
	}
	while (infile.getline(buffer, sizeof(buffer)))
	{
		
	}
}

char* IoProcess::GetFilePath()
{
	return file_path;
}
