#include <iostream>
using namespace std;


//hàm check xem một string có file hex không nếu là file hex thì trả về true, ko phải thì trả về false

bool is_hex(string file)    //input là một string
{
    for(auto i:file)
    {
        if(i!=':'&&i!='\n'&&(i<48||(57<i&&i<65)||70<i))
        {
            return false;
        }
    }
    return true;
}
