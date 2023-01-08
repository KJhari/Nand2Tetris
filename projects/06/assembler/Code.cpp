// Harikrishnan Kokkanthara Jeevan
#include "Code.h"
#include "TableLookup.h"

using std::bitset;
using std::string;
using std::vector;

// initializes the lookup tables
void initTables()
{

    initCompATable(compATable);
    initCompNotATable(compNotATable);
    initDestTable(destTable);
    initJumpTable(jmpTable);
    initSymbolTable(symbolTable);
}

// return the machine code for a instructions
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

// returns the machine code for c instructions
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