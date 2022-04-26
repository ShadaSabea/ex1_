#include "RLEList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXPANDED_LENGTH 2

typedef struct node{
    int numOfAppears;
    char character;
    struct node* next;
}*Node;

 struct RLEList_t{

    Node head;
    int length;
};



RLEList RLEListCreate()
{
    RLEList newList= malloc(sizeof (*newList));
    Node ptr= malloc(sizeof (*ptr));


    if(newList==NULL || ptr== NULL)
    {
        return NULL;
    }
    newList->head= ptr;
    newList->head->next=NULL;
    newList->length=0;
    return newList;
}

Node CreateNode(char letter,RLEList list)
{
    Node new= malloc(sizeof(*new));
    if (new==NULL)
    {
        return NULL;
    }

    new->character=letter;
    new->numOfAppears=1;
    new->next=NULL;
    list->length++;



    Node node=list->head;
    if (node==NULL)
    {
        node=new;
    }

    return new;
}


void RLEListDestroy(RLEList list)
{
        while(list->head)
        {
            Node toDelete = list->head;
            list->head = list->head->next;
            free(toDelete);
        }
    }

RLEListResult RLEListAppend(RLEList list, char value)
{

    if(list==NULL || value==0)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    Node node=list->head;



if(node==NULL)
{
    Node newNode;
    newNode = CreateNode(value,list);
    if(newNode == NULL)
    {
        return RLE_LIST_OUT_OF_MEMORY;
    }
    newNode->next=NULL;

    return RLE_LIST_SUCCESS;
}

        while(node->next != NULL)
        {
            node = node->next;
        }



    if(node->character == value)
    {
        node->numOfAppears++;
        return RLE_LIST_SUCCESS;
    }

    Node newNode;
    newNode = CreateNode(value,list);

    if(newNode == NULL)
    {
        return RLE_LIST_OUT_OF_MEMORY;
    }

    node->next=newNode;

    return RLE_LIST_SUCCESS;
}

int RLEListSize(RLEList list)
{
    if(list == NULL)
    {
        return -1;
    }
    int size=0;
    Node node=list->head;
    while (node != NULL)
    {
        size+= node->numOfAppears;
        node= node->next;
    }

    return size;
}

RLEListResult RLEListRemove(RLEList list, int index)
{
    if(list == NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    int listSize= RLEListSize(list);
    if(index>listSize || index<0)
    {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }

    int currentSize=0;
    Node node=list->head,prev=list->head;

    while (node!=NULL)
    {
        currentSize+=node->numOfAppears;
        if(currentSize-1>=index)
        {
            break;
        }
        prev=node;
        node=node->next;
    }

    node->numOfAppears--;
    if(node->numOfAppears==0)
    {

        if(prev->character == node->next->character)
        {
            prev->numOfAppears+=node->next->numOfAppears;
            prev->next=node->next->next;
            free(node->next);
        }
        else
        {
            prev->next=node->next;
        }
        free(node);
    }
    return RLE_LIST_SUCCESS;
}

char RLEListGet(RLEList list, int index, RLEListResult *result)
{
    if(list == NULL)
    {
        *result=RLE_LIST_NULL_ARGUMENT;
        return 0;
    }

    if(result==NULL)
    {
        //*result=RLE_LIST_ERROR;
        return 0;
    }

    int listSize= RLEListSize(list);
    if(index<0 || index>listSize)
    {
        *result=RLE_LIST_INDEX_OUT_OF_BOUNDS;
        return 0;
    }

    int currentSize=0;
    char letter;
    Node node=list->head;
    while (node!=NULL)
    {
        currentSize += node->numOfAppears;
        if (currentSize-1 >= index) {
            break;
        }
        node=node->next;
    }
    letter=node->character;
    *result=RLE_LIST_SUCCESS;
    return letter;
}

char* RLEListExportToString(RLEList list, RLEListResult* result) {

    if (list == NULL)
    {
        *result = RLE_LIST_NULL_ARGUMENT;
        return NULL;
    }


    Node node = list->head;
    char *exportedToString = malloc((sizeof(*exportedToString)*EXPANDED_LENGTH*list->length)+1);
    if(exportedToString==NULL)
    {
        *result=RLE_LIST_NULL_ARGUMENT;
        return NULL;
    }
    char *ptrExportedToString=exportedToString;
    int currentLen;
    while(node!=NULL)
    {
       currentLen=sprintf(ptrExportedToString,"%c%d\n",node->character,node->numOfAppears);
        ptrExportedToString+=currentLen;
        node=node->next;

    }
    *result=RLE_LIST_SUCCESS;
    return exportedToString;


}


void Rearrange(RLEList list)
{
    Node node1=list->head,node2,prev;
    int count=0;

    while(node1!=NULL)
    {   node2=node1->next;
        while(node2!=NULL && node2->character == node1->character)
        {
            count+=node2->numOfAppears;
            prev=node2;
            node2=node2->next;
            free(prev);
        }
        node1->numOfAppears+=count;
        node1->next=node2;
        node1=node1->next;
    }
}


RLEListResult RLEListMap(RLEList list, MapFunction map_function)
{
   if(list==NULL|| map_function==NULL)
   {
       return RLE_LIST_NULL_ARGUMENT;
   }

   Node node=list->head;

   while(node!=NULL)
   {
       char c =node->character;
       char toReplace=map_function(c);
       node->character=toReplace;
       node=node->next;
   }

    Rearrange(list);
    return RLE_LIST_SUCCESS;

}


