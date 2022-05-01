//
// Created by Shada Sabea on 24/04/2022.
//
#include <stdio.h>
#include <stdlib.h>
#include "AsciiArtTool.h"

RLEList asciiArtRead(FILE* in_stream)
{
    RLEList list = RLEListCreate();
    if(list==NULL)
    {
        return NULL;
    }
    if (in_stream == NULL)
    {
        return NULL;
    }
        char c;
        while (EOF != (c = fgetc(in_stream)))
        {
                RLEListAppend(list, c);
        }
        return list;
}

RLEListResult asciiArtPrint(RLEList list, FILE *out_stream)
{
    if (list==NULL ||out_stream == NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEListResult result;
    int size = RLEListSize(list), index;
    char put_char[2];
    put_char[1]='\0';

    for (index = 0; index < size; index++)
    {

        put_char[0] = RLEListGet(list, index, &result);
        if(result!=RLE_LIST_SUCCESS)
        {
            result=RLE_LIST_ERROR;
            return result;
        }
        fputs(put_char, out_stream);
    }


    return result;
}

 RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream)
 {
    if(list==NULL||out_stream==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEListResult result;
    char *ptr = RLEListExportToString(list, &result);
    if (ptr == NULL)
    {
        return RLE_LIST_ERROR;
    }
    fprintf(out_stream,ptr);
    free(ptr);
    return RLE_LIST_SUCCESS;
 }


