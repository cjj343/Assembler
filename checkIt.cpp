#include "checkIt.h"


#include <iostream>
#include <string>
#include <fstream>

checkIt::checkIt(std::string s)
{
	std::ifstream inputFile;
	inputFile.open(s);
	std::string temp;

	while (inputFile.fail()) // if the file failed to open
	{
		std::cout << "There was an error opening the file. Please re-enter the file path." << std::endl;
		std::cin >> temp; //get new file path from user
		inputFile.open(temp); // try again
		s = temp; //assign to s regardless 
	}

	fileName = s; //if file opened successfully
	inputFile.close(); // close the file
}

std::string checkIt::getFileName()
{
	return fileName; //returns the correct file name

}


checkIt::~checkIt()
{
}
