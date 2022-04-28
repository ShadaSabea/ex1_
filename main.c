#include <stdio.h>
#include <string.h>
#include "RLEList.h"
#include "AsciiArtTool.h"
#define LENGTH 4
#define SPACE ' '
#define FLAG 1
#define SOURCE 2
#define TARGET 3
#define ENCODED_CHAR "-e"
#define INVERTED_CHAR "-i"
#define ADDRESS_SIGN '@'

//void print_errors(FILE* file, char* message);
//void closeFiles(FILE* output ,FILE* input);
char Alternate(char value);


int main(int argc, char** argv)
{
    if(argc!=LENGTH)
    {
        //print_errors(stderr, "num of inputs");
        return 0;
    }
    if(strcmp(argv[FLAG],ENCODED_CHAR)!=0  &&  strcmp(argv[FLAG],INVERTED_CHAR)!=0)
    {
        return 0;
    }

  //  if(argv[SOURCE]==NULL)
   // {
        //print_errors(stderr, "the input file");
    //    return 0;
   // }
    FILE *inputFile=fopen((argv[SOURCE]) ,"r");
    if(inputFile==NULL)
    {
        //print_errors(stderr,"opening a file");
        return 0;
    }
    FILE *outputFile=fopen((argv[TARGET]) ,"w");
    if(outputFile==NULL)
    {
        fclose(inputFile);
        return 0;
    }
    RLEListResult result;
    RLEList tempList ;
    tempList=asciiArtRead(inputFile);
    if(tempList==NULL)
    { fclose(inputFile);
      fclose(outputFile);
        return 0;
     }

    if(strcmp(argv[FLAG],ENCODED_CHAR)==0)
    {

        result = asciiArtPrintEncoded(tempList, outputFile);
        fclose(outputFile);
        fclose(inputFile);
        RLEListDestroy(tempList);
        return 0;

    }

    if(strcmp(argv[FLAG], INVERTED_CHAR)==0)
    {
        result= RLEListMap(tempList,Alternate);
        if(result!=RLE_LIST_SUCCESS)
        {
            //print_errors(stderr, "building list ");
            fclose(outputFile);
            fclose(inputFile);
            RLEListDestroy(tempList);
            return 0;
        }
        result=asciiArtPrint(tempList,outputFile);
        fclose(outputFile);
        fclose(inputFile);
        RLEListDestroy(tempList);
        return 0;
    }
}
char Alternate(char value)
{
    if(value==ADDRESS_SIGN)
    {
        return SPACE;
    }
    if (value==SPACE)
    {
        return ADDRESS_SIGN;
    }
    return value;
}
