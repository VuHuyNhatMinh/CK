#include"Data_conversion.h"

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
};

uint8_t HexChar2Byte(char hex[2]){
    return (HexChar2Int(hex[1])+16*HexChar2Int(hex[0]));
};

bool GetLine(char hexLineInput[], uint8_t lineData[], uint16_t *address, uint8_t *numberOfBytesOnLine ){
    char temp[2];
    uint8_t addTemp;
    int dataIndex = 0;
    
    //To hold file hex values.
	uint8_t byteCount;
    uint16_t startAddress;
    uint8_t dataType;
    uint8_t checkSum;

    //Get BYTE COUNT
    temp[0] = hexLineInput[0];
    temp[1] = hexLineInput[1];
    byteCount = HexChar2Byte(temp);
    if (byteCount == 0)
    {
        return false;
    }
    

    //Get Address
    temp[0] = hexLineInput[2];
    temp[1] = hexLineInput[3];
    addTemp = HexChar2Byte(temp);
    temp[0] = hexLineInput[4];
    temp[1] = hexLineInput[5];
    *address = ((uint16_t)addTemp << 8) | HexChar2Byte(temp);

    //Get Record Type
    temp[0] = hexLineInput[6];
    temp[1] = hexLineInput[7];
    dataType = HexChar2Byte(temp);
    if (dataType != 0)
    {
        return false;
    }
    
    //DATA
    for (int i = 8; i < byteCount*2 + 8; i += 2)
    {
        temp[0] = hexLineInput[i];
        temp[1] = hexLineInput[i+1];
        lineData[dataIndex] = HexChar2Byte(temp);
        dataIndex ++;
    }
    *numberOfBytesOnLine = dataIndex;

    //Get Checksum
    
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
};

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
    unsigned short startAdd[25] = {0};
    uint8_t byteOnLine[25] = {0};

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
};