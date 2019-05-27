#include<stdio.h>
#include<stdlib.h>
#include <limits.h>
#include<string.h>

typedef struct Node
{
	int vertex;
	int dist; //distance int prev;
	int prev;
} Node;
typedef struct Graph
{
	int size;
	int **vertices;
	Node *nodes;
} Graph;
typedef struct Heap
{
	int Capacity;
	int Size;
	Node *Element;
} Heap;

Graph* CreateGraph(int size);

void printShortestPath(Graph* g);

Heap *createMinHeap(int heapSize);

void insertToMinHeap(Heap *minHeap, int vertex, int distance);

Node deleteMin(Heap *minHeap);

void decreaseKey(struct Heap* minHeap, int v, int dist);

void PercDown (struct Heap* minheap, int i, int N);

int Find(Heap* minheap,int target);

int main(int argc, char *argv[])
{
	{
		FILE *fi = fopen(argv[1], "r");
		Graph* g;
		int size;
		fscanf(fi,
		       "%d\n", &size);
		g = CreateGraph(size + 1); // +1 을 해서 던지면 V의 숫자하고 인덱스하고 같음
		for(int i=0;i<g->size;i++){
			for(int j=0;j<g->size;j++)
				g->vertices[i][j]=0;
		}
		char temp = 0;

		while (temp != '\n')
		{
			int node1, node2, weight;
			fscanf(fi,
			       "%d-%d-%d", &node1, &node2, &weight);
			g->vertices[node1][node2] =
							weight;
			temp = fgetc(fi);
		}
		printShortestPath(g);
	}
	return 0;
}

Graph* CreateGraph(int size){
	Graph* target = (Graph*) malloc(sizeof(struct Graph));

	target->size = size;
	target->nodes = (Node *) malloc(sizeof(Node) * size);

	target->vertices=(int**)malloc(sizeof(int*)*size);

	for(int i=0;i<size;i++){
		target->vertices[i] = (int *) malloc(sizeof(int) * size);
	}


	for (int i = 1; i < size; i++)
	{
		target->nodes[i].vertex=i;
//		target->nodes[i].dist=INT_MAX;
//		target->nodes[i].prev=0;
	}

	return target;
}

void printShortestPath(Graph * G){

	Heap *minHeap = createMinHeap(G->size);
	
	int SP[G->size];
	for(int i=1;i<G->size;i++){
		SP[i]=0;
	}

	for(int i=1; i<G->size; i++){
		G->nodes[i].dist=INT_MAX;
		G->nodes[i].prev=0;
	}

	G->nodes[1].dist=0;
	SP[1]=1;


	for(int i=1; i<G->size; i++) { // i가 2에서 시작해도 상관없음.
		if(G->vertices[1][i]!=0){
			G->nodes[i].dist=G->vertices[1][i];
			G->nodes[i].prev=1;
		}
	}
	for(int i=2;i<G->size;i++){
		insertToMinHeap(minHeap,i,G->nodes[i].dist);
	}

	while(minHeap->Size!=0){
		Node targetNode = deleteMin(minHeap);

		SP[targetNode.vertex]=1;
		for(int i=1;i<G->size;i++){
			if(G->vertices[targetNode.vertex][i]!=0 && SP[i]!=1){ // i가 adjacent 한지 체크 , SP가 1이면 이미 방문한 노드.
				if(G->nodes[targetNode.vertex].dist+ G->vertices[targetNode.vertex][i]
				   < G->nodes[i].dist ){
					G->nodes[i].dist=G->nodes[targetNode.vertex].dist+ G->vertices[targetNode.vertex][i];
					G->nodes[i].prev=targetNode.vertex;

					// 거리 조절
					decreaseKey(minHeap, i, G->nodes[i].dist);
				}
			}
		}
	}
	for(int i=2;i<G->size;i++){
		int route[G->size];
		int pathLength=0;
		int pointToV;


		route[0]=i;
		pathLength++;
		pointToV=i;


		while(1){
			if(G->nodes[pointToV].prev!=0&&pointToV!=1){
				route[pathLength++]=G->nodes[pointToV].prev;

				pointToV=G->nodes[pointToV].prev;
			}
			else
				break;
		}
//		printf route
		if(pathLength==1){
			printf("Cannot reach to node %d.\n",i);
		}else{
			for(int i=pathLength-1;i>=0;i--){
				printf("%d",route[i]);
				if(i!=0)
					printf("->");
			}
			printf(" (cost : %d)",G->nodes[i].dist);
			printf("\n");
		}
	}

}

Heap * createMinHeap(int heapSize){
	Heap *heap = (Heap *) malloc(sizeof(struct Heap));
	heap->Element = (Node *) malloc(sizeof(Node) * (heapSize));
	heap->Capacity = heapSize;
	heap->Size = 0;

	return heap;
}

void insertToMinHeap(Heap *minHeap,int vertex,int distance){
	int i;
	if (minHeap->Size >= minHeap->Capacity)
	{
		printf("Insertion Error: Max Heap is full.\n");
		return;
	}
//	if (0) //이미 있으면
//	{
//		printf("%d is already in the minHeap.\n", ver);
//		return;
//	}
	for (i = ++minHeap->Size; minHeap->Element[i / 2].dist > distance; i /= 2){
		minHeap->Element[i] = minHeap->Element[i / 2];
	}
	minHeap->Element[i].vertex=vertex;
	minHeap->Element[i].dist=distance;
}

Node deleteMin(Heap* minHeap){
	if (minHeap->Size == 0)
	{
		printf("Deletion Error: Max Heap is empty !\n");
		Node tmp;
		return tmp;
	}
	int i, Child;
	Node MinElement, LastElement;

	MinElement = minHeap->Element[1];
	LastElement = minHeap->Element[minHeap->Size--];

	for (i = 1; i * 2 <= minHeap->Size; i = Child)
	{
		Child = i * 2;

		if (Child != minHeap->Size && minHeap->Element[Child+1].dist < minHeap->Element[Child].dist)
		{
			Child++;
		}

		if (LastElement.dist > minHeap->Element[Child].dist)
			minHeap->Element[i] = minHeap->Element[Child];
		else
			break;
	}

	minHeap->Element[i]=LastElement;

	return MinElement;
}
void decreaseKey(struct Heap* minHeap, int v, int dist)
{
	int i;
	for(i=1;i<minHeap->Size;i++){
		if(minHeap->Element[i].vertex==v){
			break;
		}
	}

	minHeap->Element[i].dist=dist;


	while(minHeap->Size>1&&minHeap->Element[i/2].dist>minHeap->Element[i].dist){
		Node tmp;
		tmp=minHeap->Element[i/2];
		minHeap->Element[i/2]=minHeap->Element[i];
		minHeap->Element[i]=tmp;
		i=i/2;
	}

//	for(int i=minHeap->Size/2;i>0;i--){
//		PercDown(minHeap,i,minHeap->Size);
//	}
}

void PercDown (struct Heap* minheap, int i, int N)
{
	int Child;
	Node tmp;

	for (tmp = minheap->Element[i]; i*2 < N; i = Child)
	{
		Child=i*2;
		if (Child != N - 1 && minheap->Element[Child + 1].dist > minheap->Element[Child].dist)
			Child++;
		if (tmp.dist < minheap->Element[Child].dist){
			minheap->Element[i] = minheap->Element[Child];
		}
		else
			break;
	}
	minheap->Element[i] = tmp;
}

int Find(Heap* heap,int target){
	for(int i=1;i<=heap->Size;i++){
		if(heap->Element[i].vertex==target) return 1;
	}
	return 0;
}