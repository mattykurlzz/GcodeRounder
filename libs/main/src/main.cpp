#include "GcodeRounder.h"

int main()
{
	GcodeRounder text(".\\test\\example.TXT", 2, '.');
	text.write(".\\test\\example_output.txt");
	return 0;
}