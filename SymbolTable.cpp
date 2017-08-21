#include "SymbolTable.h"
#include <vector>
#include <string>


SymbolTable::SymbolTable()
{
}

//This class sets all the predefined variables and their adresses
void SymbolTable::setDefault()
{
	symbol.push_back("SP");
	symbol.push_back("LCL");
	symbol.push_back("ARG");
	symbol.push_back("THIS");
	symbol.push_back("THAT");
	symbol.push_back("R0");
	symbol.push_back("R1");
	symbol.push_back("R2");
	symbol.push_back("R3");
	symbol.push_back("R4");
	symbol.push_back("R5");
	symbol.push_back("R6");
	symbol.push_back("R7");
	symbol.push_back("R8");
	symbol.push_back("R9");
	symbol.push_back("R10");
	symbol.push_back("R11");
	symbol.push_back("R12");
	symbol.push_back("R13");
	symbol.push_back("R14");
	symbol.push_back("R15");
	symbol.push_back("SCREEN");
	symbol.push_back("KBD");
	address.push_back(0);
	address.push_back(1);
	address.push_back(2);
	address.push_back(3);
	address.push_back(4);
	address.push_back(0);
	address.push_back(1);
	address.push_back(2);
	address.push_back(3);
	address.push_back(4);
	address.push_back(5);
	address.push_back(6);
	address.push_back(7);
	address.push_back(8);
	address.push_back(9);
	address.push_back(10);
	address.push_back(11);
	address.push_back(12);
	address.push_back(13);
	address.push_back(14);
	address.push_back(15);
	address.push_back(16384);
	address.push_back(24576);
}

//this function sets instruction to the value parsed from the assembly code
void SymbolTable::setInstruction(std::string s)
{
	instruction = s;
	
}

//this function checks to see if the parsed value is already defined 
bool SymbolTable::preDefined()
{
	bool predefined = false;

	for (int i = 0; i < symbol.size(); i++)
	{
		if (instruction == symbol[i])
		{
			predefined = true;
			return predefined;
		}
	}

	return predefined;

}

//if the variable has not already been defined, then this function is called to add it to the vetor
bool SymbolTable::addSymbol()
{
	bool addedVar = true;

	if (memoryCounter < 16384) //total available memory
	{
		symbol.push_back(instruction);
		address.push_back(memoryCounter);
		memoryCounter++;
		return addedVar;
	}

	addedVar = false;
	return addedVar;
}

//this function returns the address of the corresponding variable
int SymbolTable::getAddress()
{
	int temp;
	for (int i = 0; i < symbol.size(); i++)
	{
		if (instruction == symbol[i])
		{
			temp = address[i];
			return temp;
		}
	}

	return 16; //if no address asw variable returns first allocatable memoery address
}

//this function adds labels and corresponding instruction line
void SymbolTable::addLabel(std::string s, int x)
{
		symbol.push_back(s);
		address.push_back(x);
}


SymbolTable::~SymbolTable()
{
}
