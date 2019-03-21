#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
typedef int ElementType;

#define HEADER -1

struct Node
{
  ElementType element;
  Position next;
};

List MakeEmpty(List L);
int IsEmpty(List L);
int IsLast(Position P,List L);
void Insert(ElementType X,List L,Position P);
void PrintList(List L);
void DeleteList(List L);

int main(int argc,char *argv[]){
  char command;
  int key1,key2;
  FILE *input;
  Position header=NULL;
  Position tmp;
  if(argc ==1){
    printf("No Input File\n");
    return 0;
  }
  else
    input=fopen(argv[1],"r");
  header=MakeEmpty(header);
  while(1){
    command=fgetc(input);
    if(feof(input)) break;
    //printf("%c \n",command);
    switch(command){
      case 'i':
        fscanf(input,"%d %d",&key1,&key2);
        //find func
        //insert func hw3
        Insert(key1,header,header);
        break;
     // case 'd':
     //   fscanf(input,"%d",&key1);
        //delete func hw3
     //   break;
     // case 'f':
      //  fscanf(input,"%d",&key1);
        //tmp=previous func hw3
        //if(IsLast(tmp,header))
        //  printf("Could not find %d in the list \n",key1);
        //else{
        //  if(tmp->element>0)
         //   printf("Key of the previous node of %d is %d.\n",key1,tmp->element);
        //  else
        //    printf("key of the previous node of %d is header.\n",key1);
      //  }
       // break;
      case 'p':
        PrintList(header);
        break;
      default :
        break;
    }
  }
  DeleteList(header);// free all memory used by linked list;
  fclose(input);
  return 0;
}

List MakeEmpty(List L){
  L=(List)malloc(sizeof(struct Node));
  L->element=HEADER;
  L->next=NULL;
  return L;
}

int IsEmpty(List L){
  return L->next==NULL;
}

int IsLast(Position P,List L){
  return P->next==NULL;
}

void Insert(ElementType X,List L,Position P){
  Position Temp;
  Temp=(Position)malloc(sizeof(struct Node));
  if(Temp==NULL){
    printf("FATAL ERROR : Out Of Memory\n");
    return;
  }
  Temp->element=X;
  Temp->next=P->next;
  P->next=Temp;
}

void PrintList(List L){
  PtrToNode currentPointer;
  currentPointer=L->next;
  while(currentPointer!=NULL){
    printf("key : %d\n",currentPointer->element);
    currentPointer=currentPointer->next;
  }
}

void DeleteList(List L){
  Position currentPointer,temp;
  currentPointer=L->next;
  L->next=NULL;
  while(currentPointer!=NULL){
   temp=currentPointer->next;
   free(currentPointer);
   currentPointer=temp;
  }
  free(L);
}


