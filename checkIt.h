/*This class checks to make sure the file name is correct and that there are no file open errors*/

#pragma once
#ifndef CHECKIT_H
#define CHECKIT_H

#include<string>

class checkIt
{
private:
	std::string fileName;
public:
	checkIt(std::string s);
	std::string getFileName();
	~checkIt();
};

#endif 