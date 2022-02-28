/*Nguyen Dinh Quoc Dai _ MSV: 20191724



*/



#include<cstdio>
#include<cstdint>
#include <cstdbool>

uint8_t HexChar2Int(char hex);
uint8_t HexChar2Byte(char hex[2]);
bool GetLine(char hexLineInput[], uint8_t lineData[255], uint16_t *address, uint8_t *numberOfBytesOnLine );
int LineCount(char hexInput[]);
int ParseLineByLine(char hexInput[], uint8_t hexDataOutput[], uint16_t *beginAdd);
int addressColumn(uint16_t beginAddress, int totalByte,  int bytePerLine, uint16_t addressColumn[]);