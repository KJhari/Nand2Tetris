#ifndef __TABLELOOKUP_H__
#define  __TABLELOOKUP_H__

#include <string>
#include <vector>
#include <unordered_map>




extern std::unordered_map<std::string, std::string> jmpTable;
extern std::unordered_map<std::string, std::string> destTable;
extern std::unordered_map<std::string, std::string> compATable;
extern std::unordered_map<std::string, std::string> compNotATable;
extern std::unordered_map<std::string, std::string> symbolTable;

void initJumpTable(std::unordered_map<std::string, std::string> &jmpTable);
void initDestTable(std::unordered_map<std::string, std::string> &destTable);
void initCompNotATable(std::unordered_map<std::string, std::string> &compNotATable);
void initCompATable(std::unordered_map<std::string, std::string> &compNotATable);
void initSymbolTable(std::unordered_map<std::string, std::string> &symbolTable);

#endif
