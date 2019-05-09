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

int main(int argc, char **argv)
{
	FILE *fp = fopen(argv[1], "r");
	int size = 0;
	int num;
	char bufferforcount[128];
	char buffer2[128];
	char bufferforedgs[128];
	Graph myGraph;
	//for loop to count node number
	// size=somevalue;

	int phase = 0;
	while (fgets(bufferforcount, sizeof(bufferforcount), fp))
	{
		phase++;
		strtok(bufferforcount, "\n");
		if (phase == 1)
		{
			strcpy(buffer2, bufferforcount);

			char *tempstr;

			tempstr = strtok(bufferforcount, " ");
			size++;

			while (1)
			{
				tempstr = strtok(NULL, " ");
				if (tempstr == NULL) break;
				size++;
			}


			tempstr = NULL;

			int *setOfNodes = (int *) malloc(sizeof(int) * size);



			char *tempstr2 = strtok(buffer2, " ");
			setOfNodes[0] = atoi(tempstr2);

			for (int j = 1; j < size; j++)
			{
				tempstr2 = strtok(NULL, " ");
				setOfNodes[j] = atoi(tempstr2);
			}

			myGraph = CreateGraph(setOfNodes, size);
		}
		else if (phase == 2)
		{

			// 입력이 두줄만 온다고 가정?
			char *edgestr = NULL;

			while (1)
			{
				edgestr = strtok(edgestr == NULL ? bufferforcount : NULL, " ");
				if(edgestr==NULL) break;
				InsertEdge(myGraph,edgestr[0]-'0',edgestr[2]-'0');
			}
		}
	}
	// print matrix
	printf("  ");
	for(int i=0;i<size;i++){
		printf("%d ",myGraph->node[i]);
	}
	printf("\n");

	for(int k=0;k<size;k++){
		printf("%d ",myGraph->node[k]);
		for(int j=0;j<size;j++){
			printf("%d ",myGraph->matrix[k][j]);
		}
		printf("\n");
	}
	printf("\n");

	//
	DeleteGraph(myGraph);
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

	for(int i=0;i<numberOfNode;i++){
		for(int j=0;j<numberOfNode;j++){
			target->matrix[i][j]=0;
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
