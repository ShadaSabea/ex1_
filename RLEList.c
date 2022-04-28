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

 struct RLEList_t {

     Node head;
     int length;
 };



RLEList RLEListCreate()
{
    RLEList newList= malloc(sizeof (*newList));

    if(newList==NULL )
    {
        return NULL;
    }
    newList->head= NULL;
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


    if (list->length==1)
    {
        Node ptr= malloc(sizeof(*ptr));
        if(ptr==NULL)
            return NULL;

        list->head=new;
    }
    return new;
}


void RLEListDestroy(RLEList list)
{
        while(list->head!=NULL)
        {
            Node toDelete = list->head;
            list->head = list->head->next;
            free(toDelete);
        }
        free(list);
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
    if(index>listSize-1 || index<0)
    {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }

    int currentSize=0;
    Node node=list->head;
    Node prev=list->head;



    while (node!=NULL)
    {
        currentSize+=node->numOfAppears;
        if(currentSize-1>=index)
        {
            node->numOfAppears--;

            break;
        }
        prev=node;
        node=node->next;
    }

    if( node!=NULL&& node->numOfAppears==0)
    {   if (list->head==prev &&prev->numOfAppears==0)
        {
            list->head = list->head->next;
            free(prev);
            return RLE_LIST_SUCCESS;
        }
        printf("here ");

        if(node->next==NULL)
        {

            prev->next=NULL;
            free(node);

            return RLE_LIST_SUCCESS;
        }
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
        if(result!=NULL)
        {
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return 0;
    }

    int listSize= RLEListSize(list);
    if(index<0 || index>listSize-1)
    {
        if(result!=NULL)
        {
            *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        }
        return 0;
    }
    int currentSize=0;
    char letter;
    Node node=list->head,prev=node;

    while (node!=NULL)
    {
        currentSize += node->numOfAppears;
        if (currentSize-1 >= index)
        {  prev=node;
            break;
        }
        node=node->next;
    }

    letter=prev->character;
    if(result!=NULL)
    {
        *result = RLE_LIST_SUCCESS;
    }

    return letter;




}


char* RLEListExportToString(RLEList list, RLEListResult* result) {

    if (list == NULL)
    { if(result==NULL)
        {
            return NULL;
        }
        *result = RLE_LIST_NULL_ARGUMENT;
        return NULL;
    }

    if(list->length==0)
    {
        if(result!=NULL)
        {
            *result=RLE_LIST_SUCCESS;
            return NULL;
        }
        else return NULL;
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

int main ()
{
    RLEListResult T;
    RLEList list = RLEListCreate();
   for (int i = 0; i < 400; ++i)
   {
        RLEListAppend(list, '1');
   }


    char *x = RLEListExportToString(list, &T);
    printf("%s", x);
    printf("next pos\n");


   // for(int i=0;i<4;i++)
   //{
     //  RLEListDestroy(list);
      // printf("destroyed\n");
    // x = RLEListExportToString(list, &T);
  //  printf("%s\n", x);
 //   printf("next pos\n");

      // char *x = RLEListExportToString(list, &T);
       //printf("%s", x);
       //printf("next pos\n");
 //}

    return 0;
}
/*
/Users/shadasabea/CLionProjects/hw1/cmake-build-debug/hw1
1 Running basicTest ... here [OK]
2 Running basicTestMacros ... [OK]
3 Running RLEListCreateTest ... [OK]
4 Running RLEListDestroyTest ... [OK]
5 Running RLEListAppendTest ... [OK]
6 Running RLEListSizeTest ... here here here here [OK]
7 Running RLEListRemoveTest ... here here here here here [OK]
8 Running RLEListGetTest ... [OK]
9 Running RLEListExportToStringTest ... here here here hw1(26321,0x117379e00) malloc: Incorrect checksum for freed object 0x7fd3f9405ba0: probably modified after being freed.
Corrupt value: 0x40000a31610a320a
hw1(26321,0x117379e00) malloc: *** set a breakpoint in malloc_error_break to debug

Process finished with exit code 134 (interrupted by signal 6: SIGABRT)*/
