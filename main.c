#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<stdlib.h>
#include "AsciiArtTool.h"

#define ENCODED_FLAG "-e"
#define INVERTED_FLAG "-i" 
#define SPACE ' '
#define AT_SIGN '@'


FILE* initInputFile(int argc, char **argv)
{
    return fopen(argv[2],"r");
}


FILE* initOutputFile(int argc, char** argv)
{
    return fopen(argv[3],"w");
}


char invertValue(char value)
{
    if(value==AT_SIGN)
    {
        return SPACE;
    }
    if(value==SPACE)
    {
        return AT_SIGN;
    }
    return value;
}


RLEListResult convertImage(char* flag, RLEList list, FILE* targetStream)
{
    assert(!strcmp(flag,INVERTED_FLAG) || !strcmp(flag,ENCODED_FLAG));
    RLEListResult result;
    if(!strcmp(flag,INVERTED_FLAG))
    {
        result = RLEListMap(list,invertValue);
        if(result!=RLE_LIST_SUCCESS)
        {
            return result;
        }
        result = asciiArtPrint(list,targetStream);
        return result;
    }
    result = asciiArtPrintEncoded(list,targetStream);
    return result;
}


int main(int argc, char **argv)
{
    if(argc!=4)
    {
        printf("Usage: AsciiArtTool <flag> <source> <target>\n");
        return 0;
    }
    if(strcmp(argv[1],INVERTED_FLAG) && strcmp(argv[1],ENCODED_FLAG))
    {
        printf("Error: Undefined flag.\n");
        printf("-i : invert option\n");
        printf("-e : encode option\n");
        return 0;
    }
    FILE* sourceStream = initInputFile(argc,argv);
    if(!sourceStream)
    {
        printf("Error: cannot open:%s\n",argv[2]);
        return 0;
    } 
    FILE* targetStream = initOutputFile(argc,argv);
    if(!targetStream)
    {
        printf("Error: cannot open:%s\n",argv[3]);
        fclose(sourceStream);
        return 0;
    }

    RLEList sourceList = asciiArtRead(sourceStream);
    if(!sourceList)
    {
        printf("Error: memory allocation failed!\n");
        fclose(sourceStream);
        fclose(targetStream);
        return 0;
    }
    RLEListResult result = convertImage(argv[1],sourceList,targetStream);
    if(result!=RLE_LIST_SUCCESS)
    {
        printf("Error: failed to complete operation...\n");
    }
    RLEListDestroy(sourceList);
    fclose(sourceStream);
    fclose(targetStream);
    return 0;
}
