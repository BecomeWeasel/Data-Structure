#include <stdio.h>
#include <stdlib.h>

#define MAX_NAME_SIZE 30

int main(int argc,char *argv[]){
  int numOfName=atoi(argv[1]);
  if(numOfName<2){
    printf("the number of students should be more than two.\n");
    return 0;
  }
 
  char **nameArray=(char**)malloc(sizeof(char*)*numOfName);
  for(int i=0;i<numOfName;i++){
    nameArray[i]=(char*)malloc(sizeof(char)*MAX_NAME_SIZE);
  }

  printf("enter %d names\n",numOfName);
 

  for(int i=0;i<numOfName;i++){
    scanf("%s",nameArray[i]);
  }



  printf("the names you entered \n");
  for (int i=0;i<numOfName;i++){
    printf("%s \n",nameArray[i]);
    free(nameArray[i]);
  }
  free(nameArray);
  return 0;
}
