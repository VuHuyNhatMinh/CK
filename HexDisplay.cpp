/***********************************************************************
 * About: This is the main program.
 * Purpose: Check whether a file is a hex file and display the file content in terminal.
 * Author: Vu Huy Nhat Minh 20191973
 * Github: 
***********************************************************************/

#include "ErrorChecking.h"
#include "GenerateData.h"
#include "DataConversion.h"
#include "DisplayData.h"

#define MAXFILESIZE 65536
// #define DEBUG

int main(int argc, char* argv[]) 
{
    /* Check whether open file data or not */
    #ifndef DEBUG
        if (!checkOpen(argv[1]))
        {
            return 1;
        }
    #else
        char inputFile[100] = "testhex3.hex";
        if (!checkOpen(inputFile))
        {
            return 1;
        }
    #endif

    /* Get data */
    // Character array
    char data[MAXFILESIZE];
    #ifndef DEBUG
        getData(data, argv[1]);
    #else
        getData(data, inputFile);
    #endif

    /* Check whether a file is a hex file */
    #ifndef DEBUG
        if (!isHex(data, MAXFILESIZE, argv[1]))
        {
            return 1;
        }
    #else
        if (!isHex(data, MAXFILESIZE, inputFile))
        {
            return 1;
        }
    #endif

    /* Check format file Hex */
    if (!checkFormat(data, MAXFILESIZE))
    {
        return 1;
    }

    /* Create content to display */
    // Unsigned integer 8 bit array of value used
    uint8_t byteData[MAXFILESIZE] = {0};
    // Numbers of memory used from 0000 to max value used
    int byteNum = ParseLineByLine(data, byteData);

    /* Display */
    Display(byteData, byteNum);
}

