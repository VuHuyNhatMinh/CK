/* Nguyen Dinh Quoc Dai _ MSV: 20191724  */


#include<cstdio>
#include<cstdint>
#include <cstdbool>
#include<iostream>
 using namespace std;


// Define line structure
struct Line{   
    //Hex line: (:ll aaaa tt [dd....] cc)
    uint8_t byteCount; // ll - hold length
    uint16_t startAddress; //aaaa - hold starting address
    uint8_t dataType; //tt - hold data type value
    uint8_t data[32]; //[dddd....] hold data value maximum of 32 byte
    uint8_t checkSum;  //cc - hold check sum value
};

//Function to convert single character (hexadecimal) to int (decimal). 
uint8_t HexChar2Int(char hex){
    if (hex >= '0' && hex <= '9')
    {
        return (uint8_t)(hex - '0');
    }
    if (hex >= 'A' && hex <= 'F')
    {
        return (uint8_t)(hex - 'A' + 10);
    }
    if (hex >= 'a' && hex <= 'f')
    {
        return (uint8_t)(hex - 'a' + 10);
    }
    
    return 0;
}


//Function to conver 2 character (hexadecimal) into 1 interger ( 1 byte unsigned int)
uint8_t HexChar2Byte(char hex[2]){
    return (HexChar2Int(hex[1])+16*HexChar2Int(hex[0]));
}


//Get infomation of single line
bool GetLine(string hexLineInput, Line *intOutput ){
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

int LineCount(char hexInput[]){
    int i = 0, lineCount = 0;
    while (hexInput[i] != '\0')
    {
        if(hexInput[i] == ':'){
            lineCount ++;
        }
        i++;
    }
    return lineCount;
}


//Read line by line and Write to out put.
int ParseLineByLine(char hexInput[], uint8_t hexDataOutput[]){
    int lineIndex = 0;
    int charIndex = 0;
    int rawDataIndex = 0;
    int byteIndex = 0;
    int totalByteRead = 0;
     
    //Get line count
    int linesInHexfile = LineCount(hexInput);

    //Data of single line.
    uint8_t lineData[255] = {0};
    char lineRawData[520] = {'\0'};
    // unsigned short startAdd[100] = {0};
    // uint8_t byteOnLine[100] = {0};
    Line lineTemp;

    //Parse line by line and write to output.
    while (lineIndex < linesInHexfile)
    {
        //Read line from ':' until '\n'.
        while (hexInput[charIndex] != '\n')
        {
            //skip ':' mark.
            if(hexInput[charIndex] != ':') {
              lineRawData[rawDataIndex] = hexInput[charIndex];
              rawDataIndex++;
            }
            charIndex++;
        }
        charIndex++;
        //Parse single line.
        if (GetLine(lineRawData, lineData, &startAdd[lineIndex], &byteOnLine[lineIndex]))
        {
            //Write to array.
            while (byteIndex < byteOnLine[lineIndex])
            {
                hexDataOutput[startAdd[lineIndex] + byteIndex] = lineData[byteIndex];
                lineData[byteIndex] = '\0';
                byteIndex++;
            }
            
        }
        rawDataIndex = 0;
        byteIndex = 0;
        lineIndex++;
    }
    for (lineIndex = 0; lineIndex < linesInHexfile; lineIndex++)
    {
        totalByteRead += byteOnLine[lineIndex];
    }
    return totalByteRead;
}