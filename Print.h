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



void Print_Line(int line, uint8_t buffer[]){
    printf("     %04X     |", line*16 );
    for (int i = 0; i < 16; i++)
    {
        printf("%2X ", buffer[line*16 + i]);
    }
    printf("|");
    for (int i = 0; i < 16; i++)
    {
        printf("%c", (char)buffer[line*16 + i] );
    }
    printf("\n");
};

void Print_Header(){
    printf("\nStart Address |");
    for (int i = 0; i < 16; i++)
    {
        printf("%2X ", i);
    }
    printf("| %8s\n", "ASCII Char");

    int i = 1;
    while (i < 81)
    {
        if (i == 15 || i == 64)
        {
            printf("%c", '|');
            i++;
        }
        else{
        printf("%c", '_');
        i++;
        }
    }
    printf("\n");
};

void Print_Footer(int current_page, int total_page){
    int i = 1;
    while (i < 81)
    {
        if (i == 15 || i == 64)
        {
            printf("%c", '|');
            i++;
        }
        else{
        printf("%c", '_');
        i++;
        }
    }
    printf("\n");

    printf("Page No. %d / %d\n", current_page, total_page);
};


void Print(uint8_t buffer[], int length){
    //Chuyển các giá trị không in được thành FF
    Process_Zero(buffer, length);
    
    //Khởi tạo biến
    int line = 0, page = 0;
    int total_page = length/400 + 1;

    //Hiển thị 3 vùng ra màn hình
    while (page < total_page)
    {
        system("cls");
        Print_Header();
        for ( line = 0; line < 24; line++)
        {
            if ((25*page + line) < (length/16 + 1))
            {
                Print_Line((25*page + line), buffer );
            }
            
        }
        Print_Footer(page + 1, total_page);
        system("pause");
        page++;
        
    }
    

};



