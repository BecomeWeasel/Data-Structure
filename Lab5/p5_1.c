#include <stdio.h>
#include <stdlib.h>

struct CompleteTree
{
		int Size;
		int nodeNum;
		int *element;
};
typedef struct CompleteTree *Tree;

#define TREE_START_INDEX 1

Tree CreateTree(int);

void Insert(Tree, int);

void printTree(Tree);

void printPreorder(Tree, int);

void printInorder(Tree, int);

void freeTree(Tree);

int GetLeftChildIndex(int);

int GetRightChildIndex(int);

int GetParentIndex(int);

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
	tree->element = (int *) malloc(sizeof(int) * (treeSize + 1));
	tree->Size = treeSize;
	tree->nodeNum = 0;
	return tree;
}

void Insert(Tree tree, int Value)
{
	if (tree->nodeNum == tree->Size)
	{
		printf("Error!Tree is Full\n");
		return;
	}
	tree->element[++tree->nodeNum] = Value;
}

void printTree(Tree tree)
{
	printf("\nPreOrder: ");
	printPreorder(tree, TREE_START_INDEX);
}

void printPreorder(Tree tree, int index)
{
	if (tree->element[index] && index <= tree->nodeNum)
	{
		printf("%d ", tree->element[index]);
		printPreorder(tree, 2 * index);
		printPreorder(tree, 2 * index + 1);
	}
}

void freeTree(Tree tree)
{
	free(tree->element);
	free(tree);
}
