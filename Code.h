#ifndef CODE_H
#define CODE_H

#pragma once
#include <string>

/*
THIS CLASS CONTAINS THE HARD CODED BINARY VALUES FOR VARIOUS ASSSEMBLY CODE INSTRUCTIONS
*/
class Code
{
private:
	std::string destMnem, compMnem, jumpMnem;
public:
	Code(std::string d, std::string c, std::string j);
	std::string dest();
	std::string comp();
	std::string jump();

	~Code();
};

#endif // !CODE_H