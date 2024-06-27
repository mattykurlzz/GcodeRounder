#include "GcodeRounder.h"

int main()
{
	GcodeRounder text("C:\\Users\\mamon\\Documents\\c++\\GcodeRounder\\example.TXT", 3, '.');
	text.write("C:\\Users\\mamon\\Documents\\c++\\GcodeRounder\\example_output.txt");
	return 0;
}