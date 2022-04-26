#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>


char* stringDuplicator(char* word ,int times);
int main() {
    char *word="layan";
    char* test=stringDuplicator(word,5);
    printf("%s",test);

    return 0;
}
char* stringDuplicator(char* s ,int times)
{
    if(!s || times<0)
    {
        printf("error\n");
        return 0;
    }
    assert(s);
    assert(times>0);
    int len= strlen(s);
    char* out = malloc( sizeof(*out)*len*times+1);
    if(out==NULL)
    {
        printf("error\n");
        return 0;
    }
    assert(out);
    char* ptr=out;
    strcpy(ptr,s);
    for(int i=1; i<times; i++)
    {
        ptr=ptr+len;
        strcpy(ptr,s);
    }
    return out;
}
