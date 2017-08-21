#include "Code.h"


//CONSTRUCTOR SETS VALUES PARSED FROM THE ASM CODE
Code::Code(std::string d, std::string c, std::string j)
{
	destMnem = d;
	compMnem = c;
	jumpMnem = j;

}


//THIS FUNCTION SETS THE CORRESPONDNG BINARY CODE FROM THE PARSED INSTRUCTION
std::string Code::dest()
{
	if (destMnem == "null")
	{
		return "000";
	}

	else if (destMnem == "M")
	{
		return "001";
	}

	else if (destMnem == "D")
	{
		return "010";
	}

	else if (destMnem == "MD")
	{
		return "011";
	}

	else if (destMnem == "A")
	{
		return "100";
	}

	else if (destMnem == "AM")
	{
		return "101";
	}

	else if (destMnem == "AD")
	{
		return "110";
	}

	else if (destMnem == "AMD")
	{
		return "111";
	}

	return "000";
}

//THIS FUNCTION SETS THE CORRESPONDNG BINARY CODE FROM THE PARSED INSTRUCTION
std::string Code::comp()
{
	if (compMnem == "0")
	{
		return "0101010";
	}

	else if (compMnem == "1")
	{
		return "0111111";
	}

	else if (compMnem == "-1")
	{
		return "0111010";
	}

	else if (compMnem == "D")
	{
		return "0001100";
	}

	else if (compMnem == "A")
	{
		return "0110000";
	}

	else if (compMnem == "!D")
	{
		return "0001101";
	}
	else if (compMnem == "!A")
	{
		return "0110001";
	}

	else if (compMnem == "-D")
	{
		return "0001111";
	}

	else if (compMnem == "-A")
	{
		return "0110011";
	}

	else if (compMnem == "D+1")
	{
		return "0011111";
	}

	else if (compMnem == "A+1")
	{
		return "0110111";
	}

	else if (compMnem == "D-1")
	{
		return "0001110";
	}

	else if (compMnem == "A-1")
	{
		return "0110010";
	}

	else if (compMnem == "D+A")
	{
		return "0000010";
	}

	else if (compMnem == "D-A")
	{
		return "0010011";
	}

	else if (compMnem == "A-D")
	{
		return "0000111";
	}

	else if (compMnem == "D&A")
	{
		return "0000000";
	}

	else if (compMnem == "D|A")
	{
		return "0010101";
	}

	else if (compMnem == "M")
	{
		return "1110000";
	}

	else if (compMnem == "!M")
	{
		return "1110001";
	}

	else if (compMnem == "-M")
	{
		return "1110011";
	}

	else if (compMnem == "M+1")
	{
		return "1110111";
	}

	else if (compMnem == "M-1")
	{
		return "1110010";
	}

	else if (compMnem == "D+M")
	{
		return "1000010";
	}

	else if (compMnem == "D-M")
	{
		return "1010011";
	}

	else if (compMnem == "M-D")
	{
		return "1000111";
	}

	else if (compMnem == "D&M")
	{
		return "1000000";
	}

	else if (compMnem == "D|M")
	{
		return "1010101";
	}

	else if (compMnem == "null")
	{
		return "0000000";
	}

	return "0000000";
}

//THIS FUNCTION SETS THE CORRESPONDNG BINARY CODE FROM THE PARSED INSTRUCTION
std::string Code::jump()
{
	if (jumpMnem == "null")
	{
		return "000";
	}

	else if (jumpMnem == "JGT")
	{
		return "001";
	}

	else if (jumpMnem == "JEQ")
	{
		return "010";
	}

	else if (jumpMnem == "JGE")
	{
		return "011";
	}

	else if (jumpMnem == "JLT")
	{
		return "100";
	}

	else if (jumpMnem == "JNE")
	{
		return "101";
	}

	else if (jumpMnem == "JLE")
	{
		return "110";
	}

	else if (jumpMnem == "JMP")
	{
		return "111";
	}

	return "000";
}


Code::~Code()
{
}
