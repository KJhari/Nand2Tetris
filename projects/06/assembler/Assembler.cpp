#include "assembler.h"
#include "Parser.h"
#include "Code.h"



int readFile(const string filename)
{
	string machineCode="";
	fstream fin,fout;
    string line = "";
	string writeFile = retFileName(filename) + ".hack";
	vector<string> splitCode;
	fin.open(filename);

	 if (fin.is_open())
    {   
        fin.seekg(0, std::ios::end); 
        if(fin.tellg() == 0)
        {   
            fin.close();
            return -1;
        }
        else{
				fin.seekg(0, std::ios::beg);
				fout.open(writeFile, std::ios_base::out);
				if((fout.is_open()))
						{	
							std::cout<<"writefile is open"<<std::endl;
							// fout<<line;
						}
						else
						{
							std::cout<<"writefile is not open"<<std::endl;
							exit(-1);
						}
				int line_num=0;
				while (getline(fin, line))
				{
					fin >> line;
					std::cout<<"line " <<line_num<<": "<< line<<"\n";
					line_num++;
					
					if(!(isComment(line)))
					{

						
						if(line[0]!='@')
						{
							if(line.find(";")!= string::npos)
							{
								if(line.find('=')==string::npos)
								{
									splitCode = parser_string(line,";");
								}
								else
								{
									splitCode = parser_string(line,"=");
									vector<string> sp = parser_string(splitCode[1],";");
									splitCode.pop_back();
									for(int i=0;i<sp.size();i++)
									{
										splitCode.push_back(sp[i]);
									}
								}
								
							}
							else
							{
								splitCode = parser_string(line,"=");
							}

							for(auto it:splitCode)
							{
								std::cout<<it<<"\t";
							}
							std::cout<<"\n";

							machineCode = retCodeC(splitCode);
							std::cout<<machineCode<<"\n";
							fout << machineCode<<"\n";
							
						}
						else
						{
							machineCode=retCodeA(line);
							fout << machineCode<<"\n";
						}
						
					}
				}
				fout.close();
				fin.close();
				return 0;
        }
        
        
    }
    else{
        std::cout<<".asm file not open";
        return -1;
    }

}

int main(int argc, char **argv)
{   

	initTables();

    string asm_file, argument;
    for (int i = 0; i < argc; i++)
	{
		argument = argv[i];
		if (argument == "-f")
		{
			asm_file = argv[i + 1];
		}
	}

	std::cout<<"file name: "<<asm_file<<std::endl;

	int code = readFile(asm_file);




    return 0;
}

