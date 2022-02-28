#include<stdio.h>
#include<stdint.h>
#include <stdbool.h>

uint8_t HexChar2Int(char hex);
uint8_t HexChar2Byte(char hex[2]);
bool GetLine(char hexLineInput[], uint8_t lineData[255], uint16_t *address, uint8_t *numberOfBytesOnLine );
int LineCount(char hexInput[]);
int ParseLineByLine(char hexInput[], uint8_t hexDataOutput[]);