#include "RLEList.h"
#include<stdlib.h>


//-----------------#define---------------
#define NULL_LIST -1
#define ILLEGAL_DATA 0

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
void RLEListDestroy(RLEList list)
{
    while(list)
    {
        RLEList listToDelete=list;
        list=list->next;
        free(listToDelete);
    }
}
int RLEListSize(RLEList list)
{
    int listSize=0;
    if(!list)
    {
        return NULL_LIST;
    }
    else
    {
        for (RLEList ptr = list; ptr != NULL; ptr = ptr->next)
        {
            listSize += ptr->valCount;
        }
    }
    return listSize;
}
char RLEListGet(RLEList list, int index, RLEListResult *result)
{
    char requiredCharacter;
    if(!list)
    {
        *result=RLE_LIST_NULL_ARGUMENT;
        return ILLEGAL_DATA;
    }
    int listSize=RLEListSize(list);
    if(index<1 || index>listSize)
    {
        *result=RLE_LIST_INDEX_OUT_OF_BOUNDS;
        return ILLEGAL_DATA;
    }
    else
    {
        RLEList ptr = list;
        int indexOfFirstAppearance=1;
        int indexOfLastAppearance=0;
        while(ptr)
        {
            indexOfLastAppearance=indexOfFirstAppearance+(ptr->valCount)-1;
            if (index>=indexOfFirstAppearance && index<=indexOfLastAppearance)
            {
                *result=RLE_LIST_SUCCESS;
                requiredCharacter=ptr->val;
            }
            indexOfFirstAppearance=indexOfLastAppearance+1;
            ptr=ptr->next;

        }
    }
    return requiredCharacter;
}


