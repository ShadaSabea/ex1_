//
// Created by Shada Sabea on 24/04/2022.
//
#include <stdio.h>
#include "AsciiArtTool.h"
#include <stdlib.h>

RLEList asciiArtRead(FILE* in_stream)
{
    RLEList list = RLEListCreate();
    FILE *myFile = fopen((const char *) in_stream, "r");
    if(myFile==NULL)
    {
        return NULL;
    }
    do
    {
        char c = fgetc(myFile);
        RLEListAppend(list, c);
      } while (fgetc(myFile) != EOF);
    fclose(myFile);
    return list;
}

RLEListResult asciiArtPrint(RLEList list, FILE *out_stream)
{
    FILE *myFile = fopen((const char *) out_stream, "r");
    if(myFile==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEListResult result=RLE_LIST_SUCCESS;
    int size = RLEListSize(list),index;
    for(index=0; index<size;index++ )
    {
        fputs(RLEListGet(list,index,result), myFile);
    }
    fclose(myFile);
    return RLE_LIST_SUCCESS;

}

RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream)
{
    char* ptr=RLEListExportToString(list,RLE_LIST_SUCCESS);
    if (ptr==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    FILE *myFile = fopen((const char *) out_stream, "r");
    if(myFile==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    fprintf(myFile,ptr);
    free(ptr);
    fclose(myFile);
    return RLE_LIST_SUCCESS;

}








