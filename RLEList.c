#include "RLEList.h"
#include<stdlib.h>
#include <assert.h>

//-----------------#define---------------
#define NULL_LIST -1
#define ILLEGAL_DATA 0

//----------------------------------------
static int nodeNumber(RLEList list);

typedef struct node{
    char val;
    int valCount;
    struct node* next;
    struct node* previous;
}*Node;

struct RLEList_t{
    Node listHead;
    int listLen;
};



RLEList RLEListCreate()
{
    RLEList newList = malloc(sizeof(*newList));
    if(!newList)
    {
        return NULL;
    }
    assert(newList);
    newList->listHead=NULL;
    newList->listLen = 0;
    return newList;
}

Node createNode(char val)
{
    Node newNode=malloc(sizeof(*newNode));
    assert(newNode);
    if(!newNode)
    {
        return NULL;
    }
    newNode->val=val;
    newNode->valCount=1;
    newNode->next=NULL;
    newNode->previous=NULL;
    return newNode;
}

void RLEListDestroy(RLEList list)
{
    if(!list)
    {
        return;
    }
    assert(list);
    while(list->listHead)
    {
        Node toDelete= list->listHead;
        list->listHead=list->listHead->next;
        free(toDelete);
    }
    free(list);
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
        for (Node ptr = list->listHead; ptr != NULL; ptr = ptr->next)
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
        Node ptr = list->listHead;
        int indexOfFirstAppearance=1;
        int indexOfLastAppearance=0;
        while(ptr)
        {
            indexOfLastAppearance=indexOfFirstAppearance+(ptr->val)-1;
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
