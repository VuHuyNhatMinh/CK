#ifndef _GENERATE_DATA_
#define _GENERATE_DATE_

#include <iostream>
#include <fstream>

using namespace std;

string getData(string filename)
{
    ifstream f;
    f.open(filename);
    string text;
    getline(f, text, '\0');
    f.close();
    return text;
}

string separateLine(string text) 
{
    static int i = 0;
    string line;
    for(i; i < text.size() ; i = i + 1) 
    {
        if (text[i] == ':')
        {
            continue;
        }
        else if (text[i] == '\n')
        {
            i = i + 1;
            break;
        }
        else 
        {
            line = line + text[i];
        }
    }
    return line;
}

#endif