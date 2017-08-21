#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#pragma once
#include <string>
#include <vector>

const int DEFAULT = 23;

/*
This class creates parallel vectors that hold the names of variables/labels and their corresponding memory address 
*/

class SymbolTable
{
private:
	std::string instruction;
	int memoryCounter = 16;
	std::vector<std::string>symbol;
	std::vector<int> address;

public:

	SymbolTable();
	void setDefault();
	void setInstruction(std::string s);
	bool preDefined();
	bool addSymbol();
	int getAddress();
	void addLabel(std::string s, int x);
	~SymbolTable();
};

#endif // !SYMBOLTABLE_H