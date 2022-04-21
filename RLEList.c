#include "RLEList.h"
#include<stdlib.h>


typedef struct RLEList_t{
    char val;
    int valCount;
    struct list* next;
    struct list* previous;
}*RLEList;

RLEList RLEListCreate()
{
    RLEList newList=malloc(sizeof(*newList));
    if(!newList)
    {
        return NULL;
    }
    newList->next=NULL;
    newList->previous=NULL;
    return newList;
}


