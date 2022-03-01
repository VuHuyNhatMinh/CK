#include<cstdio>
#include<cstring>
#include<cstdlib>
#include"DataConversion.h"



#define MAXLENGTH  100 
#define MAXFILESIZE 65536
#define LINELENGHTLIMIT 255 //Byte count max = 0xFF 

int main(int argc, char *argv[]){
  //Variables intialize.
  char inputFileDir[MAXLENGTH] ="avr_uart.hex";
  FILE *fptr;
  char temp[LINELENGHTLIMIT] ;
  char buffer[MAXFILESIZE];//Max size of 64 KBytes.
  int i = 0;
  int k = 0;
  	

  
  
  
  //Handle command line argument.
  if(argc > 1)   
    strcpy(inputFileDir,argv[1]);
  //open file.
  fptr = fopen(inputFileDir,"r");
  //Handle error
  if(fptr == NULL)
  {
    printf("Can't open the file: %s", inputFileDir);   
    exit(1);             
  }  
  //Copy data to buffer
  while(fgets(temp, LINELENGHTLIMIT, fptr) != NULL)
   {
    //  printf("\n%s",temp);
	 strcat(buffer,temp);
	 
   }
 
	/* fgets() returned NULL.  Now you can check why.... */
   if(feof(fptr))
   {
      printf ("\nRead to the end of file : %s", inputFileDir);      
   }
   else 
   {
      /* Error */
      printf ("\nThe line is too long in File : %s", inputFileDir);      
   }




  //MAIN PROGRAM (How to use)
  uint8_t byteData[50000] = {'\0'};
  uint16_t beginAdd = 0;
  uint16_t addCol[1000] = {0};
  int lineIndex = 0;

  int charNum = ParseLineByLine(buffer, byteData, &beginAdd);
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







  fclose(fptr);
  printf("%c", '\n');
  system("pause");
  return 0;
} 

