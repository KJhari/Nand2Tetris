// Harikrishnan Kokkanthara Jeevan
#include "parser.h"
#include "TableLookup.h"

using std::fstream;
using std::string;
using std::vector;

// checks if the string is a comment
bool isComment(const string s)
{
    if (s[0] == '/')
    {
        return true;
    }

    else
        return false;
}

// splits the line into multiple sections, eg: D D-M JMP
vector<string> &splitCodes(string line, const string delimiter, vector<string> &res)
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    while ((pos_end = line.find(delimiter, pos_start)) != string::npos)
    {
        token = line.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(line.substr(pos_start));

    return res;
}

// adds placeholders while parsing the instructions to enable easier translation
vector<string> parser_string(string line, const string delimiter)
{
    vector<string> res;

    if (delimiter == "=" && (line.find(";") == string::npos))
    {
        res = splitCodes(line, delimiter, res);
        res.push_back("noJMP");
    }

    else if (delimiter == ";" && (line.find("=") == string::npos) && line[0] == '0')
    {
        res.push_back("noDest");
        vector<string> res2 = splitCodes(line, delimiter, res);
        res = res2;
    }

    else if ((delimiter == ";") && (line.find("=") == string::npos) && (line[1] == ';'))
    {
        // std::cout << line << std::endl;
        res.push_back("noDest");
        vector<string> res2 = splitCodes(line, delimiter, res);
        res = res2;
    }

    else if (delimiter == ";" && (line.find("=") == string::npos))
    {

        vector<string> res2 = splitCodes(line, delimiter, res);
        res = res2;
    }

    else
    {
        res = splitCodes(line, delimiter, res);
    }

    return res;
}

// removes the extention from the filname
string retFileName(string filename)
{
    size_t lastindex = filename.find_last_of(".");
    string fileNoExstention = filename.substr(0, lastindex);
    return fileNoExstention;
}

// creates the hack0 helper file //firstpass
void labelParser(string filename)
{
    fstream fin, fout;
    string line = "";
    string writeFile = retFileName(filename) + ".hack0";
    fin.open(filename);
    if (fin.is_open())
    {
        fin.seekg(0, std::ios::end);
        if (fin.tellg() == 0)
        {
            fin.close();
        }
        else
        {
            fin.seekg(0, std::ios::beg);
            fout.open(writeFile, std::ios_base::out);
            if ((fout.is_open()))
            {
                std::cout << "Helper file .hack0 created" << std::endl;
                // fout<<line;
            }
            else
            {
                std::cout << "Cannot create Helper file .hack0 " << std::endl;
                exit(-1);
            }
            int line_num = -1;
            while (getline(fin, line))
            {
                // std::cout<<line<<std::endl;
                string noWhiteSpaceline = "";
                if (!line.empty() && !isComment(line))
                {
                    if (line[0] != '(')
                    {
                        line_num++;
                    }
                    noWhiteSpaceline = removeComments(line);
                    if (noWhiteSpaceline[0] != '(')
                    {
                        fout << noWhiteSpaceline << "\n";
                    }
                }
                if (!noWhiteSpaceline.empty())
                {
                    // fout<<noWhiteSpaceline<<"\n";
                    // line_num++;
                    if (noWhiteSpaceline[0] == '(' && noWhiteSpaceline[noWhiteSpaceline.length() - 1] == ')')
                    {
                        string key = noWhiteSpaceline.substr(1, noWhiteSpaceline.length() - 2);
                        string val = std::to_string(line_num + 1);
                        symbolTable.insert({key, val});
                    }
                }
            }
        }
        fout.close();
        fin.close();
    }

    else
    {
        std::cout << "Cannot open .asm file";
    }
}

// creates the hack1 helper file . replaces the variables from the file
void symbolParser(string filename)
{
    fstream fin, fout;
    string line = "";
    string writeFile = retFileName(filename) + ".hack1";
    fin.open(filename);
    if (fin.is_open())
    {
        fin.seekg(0, std::ios::end);
        if (fin.tellg() == 0)
        {
            fin.close();
        }
        else
        {
            fin.seekg(0, std::ios::beg);
            fout.open(writeFile, std::ios_base::out);
            if ((fout.is_open()))
            {
                std::cout << "Helper file .hack1 created" << std::endl;
                // fout<<line;
            }
            else
            {
                std::cout << "Cannot create Helper file .hack1" << std::endl;
                exit(-1);
            }
            int line_num = -1;
            int i = 16;
            while (getline(fin, line))
            {
                if (line[0] == '@' && !isdigit(line[1]))
                {
                    string var = line.substr(1, line.length() - 1);
                    if (symbolTable.find(var) != symbolTable.end())
                    {
                        string val = symbolTable.at(var);
                        fout << "@" + symbolTable.at(var) << "\n";
                    }
                    else
                    {
                        symbolTable.insert({var, std::to_string(i)});
                        fout << "@" + symbolTable.at(var) << "\n";
                        i++;
                    }
                }
                else
                {
                    fout << line << "\n";
                }
            }
        }
        fout.close();
        fin.close();
    }
    else
    {
        std::cout << "Cannot open .asm file";
    }
}

string removeComments(string prgm)
{
    int n = prgm.length();
    string res;

    // Flags to indicate that single line and multiple line comments
    // have started or not.
    bool s_cmt = false;
    bool m_cmt = false;

    // Traverse the given program
    for (int i = 0; i < n; i++)
    {
        // If single line comment flag is on, then check for end of it
        if (s_cmt == true && prgm[i] == '\n')
            s_cmt = false;

        // If multiple line comment is on, then check for end of it
        else if (m_cmt == true && prgm[i] == '*' && prgm[i + 1] == '/')
            m_cmt = false, i++;

        // If this character is in a comment, ignore it
        else if (s_cmt || m_cmt)
            continue;

        // Check for beginning of comments and set the appropriate flags
        else if (prgm[i] == '/' && prgm[i + 1] == '/')
            s_cmt = true, i++;
        else if (prgm[i] == '/' && prgm[i + 1] == '*')
            m_cmt = true, i++;

        // If current character is a non-comment character, append it to res
        else
            res += prgm[i];
    }
    res.erase(std::remove(res.begin(), res.end(), ' '), res.end());
    return res;
}

void removeHelperFiles(string filename)
{
    try
    {
        if (std::filesystem::remove(filename))
            std::cout << "Helper file " << filename << " deleted.\n";
        else
            std::cout << "Helper file " << filename << " not found.\n";
    }
    catch (const std::filesystem::filesystem_error &err)
    {
        std::cout << "filesystem error: " << err.what() << '\n';
    }
}