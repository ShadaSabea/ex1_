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
    newList->val='/0';
    newList->valCount=1;
    newList->next=NULL;
    newList->previous=NULL;
    return newList;
}


