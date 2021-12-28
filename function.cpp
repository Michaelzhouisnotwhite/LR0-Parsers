// LR(0) Parsers build in 2021.12.08
// file name: function.cpp
// Edit by @Michael Zhou

#include "function.h"

void Welcome()
{
	std::wcout << "Welcome to LR(0) Parsers! Enter 'h' to get help" << std::endl;
}

void Menu()
{
	std::wcout << "GETTING HELP" << std::endl;
	std::wcout << "------------" << std::endl;
	std::wcout << std::endl;
	std::wcout << "    f   -> Read grammar from file: './config/grammar.txt'" << std::endl;
	std::wcout << "    i   -> Read grammar from YOUR input" << std::endl;
	// std::wcout << "    f   -> Read grammar from file: './config/grammar.txt'";
}

void SwitchInput(wchar_t* buffer)
{
	wchar_t choice[2][2] = {L"f", L"i"};
	for (unsigned i =0; i < sizeof(buffer); i++)
	{
		if (buffer[i] == ' ')
		{
			int blank_idx = i;
		}
		else
		{
			break;
		}
	}
}

void PrepareInputBuffer()
{
	std::wcout << "> ";
}

void Lr0ParsersConsole()
{
	Welcome();
	while (true)
	{
		wchar_t buffer[1024];
		PrepareInputBuffer();
		std::wcin.getline(buffer, 1024);
		Lr0Parsers parsers;
	}
}
