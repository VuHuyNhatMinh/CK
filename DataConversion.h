/* Nguyen Dinh Quoc Dai _ MSV: 20191724  */
#ifndef _DATA_CONVERSION_
#define _DATA_CONVERSION_

#include<cstdio>
#include<cstdint>
#include <cstdbool>
#include<iostream>
#include "GenerateData.h"

using namespace std;

// Define line structure
struct Line {   
    //Hex line: (:ll aaaa tt [dd....] cc)
    uint8_t byteCount = 0; // ll - hold length
    uint16_t startAddress = 0; //aaaa - hold starting address
    uint8_t dataType = 0; //tt - hold data type value
    uint8_t data[32] = {0}; //[dddd....] hold data value maximum of 32 byte
    uint8_t checkSum = 0;  //cc - hold check sum value
};

//Get infomation of single line
//Input: character array of hex line.
//Output: Line struct contain information of line. (Pointer of output is an input argument)
bool GetLine(char hexLineInput[], Line *intOutput ){
    char temp[2];
    uint8_t addTemp;
    int dataIndex = 0;
    

    //Get BYTE COUNT
    temp[0] = hexLineInput[0];
    temp[1] = hexLineInput[1];
    intOutput->byteCount = HexChar2Byte(temp);
    if ( intOutput->byteCount == 0 )
    {
        return false;
    }
    

    //Get Address
    temp[0] = hexLineInput[2];
    temp[1] = hexLineInput[3];
    addTemp = HexChar2Byte(temp);
    temp[0] = hexLineInput[4];
    temp[1] = hexLineInput[5];
    intOutput->startAddress = ((uint16_t)addTemp << 8) | HexChar2Byte(temp); //Combine 2 bytes 

    //Get Record Type
    temp[0] = hexLineInput[6];
    temp[1] = hexLineInput[7];
    intOutput->dataType = HexChar2Byte(temp);
    if (intOutput->dataType != 0)
    {
        return false;
    }
    
    //DATA
    int i;
    for (i = 8; i < intOutput->byteCount*2 + 8; i += 2)
    {
        temp[0] = hexLineInput[i];
        temp[1] = hexLineInput[i+1];
        intOutput->data[dataIndex] = HexChar2Byte(temp);
        dataIndex ++;
    }

    //Get Checksum
    temp[0] = hexLineInput[i];
    temp[1] = hexLineInput[i+1];
    intOutput->checkSum = HexChar2Byte(temp);
    return true;
};


//Count the line in char array input
int LineCount(char hexInput[]){
    int i = 0, lineCount = 0;
    while (hexInput[i] != '\0')
    {
        if(hexInput[i] == ':'){
            lineCount ++; //Count line by ":" mark
        }
        i++;
    }
    return lineCount; //Output: line number
}


//Read line by line and Write to out put.

int ParseLineByLine(char hexInput[], uint8_t hexDataOutput[]){
    int lineIndex = 0;
    int byteIndex = 0;
    int length = 0;
     
    //Get line count
    int linesInHexfile = LineCount(hexInput);

    //Data of single line.
    char lineRawData[74] = {'\0'}; // up to 37 (bytes) * 2 (chars) per line 
    struct Line lineTemp[4096]; //total 37*4096 = 148 Kbytes. 

    //Parse line by line and write to output.
    while (lineIndex < linesInHexfile)
    {
        strcpy(lineRawData, separateLine(hexInput, 65536).c_str());
        //Parse single line.
        if (GetLine(lineRawData, &lineTemp[lineIndex] ))
        {
            //Write to array.
            while (byteIndex < lineTemp[lineIndex].byteCount)
            {
                hexDataOutput[lineTemp[lineIndex].startAddress + byteIndex] = lineTemp[lineIndex].data[byteIndex];
                byteIndex++;
            }          
        }
        byteIndex = 0;
        lineIndex++;
    }

    //find and return length of buffer for printing 
    for (lineIndex = 0; lineIndex < linesInHexfile; lineIndex++)
    {
        if((lineTemp[lineIndex].startAddress - 1 + lineTemp[lineIndex].byteCount) > length){
            length = (lineTemp[lineIndex].startAddress - 1 + lineTemp[lineIndex].byteCount);
        }
    }

    return length;
}

#endif