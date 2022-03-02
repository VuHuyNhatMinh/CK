/***********************************************************************
 * About: This is the main program.
 * Purpose: Check whether a file is a hex file and display the file content in terminal.
 * Author: Vu Huy Nhat Minh 20191973
 * Github: 
***********************************************************************/

#include "ErrorChecking.h"
#include "GenerateData.h"
#include "DataConversion.h"
#include "Print.h"

#define MAXFILESIZE 65536
// #define DEBUG

int main(int argc, char* argv[]) 
{
    /* Check whether open file data or not */
    #ifndef DEBUG
        if (!check_open(argv[1]))
        {
            return 1;
        }
    #else
        char inputFile[100] = "test.hex";
        if (!check_open(inputFile))
        {
            return 1;
        }
    #endif

    /* Get data */
    char data[MAXFILESIZE];
    #ifndef DEBUG
        getData(data, argv[1]);
    #else
        getData(data, inputFile);
    #endif

    /* Check whether a file is a hex file */
    #ifndef DEBUG
        if (!is_hex(data, MAXFILESIZE, argv[1]))
        {
            return 1;
        }
    #else
        if (!is_hex(data, MAXFILESIZE, inputFile))
        {
            return 1;
        }
    #endif

    /* Check format file Hex */
    if (!check_error_line_by_line(data, MAXFILESIZE))
    {
        return 1;
    }

    /* Create content to display */
    uint8_t byteData[MAXFILESIZE] = {0};
    int byteNum = ParseLineByLine(data, byteData);

    /* Display */
    Display(byteData, byteNum);
}

