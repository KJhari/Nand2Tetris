#ifndef __PARSER_H__
#define __PARSER_H__

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

bool isComment(const string s);
vector<string> parser_string(string line,string delimiter);
string retFileName(string filename);


#endif