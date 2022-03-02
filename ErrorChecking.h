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

//check các lỗi như checksum, lỗi count_byte, lỗi option_byte
//đầu vào là string tất cả data, trả về true nếu không lỗi, trả về false + in ra loại lỗi ở dòng nào đó (lỗi ở dòng đầu tiên) 
bool check_error_line_by_line(char* data, int size)
{
    int line = 1;                                               //lưu dòng đang xét là dòng bao nhiêu
    while(1)
    {


        string data_temp = separateLine(data, size);            //xét từng dòng một của file data


        if (data_temp == "")                                    //nếu không còn dòng nào nữa để xét
        {
            break;
        }


        int result=0;                                           //lưu giá trị decimal khi cộng các các byte trong quá trình checksum
        string result_1="";                                     //lưu giá trị hex hoặc binary khi cộng các byte trong quá trình checksum



        for(int j=0;j<=data_temp.size()-4;j+=2)                 //cộng tất cả các byte phải checksum của một dòng
        {
            string a = "";                                      //lưu 1 byte một trong một dòng (gồm 2 chữ cái hex liên tục) ở dạng string hex
            a+=data_temp[j];
            a+=data_temp[j+1];
            result+=hex_to_dec(a);                              //đổi string hex sang decimal rồi cộng vào result
        }                                                      
        //result =  tổng các byte cần checksum trong một dòng ở dạng decimal


        if(dec_to_bin(result).size()<8)                         //nếu kích thước của result nhỏ hơn 8 bits
        {
            for(int n=1;n<=(8-dec_to_bin(result).size());n++)   //chèm them các bit 0 đằng trước để đủ 1 8 bits
            {
                result_1+='0';                                  
            }
        }


        else if(dec_to_bin(result).size()>=8)                   //nếu result đã đủ 8 bits hoặc nhiều hơn 8 bits
        {
            result_1+='0';                                      //thêm một bit 0 đằng trước 
        }

        
        result_1 += dec_to_bin(result);                         //chuyển result sang string binary rồi lưu vào result_1

        result_1 = inverse(result_1);                           //đảo bit result_1

        result = bin_to_dec(result_1);                          //chuyenr result_1 sang decimal rồi lưu vào result
        result+=1;                                              //result cộng thêm 1
        result_1 = dec_to_hex(result);                          //chuyển result sang dạng string hex rồi lưu vào result_1
        
        string res_data = get2LastBit(data_temp);               //lấy 2 kí tự cuối của dòng đang xét (byte checksum)
        string res_final = get2LastBit(result_1);               //lấy 2 kí tự cuối của result_1  (1 byte)
        
        if(res_final!=res_data)                                 //so sánh 1 byte cuối của result_1 với byte checksum của dòng đang xét
        {
            cout<<"Error: Wrong checksum in line "<<line;              //in lỗi nếu có
            return false;
        }

        string error_check = "";                                //check count_byte của dòng đang xét có nhỏ hơn 32 bits không
        
        /*
        error_check += data_temp[0];
        error_check += data_temp[1];
        if(hex_to_dec(error_check) > 32)
        {
            cout << "Error: Out of 32 bits range in "<< line;
            return false;
        }
        */
       
        error_check = "";                                       //check option_byte của dòng đang xét xem có thỏa mãn không
        error_check += data_temp[6];
        error_check += data_temp[7];
        if(error_check!="00"&&error_check!="01"&&error_check!="02"&&error_check!="04")
        {
            cout<<"Error: Record type "<<error_check<<" is not valid in line "<<line;
            return false;
        }

        line+=1;
    }
    return true;
}

#endif 