#ifndef PARSER_H
#define PARSER_H
#pragma once
#include <string>
#include <fstream>
#include "SymbolTable.h"

using std::ios;

/*
This class handles opening the input file stream and parsing lines of assembly code
*/

enum Command { A_COMMAND, L_COMMAND, C_COMMAND}; //enum data type to signify which type of command is being read from file

class Parser
{
private:
	std::string fileName;
	std::ifstream inputFile;
	std::string instruction;
	std::string temp;
	Command type;
	
	

public:
	Parser(std::string s);
	bool hasMoreCommands();
	Command commandType();
	std::string symbol();
	std::string dest();
	std::string comp();
	std::string jump();
	bool notComment();
	bool blankLine();
	std::string findLabel();
	bool isLabel();
	void fileBegin();

	~Parser();
};

#endif