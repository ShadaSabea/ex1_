#include <stdio.h>
#include <string.h>
#include "RLEList.h"
#include "AsciiArtTool.h"
#define LENGTH 4
#define SPACE ' '

//void print_errors(FILE* file, char* message);
void closeFiles(FILE* output ,FILE* input);
char alternate(char c);


int main(int argc, char** argv)
{
    if(argc!=LENGTH)
    {
        //print_errors(stderr, "num of inputs");
        return 0;
    }

    if(argv[2]==NULL)
    {
        //print_errors(stderr, "the input file");
        return 0;
    }

    FILE *inputFile=fopen((argv[2]) ,"r");
    if(inputFile==NULL)
    {
        //print_errors(stderr,"opening a file");
        return 0;
    }
    FILE *outputFile=fopen((argv[3]) ,"w");
    if(outputFile==NULL)
    {
        fclose(inputFile);
        return 0;
    }


    RLEListResult result;
    RLEList tempList;
    tempList=asciiArtRead(inputFile);

    if(!strcmp(argv[2], "-e"))
    {
        result = asciiArtPrintEncoded(tempList, outputFile);

        if (result != RLE_LIST_SUCCESS)
        {
            //print_errors(stderr, "building list ");
            closeFiles(outputFile,inputFile);
            RLEListDestroy(tempList);
            return 0;
        }
        closeFiles(outputFile,inputFile);
        RLEListDestroy(tempList);
        return 0;

    }

    if(!strcmp(argv[2], "-i"))
    {
        MapFunction ptr=alternate;
        result= RLEListMap(tempList,ptr);
        if(result!=RLE_LIST_SUCCESS)
        {
            //print_errors(stderr, "building list ");
            closeFiles(outputFile,inputFile);
            RLEListDestroy(tempList);
            return 0;
        }
        closeFiles(outputFile,inputFile);
        RLEListDestroy(tempList);
        return 0;
    }
}





void closeFiles(FILE* output ,FILE* input)
{
    if(output!=stdin|| output ==NULL)
    {
        fclose(output);
    }
    if(input!=stdin|| input==NULL)
    {
        fclose(output);
    }
}



/*void print_errors(FILE* file, char* message)
{
    fprintf(file, "error in: %s", message);
}*/

char alternate(char c)
{
    if(c=='@')
    {
        return SPACE;
    }
    if (c==SPACE)
    {
        return '@';
    }
    return c;
}
