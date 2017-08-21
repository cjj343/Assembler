#include "Parser.h"
#include <cctype>
#include <iostream>


Parser::Parser(std::string s)
{
	fileName = s; //initializes string with fileName that has already been tested in main for file open errors
	inputFile.open(fileName); //opens the file
}

//this function tests for more lines in the asm source file and loads the current instruction into a variable
bool Parser::hasMoreCommands()
{
	std::cin.clear();

	if(std::getline(inputFile, instruction))
	{
		return true;
	}

	return false; //if no more instructions, return false
}

//this function returns the type of instruction of the current line of source file
Command Parser::commandType()
{
	for (size_t i = 0; i < instruction.length(); i++)
	{
		if (instruction[i] != ' ')
		{
			if (instruction[i] == '@' & (instruction[i+1] >= 48 & instruction[i+1] <= 57))
			{
				type = A_COMMAND;
				return type; //true if a instruction referencing a constant integer
			}

			else if ((instruction[i] == '@') & ((isalpha(instruction[i+1])) || (instruction[i+1] == '.') || (instruction[i+1] == '_') || (instruction[i+1] == '$') || (instruction[i+1] == ':')))
			{
				type = L_COMMAND;
				return type; //true if a instruction with user defined variable or label
			}

			else
			{
				type = C_COMMAND;
				return type; //otherwise c command
			}
		}
	}

	return type;
}

//THIS FUNCTION PARSES THE INSTRUCTION TO FIND A LABEL OR SYMBOL
std::string Parser::symbol()
{
	std::string aInstructionValue;

	for (size_t i = 0; i < instruction.length(); i++)
	{
		if (instruction[i] == '/' & instruction[i+1] == '/')
		{
			return aInstructionValue;
		}

		if (instruction[i] != '@')
		{
			if (instruction[i] != ' ')
			{
				aInstructionValue += instruction[i];
			}
		}
	}

	

	 return aInstructionValue;
}

//THIS FUNCTION PARSES THE INSTRUCTION TO FIND A MEMORY LOCATION INSTRUCTION
std::string Parser::dest()
{
	bool isDest = false;
	std::string destMnem;
	int destStart;
	std::string null = "null"; //MARKER FOR C INSTRUCTION WITHOUT DESTINATION

	for (size_t i = 0; i < instruction.length(); i++)
	{
		if (instruction[i] == '/' & instruction[i + 1] == '/')
		{
			break;
		}

		if (instruction[i] != ' ')
		{
			if (instruction[i] == '=')
			{
				destStart = i;
				isDest = true;
			}
		}
		
	}

	if (isDest)
	{
		for (int i = 0; i < destStart; i++)
		{
			if (instruction[i] != ' ')
			{
				destMnem += instruction[i];
			}
		}
		
		return destMnem;
	}

	return null;

}

//THIS FUNCTION PARSES THE INSTRUCTION TO FIND A COMPUATION INSTRUCTION
std::string Parser::comp()
{
	bool isComp = false;
	bool isCompJump = false;
	std::string compMnem;
	int startComp;
	int startCompJump;
	std::string null = "null"; //MARKS IF NO COMP INSTRUCTION

	for (size_t i = 0; i < instruction.length(); i++)
	{

		if (instruction[i] == '/' & instruction[i + 1] == '/')
		{
			break;
		}
	
		if (instruction[i] != ' ')
		{
			if (instruction[i] == '=')
			{
				startComp = i + 1;
				isComp = true;
			}
		}

		if (instruction[i] != ' ')
		{
			if (instruction[i] == ';')
			{
				startCompJump = i;
				isCompJump = true;
			}
		}
	}


	if (isComp)
	{
		for (size_t i = startComp; i < instruction.length(); i++)
		{
			if (instruction[i] == '/' & instruction[i+1] == '/')
			{
				return compMnem;
			}

			if (instruction[i] != ' ')
			{
				compMnem += instruction[i];
			}
		}

	return compMnem;
	}

	else if (isCompJump)
	{
		for (int i = 0; i < startCompJump; i++)
		{
			if (instruction[i] != ' ')
			{
				compMnem += instruction[i];
			}
		}

		return compMnem;
	}

	return null;

}

std::string Parser::jump()
{

	bool isJump = false;
	std::string jumpMnem;
	int startJump;
	std::string null = "null";


	for (size_t i = 0; i < instruction.length(); i++)
	{

		if (instruction[i] == '/' & instruction[i + 1] == '/')
		{
			break;
		}

		if (instruction[i] != ' ')
		{
			if (instruction[i] == ';')
			{
				startJump = i + 1;
				isJump = true;
			}
		}
	}

	if (isJump)
	{
		for (size_t i = startJump; i < instruction.length(); i++)
		{
			if (instruction[i] == '/' & instruction[i+1] == '/')
			{
				return jumpMnem;
			}

			if (instruction[i] != ' ')
			{
				jumpMnem += instruction[i];
			}
		}

		return jumpMnem;
	}

	return null;

}

//THIS FUNCTION TESTS TO SEE IF LINE IS A COMMENT LINE
bool Parser::notComment()
{
	bool notComment = true;

	for (size_t i = 0; i < instruction.length(); i++)
	{
		if ((instruction[i] >= 65 & instruction[i] <= 122) || (instruction[i] == '.') || (instruction[i] == '_') || (instruction[i] == '$') || (instruction[i] == ':') || (instruction[i] == '@') || (instruction[1] >= 48 & instruction[1] <= 57))
		{
			return notComment;
		}

		else if ((instruction[i] == '/') & (instruction[i + 1] == '/'))
		{
			notComment = false;
			return notComment;
		}
	}

	return notComment;
}

//THIS FUNCTION CHECKS TO SEE IF LINE IS BLANK
bool Parser::blankLine()
{
	bool blank = true;

	for (size_t i = 0; i < instruction.length(); i++)
	{
		if (instruction[i])
		{
			blank = false;
			return blank;
		}
	}
	
	return blank;

}

//THIS FUNCTION HANDLES PARSING LABELS
std::string Parser::findLabel()
{
	std::string label;
	bool labelTest;

	label = "";
	labelTest = false;
	std::string null = "null";

	if (notComment() & !blankLine())
	{

		for (size_t i = 0; i < instruction.length(); i++)
		{
			if (instruction[i] == '/' & instruction[i + 1] == '/')
			{
				break;
			}

			if (instruction[i] == '(')
			{
				labelTest = true;
				break;
			}
		}

		if (labelTest)
		{
			for (size_t i = 0; i < instruction.length(); i++)
			{
				if (instruction[i] == '/' & instruction[i + 1] == '/')
				{
					return label;
				}

				if ((instruction[i] != '(') & (instruction[i] != ')'))
				{
					if (instruction[i] != ' ')
					{
						label += instruction[i];
					}
				}	
			}

			return label;

		}

		return null;
	}

	return null;
}

//RETRUNS FILE STREAM BACK TO BEGGINING
void Parser::fileBegin()
{
	inputFile.clear();
	inputFile.seekg(0, ios::beg);
}


//THIS FUNCTION CHECKS TO SEE IF THE LINE IS A LABEL
bool Parser::isLabel()
{
	bool label = false;

	for (size_t i = 0; i < instruction.length(); i++)
	{
		if (instruction[i] == '/' & instruction[i + 1] == '/')
		{
			break;
		}

		if (instruction[i] == '(')
		{
			label = true;
			return label;
		}
	}

	return label;

}

//DESTRUCTOR CLOSES THE INPUT FILE
Parser::~Parser()
{
	inputFile.close();
}
