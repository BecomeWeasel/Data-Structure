#include <stdio.h>
#include <stdlib.h>

typedef struct CompleteTree *Tree;
struct CompleteTree
{
		int Size;
		int nodeNum;
		int *element;
};

Tree CreateTree(int);

void Insert(Tree, int);

void printTree(Tree);

void printInOrder(Tree, int);

void freeTree(Tree);

int GetLeftChildIndex(int);

int GetRightChildIndex(int);

int GetParentIndex(int);

void PrintPreOrder(Tree, int);

int main(int argc, char *argv[])
{

	FILE *fi;
	Tree tree;
	int treeSize;
	int tempNum;

	fi = fopen(argv[1], "r");
	fscanf(fi, "%d", &treeSize);
	tree = CreateTree(treeSize);
	while (fscanf(fi, "%d", &tempNum) == 1)
	{
		Insert(tree, tempNum);
	}
	printTree(tree);
	freeTree(tree);
}

Tree CreateTree(int treeSize)
{
	Tree tree = (Tree) malloc(sizeof(struct CompleteTree));
	tree->element = (int *) malloc(sizeof(int) * treeSize);
	tree->Size = treeSize;
	tree->nodeNum = 0;
	return tree;
}

void Insert(Tree tree, int Value)
{
	if (tree->nodeNum == tree->Size)
	{
		printf("Stack is Full\n");
		return;
	}
	tree->element[tree->nodeNum++] = Value;
}

void printTree(Tree tree)
{
	PrintPreOrder(tree, 0);
}

void PrintPreOrder(Tree tree, int index)
{
	if (tree->element[index]&&index<tree->Size)
	{
		printf("%d ", tree->element[index]);
		PrintPreOrder(tree, GetLeftChildIndex(index));
		PrintPreOrder(tree, GetRightChildIndex(index));
	}
}

int GetLeftChildIndex(int parentIndex)
{
	return parentIndex * 2 + 1;
}

int GetRightChildIndex(int parentIndex)
{
	return (parentIndex + 1) * 2;
}

int GetParentIndex(int originIndex)
{
	if (originIndex % 2 == 1)
	{ return (originIndex - 1) / 2; }
	else return originIndex / 2 - 1;
}

void freeTree(Tree tree)
{
	free(tree->element);
	free(tree);
}
