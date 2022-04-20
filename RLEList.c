#include "RLEList.h"
#include<stdlib.h>

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
//implement the functions here


RLEList RLEListCreate()
{
    RLEList newList = malloc(sizeof(*newList));
    if(!newList)
    {
        return NULL;
    }
    newList->listHead=NULL;
    newList->listLen = 0;
    return newList;
}

Node createNode(char val)
{
    Node newNode=malloc(sizeof(*newNode));
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
    Node currentNode = NULL;      
}



//------------------------------------------------------------------------------
//test functions:

int returnSize(RLEList list){
    return list->listLen;
}

//------------------------------------------------------------------------------
