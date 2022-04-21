#include "RLEList.h"
#include<stdlib.h>


typedef struct RLEList_t{
    char val;
    int valCount;
    struct node* next;
    struct node* previous;
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


