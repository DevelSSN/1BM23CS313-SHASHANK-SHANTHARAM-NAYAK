#include <stdbool.h>
#include <stdio.h>
int top, size;

void init()
{
	printf("Enter the size of stack:");
	scanf("%d",&size);
	top=-1;
}

bool isEmpty()
{return top==-1;}

bool isFull()
{return top==size-1;}

void push(int s[], int x)
{
	if(!isFull())
	{
		++top;
		s[top]=x;
		printf("Pushed %d to stack\n",x);
		printf("%d",top);
	}
	else
	{
		printf("Overflow\n");
	}
}

int pop(int s[])
{
	if(isEmpty())
	{
		printf("Underflow\n");
		return 0;
	}
	else
	{
		int tmp=s[top];
		top--;
		return tmp;
	}
}

int Top(int s[])
{return isEmpty()?s[top]:0;}

void main()
{
	init();
	int s[size];
	char choice, c;
	do{
	printf("\n\nOperations:\n");
	printf("push(p)\nPop(P)\nTop(t)\nEmpty(e)\nFull(f)\n0 to exit\nEnter choice:");
	while ((c = getchar()) != '\n' && c != EOF) { }
	scanf("%c",&choice);
	switch(choice)
	{
		case 'p':int x;
			 printf("Enter element:");
			 scanf("%d",&x);
			 push(s,x);
			 break;
		case 'P':printf("Element %d popped\n",pop(s));
			 break;
		case 'e':if(isEmpty())
				printf("Empty Stack\n");
			 else
				printf("Not Empty\n");
			 break;
		case 't':printf("Top element:%d\n",Top(s));
			 break;
		case 'f':if(isFull())
				printf("Stack is full\n");
			 else
				printf("Stack is not full\n");
			 break;
		case '0': break;
	}
	}while(choice!='0');
	printf("\nExiting...\n");
}

