#include <stdio.h>
#include <stdlib.h>

typedef struct BinarySearchTree* Tree;
struct BinarySearchTree{
  int value;
  Tree left;
  Tree right;
};

Tree insertNode(Tree root,int key);
void findNode(Tree root,int key);
void printInorder(Tree root);
void deleteTree(Tree root);

int main(int argc,char* argv[]){
  FILE* fi=fopen(argv[1],"r");
  char cv;
  int key;

  Tree root=NULL;
  while(!feof(fi)){
    fscanf(fi,"%c",&cv);
    switch(cv){
      case 'i':
        fscanf(fi,"%d",&key);
        root=insertNode(root,key);
        break;
      case 'd':
       // fscanf(fi,"%d",&key);
       // deleteTree(root,key);
        break;
      case 'f':
        fscanf(fi,"%d",&key);
        findNode(root,key);
        break;
      case 'p':
        fscanf(fi,"%c",&cv);
        if(cv=='i'){
          printInorder(root);
        }
        printf("\n");
    }
  }
  deleteTree(root);
  return 0;
}

Tree insertNode(Tree root,int key){
  if(root==NULL){
    root=(Tree)malloc(sizeof(struct BinarySearchTree));
    if(root==NULL){
      printf("OUT OF MEMORY!!");
      return NULL; // TREE malloc failed
    }else{
      root->value=key;
      root->left=root->right=NULL;
    }
  }
  else if(key<root->value){
    root->left=insertNode(root,key);
    
  }
  else if(key>root->value){
    root->right=insertNode(root,key);
  }
  else{ // key is alread in the list
    printf("already in the list!\n");
  }


  return root;
}

void findNode(Tree root,int key){
  if(root==NULL){
    printf("%d is not in the list\n",key);
    return;
  }
  else if (key<root->value){
    findNode(root->left,key);
  }
  else if(key>root->value){
    findNode(root->right,key);
  }
  else { // find success
    printf("%d is in the list\n",key);
  }
}

void printInorder(Tree root){
  if(root==NULL){
    return;
  }
  printInorder(root->left);
  printf("%d ",root->value);
  printInorder(root->right);
}

void deleteTree(Tree root){
  if(root==NULL){
    return;
  }
  deleteTree(root->left);
  deleteTree(root->right);
}

