#ifndef _ERROR_CHECKING_
#define _ERROR_CHECKING_

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <math.h>

#include "GenerateData.h"

using namespace std;

//check file open, nếu mở được return true, ko thì return false
bool check_open(char a[])  //input là arg[1]
{
    ifstream fin(a);                             
    if(!fin.is_open())  
	{
		cout<<"Error: " << a <<" could not be opened.";
        return false;
	}
    else
    {
        fin.close();
        return true;
    }
}

//hàm check xem một string có file hex không nếu là file hex thì trả về true, ko phải thì trả về false

bool is_hex(char* text, int size, char a[])    //input là một string
{
    for(int i = 0; i < size ; i = i + 1)
    {
        char c = text[i];
        if (c == 0)
        {
            break;
        }
        
        if (c !=':' && c !='\n' && (c<48 || (57<c && c<65)||70<c))
        {
            cout << "Error: " << a << " is not Hex File." << endl;
            return false;
        }
    }
    return true;
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


//chuyển số hex ở dạng string sang số deciaml
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

string inverse(string text)
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

string get2LastBit(string text)
{
    string temp;
    temp += text[text.size()-2];
    temp += text[text.size()-1]; 
    return temp;
}

//check các lỗi như checksum, lỗi count_byte, lỗi option_byte
//đầu vào là string tất cả data, trả về true nếu không lỗi, trả về false + in ra loại lỗi ở dòng nào đó (lỗi ở dòng đầu tiên) 
bool check_error_line_by_line(char* data, int size)
{
    int line = 1;  
    while(1)
    {
        string data_temp = separateLine(data, size);
        if (data_temp == "")
        {
            break;
        }

        int result=0;
        string result_1="";
        for(int j=0;j<=data_temp.size()-4;j+=2)
        {
            string a = "";
            a+=data_temp[j];
            a+=data_temp[j+1];
            result+=hex_to_dec(a);
        }


        if(dec_to_bin(result).size()<8)
        {
            for(int n=1;n<=(8-dec_to_bin(result).size());n++)
            {
                result_1+='0';
            }
        }
        else if(dec_to_bin(result).size()>=8)
        {
            result_1+='0';
        }

        
        result_1 += dec_to_bin(result);

        result_1 = inverse(result_1);

        result = bin_to_dec(result_1);
        result+=1;
        result_1 = dec_to_hex(result);
        
        string res_data = get2LastBit(data_temp);
        string res_final = get2LastBit(result_1);
        
        if(res_final!=res_data)
        {
            cout<<"Error checksum in line "<<line;
            return false;
        }

        string error_check = "";
        error_check += data_temp[0];
        error_check += data_temp[1];
        if(hex_to_dec(error_check) > 32)
        {
            cout << "Out of 32 bits range in "<< line;
            return false;
        }

        error_check = "";
        error_check += data_temp[6];
        error_check += data_temp[7];
        if(error_check!="00"&&error_check!="01"&&error_check!="02"&&error_check!="04")
        {
            cout<<"option byte "<<error_check<<" is not valid in line "<<line;
            return false;
        }

        line+=1;
    }
    return true;
}

#endif 