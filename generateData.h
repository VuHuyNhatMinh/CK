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
            break;
        }
        else 
        {
            line = line + c;
        }
    }
    return line;
}

#endif