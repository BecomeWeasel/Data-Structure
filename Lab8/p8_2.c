//
// Created by RYAN on 04/05/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef int ElementType;
typedef struct AVLNode* AVLTree;
typedef struct AVLNode* Position;
struct AVLNode{
	ElementType Element;
	AVLTree Left;
	AVLTree Right;
	int Height;
};

AVLTree Insert(ElementType,AVLTree);
void printInorder(AVLTree);
Position SingleRotateWithLeft(Position);
Position SingleRotateWithRight(Position);
Position DoubleRotateWithLeft(Position);
Position DoubleRotateWithRight (Position);

int Height(AVLTree);
int Max(int,int);
void DeleteTree(AVLTree);


int main(int argc,char**argv){
	FILE *fp=fopen(argv[1],"r");
	AVLTree myTree=NULL;
	int num;



	if(fp==NULL){
		printf("there is no file : %s\n",argv[1]);
	}
	while(fscanf(fp,"%d",&num)!=EOF){

		myTree=Insert(num,myTree);
		printInorder(myTree);
		printf("\n");
	}
	DeleteTree(myTree);
	return 0;
}

AVLTree Insert(ElementType X,AVLTree T){
	if(T==NULL){
		T=(AVLTree)malloc(sizeof(struct AVLNode));
		if(T==NULL)
			printf("Out of MEMORY!!\n");
		else{
			T->Element=X;
			T->Height=0;
			T->Left=T->Right=NULL;
		}
	}else if(X<T->Element){
		T->Left=Insert(X,T->Left);
		if(Height(T->Left)-Height(T->Right)==2){
			if(X<T->Left->Element)
				T=SingleRotateWithLeft(T);
			else
				T=DoubleRotateWithLeft(T);
		}
	}
	else if(X>T->Element){
		T->Right=Insert(X,T->Right);
		if(Height(T->Right)-Height(T->Left)==2){
			if(X>T->Right->Element)
				T=SingleRotateWithRight(T);
			else
				T=DoubleRotateWithRight(T);
		}
	}
	else{
		printf("[Error] %d already in the tree!\n",X);
	}
	T->Height=Max(Height(T->Left),Height(T->Right))+1;
	return T;
}

void printInorder(AVLTree tree){
	if(tree==NULL)
		return;
	printInorder(tree->Left);
	printf("%d (%d) ",tree->Element,tree->Height);
	printInorder(tree->Right);
}

Position SingleRotateWithLeft(Position K2){
	Position K1;

	K1=K2->Left;

	K2->Left=K1->Right;
	K1->Right=K2;

	K2->Height=Max(Height(K2->Left),Height(K2->Right))+1;
	K1->Height=Max(Height(K1->Left),K2->Height)+1;

	return K1;
}

Position SingleRotateWithRight(Position K2){
	Position K1;

	K1=K2->Right;

	K2->Right=K1->Left;
	K1->Left=K2;

	K2->Height=Max(Height(K2->Right),Height(K2->Left))+1;
	K1->Height=Max(Height(K1->Right),K2->Height)+1;

	return K1;
}

Position DoubleRotateWithLeft(Position K3){

	/* rotate between K1 and K2*/
	K3->Left=SingleRotateWithRight(K3->Left); /* K2 */

	/* rotate between K3 and K2*/
	return SingleRotateWithLeft(K3); /* K2 */

}

Position DoubleRotateWithRight(Position K3){

	/* rotate between K1 and K2 */
	K3->Right=SingleRotateWithLeft(K3->Right); /* K2 */

	/* rotate between K3 and K2 */
	return SingleRotateWithRight(K3); /* K2*/
}

int Height(AVLTree T){
//  int leftHeight;
//  int rightHeight;
//
//	if(T==NULL) return -1;
//
//  if(T->Left==NULL)
//    leftHeight=0;
//  else leftHeight=T->Left->Height;
//
//  if(T->Right==NULL)
//    rightHeight=0;
//  else rightHeight=T->Right->Height;
//
//  return leftHeight>rightHeight?leftHeight:rightHeight;
	if(T==NULL){
		return -1;
	}
	else{
		T->Height=Max(Height(T->Left),Height(T->Right))+1;
		return T->Height;
	}
}

int Max(int a,int b){
	return a>b?a:b;
}

void DeleteTree(AVLTree T){
	if(T!=NULL){
		DeleteTree(T->Left);
		DeleteTree(T->Right);
		free(T);
	}
}