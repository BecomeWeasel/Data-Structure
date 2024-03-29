#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define INT_MAX 2147438647
#define INT_MIN -2147438647


int Zero();
bool IsZero(int);
bool Equal(int,int);
int Successor(int);
int Add(int,int);
int Subtract(int,int);

int main(int argc,char ** args){
  int x=atoi(args[1]);
  int y=atoi(args[2]);

  printf("Is %d Zero? %s\n",x,IsZero(x)?"True":"False");
  printf("Is %d Zero? %s\n",y,IsZero(y)?"True":"False");
  printf("Does %d equal %d? %s\n",x,y,Equal(x,y)?"True":"False");
  printf("%d's next number is %d\n",x,Successor(x));
  printf("%d's next number is %d\n",y,Successor(y));
  printf("%d+%d=%d\n",x,y,Add(x,y));
  printf("%d-%d=%d\n",x,y,Subtract(x,y));
  

  return 0;
}

int Zero(){
  return 0;
}

bool IsZero(int num){
  if(num==Zero())
    return true;
  else
    return false;
}

bool Equal(int num1,int num2){
  if(num1==num2)
    return true;
  else
    return false;
}

int Successor(int t){
  if(t+1<INT_MAX){
    return t+1;
  }
  else{
    return t;
  }
}

int Add(int num1,int num2){
  if(num1+num2<INT_MAX){
    return num1+num2;
  }
  else {
    return INT_MAX;
  }
}

int Subtract(int num1,int num2){
  if(num1>num2){
    return num1-num2;
  }
  else{
   return 0;
  }
}

