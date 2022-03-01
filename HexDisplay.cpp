/*******************************
 * About: This is the main program.
 * Purpose: Check whether a file is a hex file and display the file content in terminal.
 * Author: Vu Huy Nhat Minh 20191973
 * Github: 
*******************************/

#include "ErrorChecking.h"
#include "generateData.h"
#include "DataConversion.h"

int main(int argc, char* argv[]) 
{
    /* Check whether open file data or not */
    if (!check_open(argv[1]))
    {
        return 1;
    }

    /* Get data */
    string data = getData(argv[1]);

    /* Check whether a file is a hex file */
    if (!is_hex(data, argv[1]))
    {
        return 1;
    }

    /* Create content to display */
    uint8_t byteData[50000] = {'\0'};
    uint16_t beginAdd = 0;
    uint16_t addCol[1000] = {0};
    int lineIndex = 0;

    int charNum = ParseLineByLine(data, byteData, &beginAdd);
    int totalLine = AddressColumn(beginAdd, charNum, 16, addCol);
    
    //Print header
    printf("\n");
    printf("%s ", "Begin Add");
    printf("%32s\n", "Data");
    for (lineIndex = 0; lineIndex < totalLine; lineIndex++)
    { 
        PrintAddress_n_Data(addCol, byteData, charNum, 16, lineIndex);
        printf("\n");
    }

    /* Display */
}

