#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stack
{
		int *key;
		int top;
		int max_stack_size;

} Stack;

#define INPUT_LIMIT 100


Stack *CreateStack(int);

void Push(Stack *, int);

int IsFull(Stack *);

void DeleteStack(Stack *);

int IsEmpty(Stack *);

int Pop(Stack *);

int PostFix(Stack *, char);

int Top(Stack *);

Stack *CreateStack(int max)
{
	Stack *S = NULL;
	S = (Stack *) malloc(sizeof(struct Stack));
	if (S == NULL)
	{
		printf("ERROR:Out of Memory,stack malloc failed\n");
		return NULL;
	}
	S->key = (int *) malloc(sizeof(int) * max);
	if (S->key == NULL)
	{
		printf("ERROR:Out of Memory,key malloc failed\n");
		return NULL;
	}
	S->max_stack_size = max;
	S->top = -1;
	return S;
}

void Push(Stack *S, int X)
{
	if (S == NULL)
	{
		printf("ERROR:Null parameter on Push function,Invalid stack pointer\n");
		return;
	}
	if (IsFull(S))
	{
		printf("\nFull stack insertion failed %d\n", X);
		return;
	}
	else
	{
		S->key[++S->top] = X;
	}
}

int IsFull(Stack *S)
{
	if (S == NULL)
	{
		printf("ERROR:Null paramter on IsFull function\n");
		return NULL;
	}
	else
	{
		return S->max_stack_size - 1 == S->top;
	}
}

void DeleteStack(Stack *S)
{
	free(S->key);
	free(S);
}

int IsEmpty(Stack *S)
{
	if (S == NULL)
	{
		printf("ERROR:NULL paramter on IsFull function\n");
		return -1;
	}
	else
	{
		if (S->top > -1)
		{
			return 0;
		}
		else
		{
			return 1;
		}

	}
}

int Pop(Stack *S)
{
	if (S == NULL)
	{
		printf("ERROR:NULL parameter on IsFull function\n");
		return -1;
	}
	if (IsEmpty(S))
	{
		printf("Empty stack\n");
		return -1;
	}
	else
	{
		return S->key[S->top--];
	}
}

int PostFix(Stack *S, char input_str)
{
	int a, b;
	int result;
	if (S == NULL)
	{
		printf("ERROR:NUll parameter on PostFix function\n");
		return -1;
	}
	switch (input_str)
	{
		case '+':
			b = Pop(S);
			a = Pop(S);
			if (a == -1 || b == -1)
			{
				printf("at least one of operands is empty\nPlease try valid input\n");
				return -1;
			}
			result = a + b;
			Push(S, result);
			printf("%d ", Top(S));
			return result;
			break;
		case '-':
			b = Pop(S);
			a = Pop(S);
			if (a == -1 || b == -1)
			{
				printf("at least one of operands is empty\nPlease try valid linput\n");
				return -1;
			}
			result = a - b;
			Push(S, result);
			printf("%d ", Top(S));
			return result;
		case '*':
			b = Pop(S);
			a = Pop(S);
			if (a == -1 || b == -1)
			{
				printf("at least one of operands is empty\nPlease try valid input\n");
				return -1;
			}
			result = a * b;

			Push(S, result);
			printf("%d ", Top(S));
			return result;

			break;
		case '/':
			b = Pop(S);
			a = Pop(S);
			if (a == -1 || b == -1)
			{
				printf("at least one of operands is empty\nPlease try valid input\n");
				return -1;
			}
			result = a / b;

			Push(S, result);
			printf("%d ", Top(S));
			return result;

			break;
		case '%':
			b = Pop(S);
			a = Pop(S);
			if (a == -1 || b == -1)
			{
				printf("at least one of operands is empty\nPlease try valid input\n");
				return -1;
			}
			result = a % b;

			Push(S, result);
			printf("%d ", Top(S));
			return result;

			break;
		default:

			Push(S, input_str - '0');
			printf("%d ", Top(S));

			break;
	}
}

int Top(Stack *S)
{
	if (S == NULL)
	{
		printf("ERROR:NULL parameter on IsFull function\n");
		return NULL;
	}
	else
	{
		return S->key[S->top];
	}
}

int main(int argc, char *argv[])
{
	if (argc <= 1)
	{
		printf("input file not exist\n");
		return 0;
	}
	FILE *fi = fopen(argv[1], "r");
	if (fi == NULL)
	{
		printf("input file not exist!!\n");
		return 0;
	}
	Stack *stack;
	char input_str[101];
	int max, i = 0, a, b, result;

	fgets(input_str, 101, fi);
	max = 10;
	stack = CreateStack(max);

	printf("Top numbers : ");

	for (i = 0; i < strlen(input_str) && input_str[i] != '#'; i++)
	{
		result = PostFix(stack, input_str[i]);
		if (result == -1)
		{
			printf("something wrong with input or invalid stack structure\n");
			printf("please try with valid postfix evaluation input files\n");
			continue;
		}
	}
	printf("\nevaluation result : %d\n", result);
	fclose(fi);
	DeleteStack(stack);
	return 0;
}


