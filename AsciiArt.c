#include "AsciiArt.h"
#include<stdio.h>
#include<stdlib.h>

#define CHUNK_SIZE 256

RLEList asciiArtRead(FILE* in_stream)
{
    if(!in_stream)
    {
        return NULL;
    }
    RLEList list=RLEListCreate();
    char buffer[CHUNK_SIZE];
    while(fgets(buffer,CHUNK_SIZE,in_stream) != NULL)
    {
        int index=0;
        while(buffer[index])
        {
            RLEListAppend(list,buffer[index++]);
        }
    }
    return list;
}



RLEListResult asciiArtPrint(RLEList list, FILE* out_stream)
{
    if(!list || !out_stream)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    int listLen = RLEListSize(list);
    RLEListResult result;
    char currentChar[2];
    currentChar[1]='\0';
    for (int i = 0; i < listLen; i++)
    {
        currentChar[0] = RLEListGet(list, i ,&result);
        if(result != RLE_LIST_SUCCESS)
        {
            return result;
        }
        fputs(currentChar,out_stream);
    }
    return result;
}
