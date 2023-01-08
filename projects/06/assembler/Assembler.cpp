#include "assembler.h"
#include "Parser.h"
#include "Code.h"

using std::string;
using std::fstream;
using std::vector;


int readFile(const string filename)
{
	string machineCode = "";
	fstream fin, fout;
	string line = "";
	string writeFile = retFileName(filename) + ".hack";
	vector<string> splitCode;

	//open the hack1 file
	fin.open(filename);
	if (fin.is_open())
	{
		fin.seekg(0, std::ios::end);
		if (fin.tellg() == 0)
		{
			fin.close();
			return -1;
		}
		else
		{
			fin.seekg(0, std::ios::beg);
			fout.open(writeFile, std::ios_base::out);
			if ((fout.is_open()))
			{
				std::cout << ".hack file created" << std::endl;
			}
			else
			{
				std::cout << "unable to create .hack file" << std::endl;
				exit(-1);
			}
			int line_num = 0;
			while (getline(fin, line))
			{
				//uncomment this line to show the lines from hack1 helper file
				// std::cout << "line " << line_num << ": " << line << "\n";
				line_num++;

				if (!(isComment(line)))
				{
					//if c instruction 
					if (line[0] != '@')
					{
						//if c instruction contains ;
						if (line.find(";") != string::npos)
						{
							if (line.find('=') == string::npos)
							{
								//if instruction does not contain = but contains ;. eg: 0:JMP
								splitCode = parser_string(line, ";");
							}
							else
							{
								//if instructions contains all operands eg: D=D-M;JMP
								//split line based on =
								splitCode = parser_string(line, "=");
								//split the 2nd operand based on ; to generate other operands
								vector<string> sp = parser_string(splitCode[1], ";");
								splitCode.pop_back();
								for (int i = 0; i < sp.size(); i++)
								{
									splitCode.push_back(sp[i]);
								}
							}
						}
						else
						{	
							//if c instruction is of the format D=M etc..
							splitCode = parser_string(line, "=");
						}
						machineCode = retCodeC(splitCode);
						//uncomment this to see the generated c instruction machine code
						// std::cout << machineCode << "\n";
						fout << machineCode << "\n";
					}
					else
					{
						machineCode = retCodeA(line);
						//uncomment this to see the generated a instruction machine code
						// std::cout << machineCode << "\n";
						fout << machineCode << "\n";
					}
				}
			}
			fout.close();
			fin.close();
			return 0;
		}
	}
	else
	{
		std::cout << "Cannot open assembly file";
		return -1;
	}
}



//run compiled file with "-f filename.asm"
int main(int argc, char **argv)
{
	//initialize the predefined symbol & lookup tables
	initTables();


	//Read assembly file from command line
	string asm_file, argument;
	for (int i = 0; i < argc; i++)
	{
		argument = argv[i];
		if (argument == "-f")
		{
			asm_file = argv[i + 1];
		}
	}

	//Generate a helper file without labels //first pass
	labelParser(asm_file);
	//Generate a helper file without varibales //2nd pass
	symbolParser(retFileName(asm_file) + ".hack0");
	std::cout << "Input file name: " << asm_file << std::endl;

	//genetare the machine code file
	int code = readFile(retFileName(asm_file) + ".hack1");
	if (code == 0)
	{
		std::cout << "sucessfully assembled " << asm_file << " into " << retFileName(asm_file) << ".hack" << std::endl;
	}
	else exit(-1);
	// remove helper files
	removeHelperFiles(retFileName(asm_file) + ".hack0");
	removeHelperFiles(retFileName(asm_file) + ".hack1");

	return 0;
}
