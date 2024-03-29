#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct HeapStruct{
  int Capacity;
  int Size;
  int *Element;
}Heap;

Heap* CreateHeap(int);
void Insert(Heap*,int);
int Find(Heap*,int);
int DeleteMax(Heap*);
void PrintHeap(Heap*);

void main(int argc,char* argv[]){
  FILE* fi=fopen(argv[1],"r");
  char cv;
  Heap* maxHeap;
  int heapsize,key;
  while(!feof(fi)){
    fscanf(fi,"%c",&cv);
    switch(cv){
      case 'n':
        fscanf(fi,"%d",&heapsize);
        maxHeap=CreateHeap(heapsize);
        break;
      case 'i':
        fscanf(fi,"%d",&key);
        Insert(maxHeap,key);
        break;
      case 'd':
        DeleteMax(maxHeap);
        break;
      case 'p':
        PrintHeap(maxHeap);
        break;
      case 'f':
        fscanf(fi,"%d",&key);
        if(Find(maxHeap,key)){
          printf("%d is in the heap.\n",key);}
        else{
          printf("%d is not in the heap.\n",key);
        }
        break;
        }
    }
}



Heap* CreateHeap(int heapSize){
 Heap* heap=(Heap*)malloc(sizeof(struct HeapStruct));
 heap->Element=(int*)malloc(sizeof(int)*(heapSize+1));
 heap->Capacity=heapSize;
 heap->Size=0;
 heap->Element[0]=INT_MAX;
 return heap;
}

void Insert(Heap* heap,int value){
  int i;
  if(heap->Size>=heap->Capacity){
    printf("Insertion Error: Max Heap is full.\n");
    return;
  }
  if(Find(heap,value)){
    printf("%d is already in the heap.\n",value);
    return ;
  }
  for(i=++heap->Size;heap->Element[i/2]<value;i/=2)
    heap->Element[i]=heap->Element[i/2];
  heap->Element[i]=value;
  printf("insert %d\n",value);
}

int Find(Heap* heap,int target){
  for(int i=1;i<=heap->Size;i++){
    if(heap->Element[i]==target) return 1;
  }
  return 0;
}

int DeleteMax(Heap* heap){
  if(heap->Size==0){
    printf("Deletion Error: Max Heap is empty !\n");
    return -INT_MAX;
  }
  int i,Child;
  int MaxElement,LastElement;

  MaxElement=heap->Element[1];
  LastElement=heap->Element[heap->Size--];
  
  for(i=1;i*2<=heap->Size;i=Child){
    Child=i*2;

    if(Child!=heap->Size&&heap->Element[Child]<heap->Element[Child+1]){
      Child++;
    }

    if(LastElement<heap->Element[Child])
      heap->Element[i]=heap->Element[Child];
    else 
      break;
  }
  
  heap->Element[i]=LastElement;
  printf("Max Element: %d deleted\n",MaxElement);
  return MaxElement;
}

void PrintHeap(Heap* heap){
  if(heap->Size==0) {
    printf("Print Error: Max Heap is empty !\n");
    return ;
  }
 for(int i=1;i<heap->Size+1;i++){
   printf("%d ",heap->Element[i]);
 } 
 printf("\n");
}



