#include <iostream>
#include <string>
#include <math.h>
using namespace std;

//chuyển binary ở dạng string sang số decimal
int bin_to_dec(string bin) 
{
    int res=0;
    for(int i=0;i<bin.size()-1;i++)
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

//check các lỗi như checksum, lỗi count_byte, lỗi option_byte
//đầu vào là string tất cả data, trả về true nếu không lỗi, trả về false + in ra loại lỗi ở dòng nào đó (lỗi ở dòng đầu tiên) 
bool check_error_line_by_line(string data)
{
    data+='\n';
    int line = 1;
    string data_temp = "";
    for( int i=0;i<data.size();i++)
    {
        if(data[i]==':')
        {
            continue;
        }
        else if(data[i]!=':'&&data[i]!='\n')
        {
           data_temp += data[i];
        }
        else if(data[i]=='\n')
        {   
            int result=0;
            string result_1="";
            for(int j=0;j<data_temp.size()-2;j+=2)
            {
                string a = "";
                a+=data_temp[j];
                a+=data_temp[j+1];
                result+=hex_to_dec(a);
            }
            result_1 = dec_to_bin(result);
            for(int k=0;k<result_1.size();k++)
            {
                if(result_1[k]=='0')
                {
                    result_1[k]='1';
                }
                else
                {
                    result_1[k]='0';
                }
            }
            result = bin_to_dec(result_1);
            result+=1;
            result_1 = dec_to_hex(result);
            
            string res_data = "";
            res_data += data_temp[data_temp.size()-2];
            res_data += data_temp[data_temp.size()-1];

            string res_final = "";
            res_final += result_1[result_1.size()-2];
            res_final += result_1[result_1.size()-1];
            
            if(res_final!=res_data)
            {
                cout<<"error checksum in line "<<line;
                return false;
            }

            string error_check = "";
            error_check += data_temp[0];
            error_check += data_temp[1];
            if(hex_to_dec(error_check)>20)
            {
                cout<<"so byte trong dong "<<line<<" lon hon 20";
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


            data_temp = "";
            line+=1;
        }
    }
    return true;
}


