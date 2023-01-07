#ifndef __TABLELOOKUP_H__
#define  __TABLELOOKUP_H__

#include <string>
#include <vector>
#include <unordered_map>


using std::string;
using std::unordered_map;

extern unordered_map<string, string> jmpTable;
extern unordered_map<string, string> destTable;
extern unordered_map<string, string> compATable;
extern unordered_map<string, string> compNotATable;
extern unordered_map<string, string> symbolTable

void initJumpTable(unordered_map<string, string> &jmpTable);
void initDestTable(unordered_map<string, string> &destTable);
void initCompNotATable(unordered_map<string, string> &compNotATable);
void initCompATable(unordered_map<string, string> &compNotATable);

#endif
