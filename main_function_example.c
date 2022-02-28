#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"Data_conversion.h"


#define MAXLENGTH  100 
#define MAXFILESIZE 65536
#define LINELENGHTLIMIT 255 //Byte count max = 0xFF 

int main(int argc, char *argv[]){
  char inputFileDir[MAXLENGTH] ="avr_uart.hex";
  FILE *fptr;
  char temp[LINELENGHTLIMIT] ;
  char buffer[MAXFILESIZE];//Max size of 64 KBytes.
  	

  if(argc > 1)   
    strcpy(inputFileDir,argv[1]);
  fptr = fopen(inputFileDir,"r");

  if(fptr == NULL)
  {
    printf("Can't open the file: %s", inputFileDir);   
    exit(1);             
  }  
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

   uint8_t output[10000] = {'\0'};
  int charNum = ParseLineByLine(buffer, output);
  int i = 0;
    while (i < charNum)
    {
       printf("%X ", output[i]);
       i++;
    }
    printf("%d", charNum); 
   


  fclose(fptr);
  printf("%c", '\n');
  system("pause");
  return 0;
} 

