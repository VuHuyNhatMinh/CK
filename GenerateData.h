#ifndef _GENERATE_DATA_
#define _GENERATE_DATA_

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

void getData(char* buffer, string filename)
{
    ifstream f;
    f.open(filename);
    string text;
    getline(f, text, '\0');
    strcpy(buffer, text.c_str());
    f.close();
}

string separateLine(char* text, int size) 
{
    static int i = 0;
    string line;
    for(i; i < size ; i = i + 1) 
    {
        char c = text[i];
        if (c == ':')
        {
            continue;
        }
        else if (c == '\n')
        {
            i = i + 1;
            break;
        }
        else if (c == 0)
        {
            i = 0;
            break;
        }
        else 
        {
            line = line + c;
        }
    }
    return line;
}

//Function to convert single character (hexadecimal) to int (decimal). 
uint8_t HexChar2Int(char hex){
    if (hex >= '0' && hex <= '9')
    {
        return (uint8_t)(hex - '0');
    }
    if (hex >= 'A' && hex <= 'F')
    {
        return (uint8_t)(hex - 'A' + 10);
    }
    if (hex >= 'a' && hex <= 'f')
    {
        return (uint8_t)(hex - 'a' + 10);
    }
    
    return 0;
}


//Function to conver 2 character (hexadecimal) into 1 interger ( 1 byte unsigned int)
uint8_t HexChar2Byte(char hex[2]){
    return (HexChar2Int(hex[1])+16*HexChar2Int(hex[0]));
}

#endif