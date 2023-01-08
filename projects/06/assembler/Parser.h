#ifndef __PARSER_H__
#define __PARSER_H__

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <filesystem>


bool isComment(const std::string s);
std::vector<std::string> parser_string(std::string line,std::string delimiter);
std::string retFileName(std::string filename);
void labelParser(std::string filename);
void symbolParser(std::string filename);
std::string removeComments(std::string prgm);
void removeHelperFiles(std::string filename);

#endif