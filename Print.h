// Nguyen Tien Linh 20191924
#include<iostream>
using namespace std;

//Xử lí các giá trị không in được
void ProcessZero(uint8_t data[], int data_length){
    //Vòng lặp for kiểm tra từ đầu đến cuối byte có giá trị không in được
    for (int i = 0; i < data_length; i++)
    {
        //Nếu gặp số 0 - 31 thay thế bằng giá trị 255 (0xFF h)
        if (data[i] >= 0 && data[i] <= 31)
        {
            data[i] = 255;
        }
    }
    return;
};

//Chuyển các byte sang kí tự tương ứng trong bảng mã Ascii
void Char_Convert(uint8_t data_input[], int length, char ascii_char[]){
    //Chạy vòng lặp từ đầu đến cuối, chuyển sang kí tự tương ứng.
    for (int i = 0; i < length; i++)
    {
        ascii_char[i] = (char)data_input[i];
    }
    return;
};





