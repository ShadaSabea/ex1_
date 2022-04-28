#include "RLEList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct node{
    int numOfAppears;
    char character;
    struct node* next;
}*Node;

 struct RLEList_t {

     Node head;
     int length;
 };
Node CreateNode(char letter,RLEList list);
bool CheckResultIsNull(RLEListResult *result);
int countPlaces(int num);
int countPlacesNeedList(RLEList list);
void Rearrange(RLEList list);


bool CheckResultIsNull(RLEListResult *result)
{
     if(result==NULL)
         return true;
     return false;
}

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
        if(!CheckResultIsNull(result))
        {
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return 0;
    }

    int listSize= RLEListSize(list);
    if(index<0 || index>listSize-1)
    {
        if(!CheckResultIsNull(result))
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
    if(!CheckResultIsNull(result))
    {
        *result = RLE_LIST_SUCCESS;
    }

    return letter;




}

int countPlaces(int num)
{int count=0;
    while(num!=0)
    {
        count++;
        num=num/10;
    }
    return count;
}

int countPlacesNeedList(RLEList list)
{int count=0;
    Node node=list->head;
    while (node!=NULL)
    {
        count+=countPlaces(node->numOfAppears);
        node=node->next;
    }
    return count;
}


char* RLEListExportToString(RLEList list, RLEListResult* result)
{

    char *str = malloc((sizeof(*str)+1));
    if(str==NULL)
    { if(!CheckResultIsNull(result))
        {
            *result= RLE_LIST_OUT_OF_MEMORY;
        }
        return NULL;
    }

    str[0]='\0';




    if (list == NULL)
    { if(!CheckResultIsNull(result))
        {
            *result=RLE_LIST_NULL_ARGUMENT;
        }
            return NULL;
    }

    if(list->length==0)
    {if(!CheckResultIsNull(result))
        {
            *result=RLE_LIST_SUCCESS;
        }
        return  str;
    }



    Node node = list->head;
    int size=countPlacesNeedList(list)+(2*list->length);

    char *exportedToString = malloc((sizeof(*exportedToString)*((size))+1));
    if(exportedToString==NULL)
    {
        if(!CheckResultIsNull(result))
        {
            *result=RLE_LIST_OUT_OF_MEMORY;
        }
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

   if(!CheckResultIsNull(result))
   {
       *result = RLE_LIST_SUCCESS;
   }

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
        count=0;
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

/*
int main ()
{
    RLEListResult T;
    RLEList list = RLEListCreate();
   for (int i = 0; i < 400; ++i)
   {
        RLEListAppend(list, '1');
   }
    for (int i = 0; i < 4000; ++i)
    {
        RLEListAppend(list, '2');

    }


    char *x = RLEListExportToString(list, &T);
    printf("%c", x[0]);
    printf("%c", x[1]);
    printf("%c", x[2]);
    printf("%c", x[3]);
    printf("%c", x[4]);
    printf("%c", x[5]);
    printf("%c", x[6]);
    printf("%c", x[7]);
    printf("%c", x[8]);
    printf("%c", x[9]);
    printf("%c", x[10]);


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

*/
/*
1 Running basicTest ... here [OK]
2 Running basicTestMacros ... [OK]
3 Running RLEListCreateTest ... [OK]
4 Running RLEListDestroyTest ... [OK]
5 Running RLEListAppendTest ... [OK]
6 Running RLEListSizeTest ... here here here here [OK]
7 Running RLEListRemoveTest ... here here here here here [OK]
8 Running RLEListGetTest ... [OK]
9 Running RLEListExportToStringTest ... here here here [OK]
10 Running RLEListMapTest ... [OK]
11 Running RLEListMapAndExportTest ... [OK]*/
