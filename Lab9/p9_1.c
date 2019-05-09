#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Queue* Queue;
typedef struct _Graph* Graph;

struct _Queue
{
  int *key;
  int first;
  int rear;
  int qsize;
  int max_queue_size;
};

struct _Graph
{
  int size;
  int *node;
  int **matrix;
};

Graph CreateGraph(int* nodes);
void InsertEdge(Graph G, int a, int b); 
void DeleteGraph(Graph G);

int main(int argc,char** argv){
  FILE *fp=fopen(argv[1],"r");
  int size=0;
  int num;
  char buffer[128];
  //for loop to count node number
  // size=somevalue;
  
  fgets(buffer,sizeof(buffer),fp);



  int* temp=(int*)malloc(sizeof(int)*size);

  for(int j=0;j<size
      &&fscanf(fp,"%d ",&num)!=EOF;j++){
    temp[j]=num;
  }
  


}

Graph CreateGraph(int* nodes){

}

void InsertEdge(Graph G,int src,int dest){

}

void DeleteGraph(Graph G){
  
}
