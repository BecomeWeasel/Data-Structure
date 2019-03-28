#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stack{
  int *key;
  int top;
  int max_stack_size;
}Stack;

Stack* CreateStack(int);
void Push(Stack*,int);
int IsFull(Stack *);
void DeleteStack(Stack*);

Stack* CreateStack(int max){
  if(max==NULL) 
  {
    printf("ERROR:Null paramter on CreateStack function!\n");
    return NULL;
  }
  Stack* S=NULL;
  S=(Stack*)malloc(sizeof(struct Stack));
  if(S==NULL){
    printf("ERROR:Out of MEMORY,stack malloc failed\n");
    return NULL;
  }
  S->key=(int*)malloc(sizeof(int)*max);
  if(S->key==NULL){
    printf("ERROR:Out of MEMORY,key malloc failed\n");
    return NULL;
  }
  S->max_stack_size=max;
  S->top=-1;
  return S;
}

void Push(Stack* S,int X){
  if(S==NULL||X==NULL){
    printf("ERROR:Null parameter on Push function,Invalid stack pointer\n");
    return;
  }
  if(IsFull(S)){
   printf("FULL Stack\n");
   return;
  }
  else
  {
    printf("%d current top\n",S->top);
    S->key[++S->top]=X;
    printf("%d after insertion\n",S->top);
  }
  printf("%d inserted\n",X);
}

int IsFull(Stack* S){
  if(S==NULL){
    printf("ERROR:Null paramter on IsFull function,Invalid stack pointer\n");
    return NULL;
  }
  else{
   return S->max_stack_size<=S->top-1;
  }
}

void DeleteStack(Stack *S){
  free(S->key);
  free(S);
}

int main(int argc,char *argv[]){
  FILE* fi=fopen(argv[1],"r");

  Stack* stack;
  char input_str[101];
  int max,i=0,a,b,result;

  fgets(input_str,101,fi);
  max=10;
  stack=CreateStack(max);
  //p4_1 main code
  //
  for(i=0;i<strlen(input_str)&&input_str[i]!='#';i++){
    printf("%c\n",input_str[i]);
    Push(stack,atoi(input_str[i]));

  }
  fclose(fi);
  DeleteStack(stack);

}


