// Harikrishnan Kokkanthara Jeevan
#include "TableLookup.h"

using std::string;
using std::unordered_map;

unordered_map<string, string> jmpTable = {};
unordered_map<string, string> destTable = {};
unordered_map<string, string> compATable = {};
unordered_map<string, string> compNotATable = {};
unordered_map<string, string> symbolTable = {};

// init jmp table
void initJumpTable(unordered_map<string, string> &jmpTable)
{
    jmpTable.insert({"NULL", "000"});
    jmpTable.insert({"JGT", "001"});
    jmpTable.insert({"JEQ", "010"});
    jmpTable.insert({"JGE", "011"});
    jmpTable.insert({"JLT", "100"});
    jmpTable.insert({"JNE", "101"});
    jmpTable.insert({"JLE", "110"});
    jmpTable.insert({"JMP", "111"});
}

// init destination table
void initDestTable(unordered_map<string, string> &destTable)
{
    destTable.insert({"NULL", "000"});
    destTable.insert({"M", "001"});
    destTable.insert({"D", "010"});
    destTable.insert({"MD", "011"});
    destTable.insert({"A", "100"});
    destTable.insert({"AM", "101"});
    destTable.insert({"AD", "110"});
    destTable.insert({"AMD", "111"});
}

// init comp table ,a=0
void initCompNotATable(unordered_map<string, string> &compNotATable)
{
    compNotATable.insert({"0", "101010"});
    compNotATable.insert({"1", "111111"});
    compNotATable.insert({"-1", "111010"});
    compNotATable.insert({"D", "001100"});
    compNotATable.insert({"A", "110000"});
    compNotATable.insert({"!D", "001101"});
    compNotATable.insert({"!A", "110001"});
    compNotATable.insert({"-D", "001111"});
    compNotATable.insert({"-A", "110011"});
    compNotATable.insert({"D+1", "011111"});
    compNotATable.insert({"A+1", "110111"});
    compNotATable.insert({"D-1", "001110"});
    compNotATable.insert({"A-1", "110010"});
    compNotATable.insert({"D+A", "000010"});
    compNotATable.insert({"D-A", "010011"});
    compNotATable.insert({"A-D", "000111"});
    compNotATable.insert({"D&A", "000000"});
    compNotATable.insert({"D|A", "010101"});
}

// init comp table ,a=1
void initCompATable(unordered_map<string, string> &compNotATable)
{

    compNotATable.insert({"M", "110000"});
    compNotATable.insert({"!M", "110001"});
    compNotATable.insert({"-M", "110011"});
    compNotATable.insert({"M+1", "110111"});
    compNotATable.insert({"M-1", "110010"});
    compNotATable.insert({"D+M", "000010"});
    compNotATable.insert({"D-M", "010011"});
    compNotATable.insert({"M-D", "000111"});
    compNotATable.insert({"D&M", "000000"});
    compNotATable.insert({"D|M", "010101"});
}

// init symbol table
void initSymbolTable(unordered_map<string, string> &symbolTable)
{
    symbolTable.insert({"R0", "0"});
    symbolTable.insert({"R1", "1"});
    symbolTable.insert({"R2", "2"});
    symbolTable.insert({"R3", "3"});
    symbolTable.insert({"R4", "4"});
    symbolTable.insert({"R5", "5"});
    symbolTable.insert({"R6", "6"});
    symbolTable.insert({"R7", "7"});
    symbolTable.insert({"R8", "8"});
    symbolTable.insert({"R9", "9"});
    symbolTable.insert({"R10", "10"});
    symbolTable.insert({"R11", "11"});
    symbolTable.insert({"R12", "12"});
    symbolTable.insert({"R13", "13"});
    symbolTable.insert({"R14", "14"});
    symbolTable.insert({"R15", "15"});
    symbolTable.insert({"SCREEN", "16384"});
    symbolTable.insert({"KBD", "24576"});
    symbolTable.insert({"SP", "0"});
    symbolTable.insert({"LCL", "1"});
    symbolTable.insert({"ARG", "2"});
    symbolTable.insert({"THIS", "3"});
    symbolTable.insert({"THAT", "4"});
}
