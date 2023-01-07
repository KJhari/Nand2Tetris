
#include "Code.h"
#include "TableLookup.h"

void initTables()
{

    initCompATable(compATable);
    initCompNotATable(compNotATable);
    initDestTable(destTable);
    initJumpTable(jmpTable);
    initJumpTable(symbolTable)

    // unordered_map<string, string>::iterator itr;
    // std::cout << "\nAll Elements : \n";
    // for (itr = compATable.begin();
    //     itr != compATable.end(); itr++)
    // {
    //     // itr works as a pointer to
    //     // pair<string, double> type
    //     // itr->first stores the key part and
    //     // itr->second stores the value part
    //     std::cout << itr->first << "  " <<itr->second << std::endl;
    // }

    // string s = compATable.at("M");
}
string retCodeA(string op)
{
    string s = "";
    if (op[0] == '@')
    {

        int num = stoi(op.substr(1, op.length()));
        std::string binary = std::bitset<15>(num).to_string(); // to binary
        // std::cout<<binary<<"\n";
        s = s + "0" + binary;
    }
    return s;
}

string retCodeC(vector<string> op)
{
    // C instruction format = 1 11(unused) acccc ddd jjj
    // a selects the table, cccc control bits for comp, ddd ctrl bits for destination, jjj ctrl bits for jump
    string op1 = op[0];
    string op2 = op[1];
    string op3 = op[2];

    // all c instructions start with 111
    string machineCode = "111";

    // Append comp bits
    // First check for a=0 table
    if (compNotATable.find(op2) != compNotATable.end())
    {
        // append 0 since a=0
        machineCode += "0";
        machineCode += compNotATable.at(op2);
    }

    // else check in a=1 table (Memeory comp)
    else if (compATable.find(op2) != compATable.end())
    {
        // append 0 since a=0
        machineCode += "1";
        machineCode += compATable.at(op2);
    }

    // append Dest bits
    if (op1 != "noDest")
    {
        if (destTable.find(op1) != destTable.end())
        {
            machineCode += destTable.at(op1);
        }
    }
    else
    {
        op1 = "NULL";
        machineCode += destTable.at(op1);
    }

    // Append jmp bits
    if (op3 != "noJMP")
    {
        if (jmpTable.find(op3) != jmpTable.end())
        {
            machineCode += jmpTable.at(op3);
        }
    }
    else
    {
        op3 = "NULL";
        machineCode += destTable.at(op3);
    }

    return machineCode;
}