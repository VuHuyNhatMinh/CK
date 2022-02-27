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
		cout<<"Error: "<<a<<" could not be opened.";
        return false;
	}
    else
    {
        fin.close();
        return true;
    }
}