#include <stdio.h>
#include <stdlib.h>

typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
typedef int ElementType;

struct Node
{
  ElementType element;
  Position next;
};

#define HEADER -1

void Delete(ElementType,List );
Position Find(ElementType,List);
Position FindPrevious(ElementType,List);
void DeleteList(List);

List MakeEmpty(List);
int IsEmpty(List);
int IsLast(Position,List);
void Insert(ElementType,List,Position);
void PrintList(List);
void DeleteList(List);

int main(int argc,char *argv[]){
  char command;
  int key1,key2;
  FILE *input;
  Position header=NULL;
  Position tmp=NULL;
  if(argc==1){
    printf("NO input file\n");
    return 0;
  }
  else
    input=fopen(argv[1],"r");
  header=MakeEmpty(header);
  while(1){
    command=fgetc(input);
    if(feof(input)) break;
    switch(command){
      case 'i':
        fscanf(input,"%d %d",&key1,&key2);
        if(key2==-1){
          Insert(key1,header,header);
        }
        else{
          tmp=Find(key2,header);
          if(tmp==NULL){
            printf("Insertion(%d) Failed : cannot find the location to be inserted\n",key1);
          break;
          }
          else
          {
          Insert(key1,header,tmp);
          }

        }
        printf("insert %d\n",key1);
        break;
      case 'd':
        fscanf(input,"%d",&key1);
        Delete(key1,header);
        break;
      case 'f':
        fscanf(input,"%d",&key1);
        tmp=FindPrevious(key1,header);
        if(IsLast(tmp,header))
          printf("Could not find %d in the list\n",key1);
        else{
          if(tmp->element>0)
            printf("key of the previous node of %d is %d.\n",key1,tmp->element);
          else
            printf("key of the previous node of %d is header.\n",key1);
        }
        break;
      case 'p':
        PrintList(header);
        break;
      default:
        break;

    }
  }
  DeleteList(header);
  fclose(input);
  return 0;
}

void Delete(ElementType X,List L){
  Position P,temp;

  P=FindPrevious(X,L);
  if(!IsLast(P,L)){
    temp=P->next;
    P->next=temp->next;
    free(temp);
  }
  else
  {
    printf("Deletion failed : %d is not in the list\n",X);
    return;
  }

}

Position Find(ElementType X,List L){
  Position P;
  P=L->next;

  while(P!=NULL&&P->element!=X){
    P=P->next;
  }
  return P;
}

Position FindPrevious(ElementType X,List L){
  Position P;
  P=L;
  while(P->next!=NULL&&P->next->element!=X){
    P=P->next;
  }
  return P;
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
    printf("FATAL ERROR: Out Of Memory\n");
    return;
  }
  Temp->element=X;
  Temp->next=P->next;
  P->next=Temp;
}

void PrintList(List L){
  Position currentPointer;
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
