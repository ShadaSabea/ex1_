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


int main()
{
    FILE* testFile = fopen("fileName","r");
    if(!testFile)
    {
        printf("cannot open file\n");
        return 0;
    }
    RLEList list=asciiArtRead(testFile);
    free(list);
    return 0;
}
