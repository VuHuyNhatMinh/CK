/*******************************
 * About: This is the main program.
 * Purpose: Check whether a file is a hex file and display the file content in terminal.
 * Author: Vu Huy Nhat Minh 20191973
 * Github: 
*******************************/

#include "ErrorChecking.h"
#include "generateData.h"

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
    while (1)
    {
        string newline = separateLine(data);
        if (newline == "")
        {
            break;
        }
        else
        {
            // TO DO
        }
    }

    /* Display */
}

