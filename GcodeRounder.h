// GcodeRounder.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include <sstream>
#include <cmath>

class GcodeRounder
{
public: 
	GcodeRounder(std::string pathToSource, unsigned maxFloatPrecision, char delimeter);
	int write(std::string pathToFile) const;
	~GcodeRounder();

private:
	std::ifstream file;
	std::string bufferText;
	char delimeter;
	unsigned maxFloatPrecigion;
	int scanText();

	std::string handleFloatInText(std::string word);
	bool isNumber(std::string numberString) const;
	bool isLongFloat(std::string textFloat) const;

};
