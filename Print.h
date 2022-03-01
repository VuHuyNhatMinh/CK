// Nguyen Tien Linh 20191924
#include<iostream>
using namespace std;

//Xử lí các giá trị không in được
//Đầu vào: mảng các byte dữ liệu
//Đầu ra: Các byte dữ liệu đã được xử lí các giá trị không in được
void Process_Zero(uint8_t data[], int data_length){
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
//Đầu vào: mảng các byte dữ liệu, độ dài của mảng đó
//Đầu ra: mảng kí tự tương ứng, truyền theo kiểu tham chiếu
void Char_Convert(uint8_t data_byte[], int length, char ascii_char[]){
    //Chạy vòng lặp từ đầu đến cuối, chuyển sang kí tự tương ứng.
    for (int i = 0; i < length; i++)
    {
        ascii_char[i] = (char)data_byte[i];
    }
    return;
};

//In các giá trị Ascii ra màn hình.
//Đầu vào: mảng các kí tự ascii, số dòng, số kí tự trên dòng, độ dài mảng kí tự.
//Đầu ra: in ra màn hình....
void Print_Ascii_Line(char data_ascii[], int line, int char_per_line, int data_length ){
    //Chạy vòng lặp từ đầu dòng tới cuối dòng, in từng giá trị của dòng đó ra.
    int i = line*char_per_line ;
    while ( i < (line + 1)*char_per_line )
    {
        if ( i < data_length)
        {
            printf("%c", data_ascii[i]);
            i++;
        }
        else{i++;}
        
    };
    return;
};



