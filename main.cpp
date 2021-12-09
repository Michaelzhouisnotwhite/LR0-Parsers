#include "LR0_Parser.h"
#include "utils.h"
int main()
{
	char test[] = "E -> aB";
	char test2[] = "aA|bB";
	char a[] = "1";
	Lr0Parsers().Run();
	return 0;
}