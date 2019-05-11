#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Queue *Queue;
typedef struct _Graph *Graph;

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

Graph CreateGraph(int *input_nodes, int numberofNode);

void InsertEdge(Graph G, int a, int b);

void DeleteGraph(Graph G);

void PrintGraph(Graph G);

void checkIndegree(int *indegree,Graph G);

void Topsort(Graph G);

Queue MakeNewQueue(int X);

void Enqueue(Queue Q, int X);

int Dequeue(Queue Q,Graph G);

int IsEmpty(Queue Q);

int IsFull(Queue Q);

void DeleteQueue(Queue Q);

void MakeEmpty(Queue Q);

int main(int argc, char **argv)
{
	int i = 0;
	int *int_node;
	char input_node[100];
	char *token;
	Graph G;
	FILE *fi = fopen(argv[1], "r");
	fgets(input_node, 100, fi);
	int_node = (int *) malloc(sizeof(int) * strlen(input_node));
	strtok(input_node,"\n");
	token = strtok(input_node, " ");
	while (token != NULL)
	{
		int_node[i++] = atoi(token);
		token = strtok(NULL, " ");
	}
	G = CreateGraph(int_node, i);
	while (!feof(fi))
	{
		fscanf(fi, "%s", input_node);
		token = strtok(input_node, "-");
		if (token == NULL) break;
		int a = atoi(token);
		token = strtok(NULL, " ");
		if (token == NULL) break;
		int b = atoi(token);
		InsertEdge(G, a, b);
	}
	Topsort(G);
	DeleteGraph(G);
	return 0;
}

Graph CreateGraph(int *input_nodes, int numberOfNode)
{
	Graph target = (Graph) malloc(sizeof(struct _Graph));

	target->size = numberOfNode;
	target->node = (int *) malloc(sizeof(int) * numberOfNode);

	for (int i = 0; i < numberOfNode; i++)
	{
		target->node[i] = input_nodes[i];
	}
	target->matrix = (int **) malloc(numberOfNode * sizeof(int *));

	for (int i = 0; i < numberOfNode; i++)
	{
		target->matrix[i] = (int *) malloc(numberOfNode * sizeof(int));
	}

	for (int i = 0; i < numberOfNode; i++)
	{
		for (int j = 0; j < numberOfNode; j++)
		{
			target->matrix[i][j] = 0;
		}

	}

	return target;
}

void InsertEdge(Graph G, int src, int dest)
{
	int srcIndex;
	int destIndex;

	for (int i = 0; i < G->size; i++)
	{
		if (G->node[i] == src) srcIndex = i;
		if (G->node[i] == dest) destIndex = i;
	}

	G->matrix[srcIndex][destIndex] = 1;
}

void DeleteGraph(Graph G)
{
	for (int i = 0; i < G->size; i++)
	{
		free(G->matrix[i]);
	}
	free(G->matrix);
	free(G->node);
	free(G);
}

void PrintGraph(Graph G)
{
	printf("  ");
	for (int i = 0; i < G->size; i++)
	{
		printf("%d ", G->node[i]);
	}
	printf("\n");

	for (int k = 0; k < G->size; k++)
	{
		printf("%d ", G->node[k]);
		for (int j = 0; j < G->size; j++)
		{
			printf("%d ", G->matrix[k][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void checkIndegree(int * indegree,Graph G){
	for(int i=0;i<G->size;i++){
		indegree[i]=0;
		for(int j=0;j<G->size;j++){
			if(G->matrix[j][i]==1) indegree[i]++;
		}
	}
}

void Topsort(Graph G){
	Queue Q=MakeNewQueue(G->size);
	int V;
	int* InDegree=(int *)malloc(sizeof(int)*G->size);
	checkIndegree(InDegree,G);
	for(int i=0;i<G->size;i++){
		if(InDegree[i]==0)
			Enqueue(Q, i); // index 삽입
	}
	while(!IsEmpty(Q)){
		V=Dequeue(Q,G);
		for(int i=0;i<G->size;i++){
			if(G->matrix[V][i]==1){
				G->matrix[V][i]=0;
				InDegree[i]--;
				if(InDegree[i]==0) Enqueue(Q,i);
			}
		}

	}
	DeleteQueue(Q);
}

Queue MakeNewQueue(int X){
	Queue q=(Queue)malloc(sizeof(struct _Queue));
	q->qsize=0;
	q->key=malloc(sizeof(int)*X);
	q->rear=-1;
	q->first=0;
	q->max_queue_size=X;
	return q;
}

void Enqueue(Queue Q,int X){
	Q->qsize++;
	Q->key[++Q->rear]=X;
}

int Dequeue(Queue Q,Graph G){
	printf("%d ",G->node[Q->key[Q->first]]);
	Q->qsize--;
	return Q->key[Q->first++];
}

int IsEmpty(Queue Q){
	return Q->qsize==0;
}

int IsFull(Queue Q){
	return Q->qsize==Q->max_queue_size;
}

void DeleteQueue(Queue Q){
	free(Q->key);
	free(Q);
}

void MakeEmpty(Queue Q){

}
