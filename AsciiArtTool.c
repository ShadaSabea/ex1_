//
// Created by Shada Sabea on 24/04/2022.
//
#include <stdio.h>
#include "AsciiArtTool.h"
#define CHUNCK_SIZE 100

RLEList asciiArtRead(FILE* in_stream) {
    RLEList list = RLEListCreate();
    // FILE *myFile = fopen((const char *) in_stream, "r");
    if (in_stream == NULL) {
        return NULL;
    }
        char buffer[CHUNCK_SIZE];
        while (fgets(buffer, CHUNCK_SIZE, in_stream) != NULL)
        {
            int index = 0;
            while (index < CHUNCK_SIZE)
            {
                char c = buffer[index];
                RLEListAppend(list, c);
                index++;
            }

        }
        // fclose(in_stream);
        return list;
    }

    RLEListResult asciiArtPrint(RLEList list, FILE *out_stream)
    {
        // FILE *myFile = fopen((const char *) out_stream, "r");
        if (out_stream == NULL)
        {
            return RLE_LIST_NULL_ARGUMENT;
        }
        RLEListResult result = RLE_LIST_SUCCESS;
        int size = RLEListSize(list), index;
        for (index = 0; index < size; index++) {
            char tmp = RLEListGet(list, index, &result);
            fputs(&tmp, out_stream);
        }
        // fclose(myFile);
        return RLE_LIST_SUCCESS;

    }

    RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream) {
        RLEListResult result = RLE_LIST_SUCCESS;
        char *ptr = RLEListExportToString(list, &result);
        if (ptr == NULL) {
            return RLE_LIST_NULL_ARGUMENT;
        }
        // FILE *myFile = fopen((const char *) out_stream, "r");
        if (out_stream == NULL) {
            return RLE_LIST_NULL_ARGUMENT;
        }
        fprintf(out_stream, ptr);
        return RLE_LIST_SUCCESS;

    }


