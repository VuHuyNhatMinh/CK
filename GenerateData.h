/***********************************************************************
 * About: This is the program for processing data.
 * Purpose: get data from file, convert from dec to hex and vice versa.
 * Author: Vu Huy Nhat Minh 20191973
***********************************************************************/

#ifndef _GENERATE_DATA_
#define _GENERATE_DATA_

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

/*******************************************
 * About: Get data from file hex.
 * Input: 
- buffer: array of characters which hold content.
- filename: name of the file.      
 * Output: array of char from filename.
*******************************************/
void getData(char* buffer, string filename)
{
    ifstream f;
    f.open(filename);
    string text;
    getline(f, text, '\0');
    strcpy(buffer, text.c_str());
    f.close();
}

/*******************************************
 * About: Seperate line from character array.
 * Input: 
- text: array of characters which hold content
- size: size of array used.      
 * Output: single line from array (which start from ':' and end at '\n').
*******************************************/
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

/*******************************************
 * About: Convert single character (hexadecimal) to integer (decimal).
 * Input: A hexadecimal character    
 * Output: A decimal integer value.
*******************************************/
//Function to . 
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

/*******************************************
 * About: Conver 2 hexadecimal characters to 1 interger value  (1 byte unsigned int).
 * Input: 2 hexadecimal characters.    
 * Output: A decimal integer value.
*******************************************/
uint8_t HexChar2Byte(char hex[2]){
    return (HexChar2Int(hex[1])+16*HexChar2Int(hex[0]));
}

#endif