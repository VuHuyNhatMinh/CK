#ifndef _ERROR_CHECKING_
#define _ERROR_CHECKING_

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

//check file open, nếu mở được return true, ko thì return false
bool check_open(char a[])  //input là arg[1]
{
    ifstream fin(a);                             
    if(!fin.is_open())  
	{
		cout<<"Error: " < <a <<" could not be opened.";
        return false;
	}
    else
    {
        fin.close();
        return true;
    }
}

//hàm check xem một string có file hex không nếu là file hex thì trả về true, ko phải thì trả về false

bool is_hex(string file, char a[])    //input là một string
{
    for(auto i:file)
    {
        if(i!=':'&&i!='\n'&&(i<48||(57<i&&i<65)||70<i))
        {
            cout << "Error: " << a << " is not Hex File." << endl;
            return false;
        }
    }
    return true;
}

#endif 