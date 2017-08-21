#include "Parser.h"
#include "code.h"
#include <string>
#include <bitset>
#include <fstream>
#include "checkIt.h"
#include "SymbolTable.h"
#include <vector>
#include <iostream>

std::string makeFileStub(std::string s);

int main(int argc, char* argv[])
{
	// Check the number of parameters
	if (argc < 2 || argc > 2)
	{
		// Tell the user how to run the program
		std::cout << "Usage: " << argv[0] << " <FILE NAME>" << std::endl;
		return 1;
	}

	std::string s = argv[1]; //tests file entered on command line for open errors
	checkIt testFile(s);
	s = testFile.getFileName();

	std::string destMnem; //holds the parsed parts of a c instruction
	std::string compMnem;
	std::string jumpMnem;
	std::string label;
	Command type; //enum value determining the type of command
	std::string aInstructionValue; //holds the value of an A instruction in string form
	int aInstructionInt; //converts A instruction to int
	int lInstructionInt;
	std::ofstream outputFile;
	std::string hackFile; //string to hold output file name
	SymbolTable lvar;
	bool labelTest;
	int lineCount = 0;
	

	hackFile = makeFileStub(s); //changes file extension to .txt
	hackFile += ".hack";

	outputFile.open(hackFile);
	
	Parser fileName(s); //initialized the parser with the file name
	lvar.setDefault(); //initializes vectors with predifned memory locations

	while (fileName.hasMoreCommands()) //goes through the file once and gets the names and instruction lines of all the labels
	{

		label = fileName.findLabel(); //parses the name of the label

		if (label != "null") 
		{
			lvar.addLabel(label, lineCount); //add a label to the vector along with its corresponding instruction line
		}


		if (fileName.notComment() & !fileName.blankLine() & !fileName.isLabel())
		{
			lineCount++; //if the line is not a blank line or comment, line count increments
		}

	}

	fileName.fileBegin(); //retruns the file stram back to the beggining of the file
	

	while (fileName.hasMoreCommands()) //only executes if there are more commands to be read from the aseembly file
	{
		
		std::string aInstructionBinaryString = "0"; //A instruction has a leading zero
		std::string cInstructionBinaryString = "111"; //C instruction has three leading 1's

		if (fileName.notComment() & !fileName.blankLine() & !fileName.isLabel()) //tests to see if line is blank or a comment
		{
			type = fileName.commandType(); //finds out if C, A or L instruction

			if (type == A_COMMAND)
			{
				aInstructionValue = fileName.symbol(); //gets the A instruction in string format
				aInstructionInt = atoi(aInstructionValue.c_str()); //converts string to int
				aInstructionBinaryString += std::bitset<15>(aInstructionInt).to_string(); //converts int to binary string...probably a better way to do this
				outputFile << aInstructionBinaryString << std::endl; //writes it to file
			}

			if (type == L_COMMAND)
			{
				
				aInstructionValue = fileName.symbol(); //gets the label name from the a instruction parser
			
				lvar.setInstruction(aInstructionValue); //sets that label to the symbol table class
				
				if (!lvar.preDefined()) //check if label or variable has already been defined
				{
					if (!lvar.addSymbol()) //tests to see if there was enough memory to allocate and allocates variable if memory allows
					{
						std::cout << "Memory allocation failed!" << std::endl;
						return 1;
					}
				}

				lInstructionInt = lvar.getAddress(); //gets the address associated with the label or variable
				aInstructionBinaryString += std::bitset<15>(lInstructionInt).to_string(); //converts to binary
				outputFile << aInstructionBinaryString << std::endl; //write to file
			}

			else if (type == C_COMMAND)
			{
				destMnem = fileName.dest(); //populates variables with the parsed c instruction
				compMnem = fileName.comp();
				jumpMnem = fileName.jump();

				Code convert(destMnem, compMnem, jumpMnem); //initializes the code class which converts c instructions to binary

				cInstructionBinaryString += convert.comp(); //concantenates string of binary to stub string for c instructions
				cInstructionBinaryString += convert.dest();
				cInstructionBinaryString += convert.jump();

				outputFile << cInstructionBinaryString << std::endl;
			}
		}
	}

	outputFile.close();

	return 0;
}

//This function removes the extension from the file name entered on the command line
std::string makeFileStub(std::string s)
{
	std::string fileName = s;
	std::string fileStub;


	for (size_t i = 0; i < fileName.length(); i++)
	{
		if (fileName[i] == '.')
		{
			return fileStub;
		}

		fileStub += fileName[i];
	}

	return fileStub;
}
