// GcodeRounder.cpp : 
//

#include "GcodeRounder.h"

GcodeRounder::GcodeRounder(std::string pathToSource, unsigned maxFloatPrecision, char delimeter)
{
	file.open(pathToSource);
	this->delimeter = delimeter;

	if (!file.is_open()) {
		std::cerr << "Failed to open file: " << pathToSource << std::endl;
		return;
	}

	this->maxFloatPrecigion = maxFloatPrecision;

	scanText();
}

GcodeRounder::~GcodeRounder() {
	file.close();
}

int GcodeRounder::scanText() {
	for (std::string line; std::getline(file, line);)
	{
		std::string word;
		std::istringstream lineStream(line);
		while (lineStream >> word)
		{
			if (word.find(delimeter) != std::string::npos)
			{
				word = handleFloatInText(word);
			}

			bufferText.append(word + " ");
		}
		bufferText.append("\n");
	}

	bufferText.pop_back();
	
	return 0;
}

std::string GcodeRounder::handleFloatInText(std::string word)
{
	std::string::iterator iterator; 
	std::string dictionary = "1234567890";
	dictionary += delimeter;

	std::string textNonNumber = "";
	std::string textNumber = "";

	float numberToRound = 0;
	unsigned naturalPart = 0;
	unsigned decimalPart = 0;

	for (iterator = word.begin(); dictionary.find(*iterator) == std::string::npos; iterator++)
	{
		textNonNumber += *iterator;
	}
	textNumber = word.substr(std::distance(word.begin(), iterator));

	if (!isNumber(textNumber)) { return word; }
	if (!isLongFloat(textNumber)) { return word; }

	// ToDo: do steps 2-7
	numberToRound = std::stof(textNumber);
	naturalPart = int(std::floor(numberToRound));
	decimalPart = std::round(numberToRound * (std::pow(10, maxFloatPrecigion))) - naturalPart * (std::pow(10, maxFloatPrecigion));

	textNumber = std::to_string(naturalPart) + delimeter + std::to_string(decimalPart);

	for (std::string::reverse_iterator zeroPopper = textNumber.rbegin(); *zeroPopper == '0';)
	{
		zeroPopper++;
		textNumber.pop_back();
	}

	return textNonNumber+textNumber;
}

int GcodeRounder::write(std::string pathToFile) const
{
	std::ofstream outputFile(pathToFile);
	if (!outputFile.is_open())
	{
		std::cerr << "error creating " << pathToFile << std::endl;
		return 1;
	}
	if (!(outputFile << bufferText))
	{
		std::cerr << "error writing to " << pathToFile << std::endl;
		return 1;
	}
	return 0;
}

bool GcodeRounder::isNumber(std::string numberString) const
{
	std::string dictionary = "1234567890";
	dictionary += delimeter;
	for (std::string::iterator iterator = numberString.begin(); iterator != numberString.end(); iterator++)
	{
		if (dictionary.find(*iterator) == std::string::npos) { return false; }
	}
	return true;
}

bool GcodeRounder::isLongFloat(std::string textFloat) const
{
	unsigned currentPrecigion = 0;
	for (std::string::reverse_iterator rIterator = textFloat.rbegin(); *rIterator != delimeter; rIterator++)
	{
		currentPrecigion++;
	}
	return currentPrecigion > maxFloatPrecigion;
}

