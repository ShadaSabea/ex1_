#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>


char* stringDuplicator(char* s ,int times)
{
    if(!s || times<0)
    {
        printf("error\n");
        return 0;
    }
    int len= strlen(s);
    char* out = malloc( sizeof(*out)*len*times+1);
    if(out==NULL)
    {
        printf("error\n");
        return 0;
    }
    char* ptr=out;
    strcpy(ptr,s);
    for(int i=1; i<times; i++)
    {
        ptr=ptr+len;
        strcpy(ptr,s);
    }
    return out;
}