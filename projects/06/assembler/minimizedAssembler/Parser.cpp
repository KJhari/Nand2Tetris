#include "parser.h"

bool isComment(const string s)
{
    if(s[0] == '/')
    {
        return true;
    }

    else return false;
}

vector<string>& splitCodes(string line, const string delimiter, vector<string> &res)
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    while ((pos_end = line.find (delimiter, pos_start)) != string::npos) 
        {
            token = line.substr (pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            res.push_back (token);
        }

        res.push_back (line.substr (pos_start));

        return res;
}

vector<string> parser_string(string line,const string delimiter)
{
    vector<string> res;

    if(delimiter=="=" && (line.find(";")==string::npos))
    {
        res = splitCodes(line,delimiter,res);
        res.push_back("noJMP");
    }    

    else if(delimiter==";" && (line.find("=")==string::npos) && line[0]=='0')
    {
        res.push_back("noDest");
        vector<string> res2= splitCodes(line,delimiter,res);
        res = res2;
    }

       else if((delimiter==";") && (line.find("=")==string::npos) && (line[1]==';'))
    {
        std::cout<<line<<std::endl; 
        res.push_back("noDest");
        vector<string> res2= splitCodes(line,delimiter,res);
        res = res2;
    }

    else if(delimiter==";" && (line.find("=")==string::npos))
    {
        
        vector<string> res2= splitCodes(line,delimiter,res);
        res = res2;
    }

    else
    {
       res = splitCodes(line,delimiter,res);
    }

    return res;

}

string retFileName(string filename)
{
    size_t lastindex = filename.find_last_of("."); 
    string fileNoExstention = filename.substr(0, lastindex); 
    return fileNoExstention;
}