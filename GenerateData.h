/***********************************************************************
 * About: This is the program for processing data.
 * Purpose: get data from file, convert between data.
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

//chuyển binary ở dạng string sang số decimal
int bin_to_dec(string bin) 
{
    int res=0;
    for(int i=0;i<=bin.size()-1;i++)
    {
        res+=(bin[i]-48)*pow(2,bin.size()-1-i);
    }
    return res;
}


//chuyển một số decimal sang số binary ở dạng string
string dec_to_bin(int value)
{   
    string res;
    while(value!=0)
    {
        if(value%2 == 0)
        {
            res+='0';
        }
        else
        {
            res+='1';
        }
        value/=2;
    }
    string reverse_res="";
    for(int i=res.size()-1;i>=0;i--)
    {
        reverse_res+=res[i];
    }
    return reverse_res;
}


//chuyển số decimal sang số hex ở dạng string
string dec_to_hex(int value)
{
    string res = "";
    string reverse_res = ""; 
    while(value!=0)
    {
       int carry = value%16;
       if(carry<=9)
       {
           res+=char(carry+48);
       }
       else
       {
           res+=char(carry-10+'A');
       }
       value/=16;
    }
    for(int i=res.size()-1;i>=0;i--)
    {
        reverse_res+=res[i]; 
    }
    return reverse_res;

}


//chuyển số hex ở dạng string sang số decimal
int hex_to_dec(string hex)   //hàm truyền vào là một string hex, đầu ra là decimal
{
    int res = 0;
    for(int i=0;i<hex.length();i++)
    {
        if(48<=hex[i]&&hex[i]<=57)
        {
            res += (hex[i]-48)*pow(16,hex.length()-i-1);
        }
        else if(65<=hex[i]&&hex[i]<=70)
        {
            res += (hex[i]-55)*pow(16,hex.length()-i-1);
        }
    }
    return res;
}



//đảo tất cả các bit của một binary ở dạng string
string inverse(string text)         //đầu vào là binary ở dạng string, đầu ra là binary ở dạng string
{
    for(int k=0; k < text.size();k++)
    {
        if(text[k]=='0')
        {
            text[k]='1';
        }
        else
        {
            text[k]='0';
        }
    }
    return text;
}



//Lấy 2 kí tự cuối cùng của một string 
string get2LastBit(string text)         
{
    string temp;
    temp += text[text.size()-2];
    temp += text[text.size()-1]; 
    return temp;
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