#include<stdio.h>
#include<assert.h>
#include<string.h>
#include "AsciiArtTool.h"

#define ENCODED_FLAG "-e"
#define INVERTED_FLAG "-i"
#define SPACE ' '
#define AT_SIGN '@'
#define EXPECTED_ARGC 4
#define FLAG_INDEX 1
#define SOURCE_INDEX 2
#define TARGET_INDEX 3


FILE* initInputFile(char **argv)
{
    return fopen(argv[SOURCE_INDEX],"r");
}


FILE* initOutputFile(char** argv)
{
    return fopen(argv[TARGET_INDEX],"w");
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
    if(argc!=EXPECTED_ARGC)
    {
        printf("Usage: AsciiArtTool <flag> <source> <target>\n");
        return 0;
    }
    if(strcmp(argv[FLAG_INDEX],INVERTED_FLAG) && strcmp(argv[FLAG_INDEX],ENCODED_FLAG))
    {
        printf("Error: Undefined flag.\n");
        printf("-i : invert option\n");
        printf("-e : encode option\n");
        return 0;
    }
    FILE* sourceStream = initInputFile(argv);
    if(!sourceStream)
    {
        printf("Error: cannot open:%s\n",argv[SOURCE_INDEX]);
        return 0;
    }
    FILE* targetStream = initOutputFile(argv);
    if(!targetStream)
    {
        printf("Error: cannot open:%s\n",argv[TARGET_INDEX]);
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
    RLEListResult result = convertImage(argv[FLAG_INDEX],sourceList,targetStream);
    if(result!=RLE_LIST_SUCCESS)
    {
        printf("Error: failed to complete operation...\n");
    }
    RLEListDestroy(sourceList);
    fclose(sourceStream);
    fclose(targetStream);
    return 0;
}
