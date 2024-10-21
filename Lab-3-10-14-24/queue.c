#include <stdio.h>
#include <stdbool.h>
#define size 5
int front=-1, rear=-1;
bool isEmpty(){return (front>rear)||(front==-1&&rear==-1);}
bool isFull(){return rear==size-1;}

void enqueue(int* q, int x)
{
	if(isEmpty())
	{
		front=0; rear=0;
		q[rear]=x;
	}
	else if(!isFull())
	{
		q[++rear]=x;
		printf("Enqueued %d\n",q[rear]);
	}
	else
	{
		printf("Overflow\n");
	}
}

void dequeue(int* q)
{
	if(!isEmpty())
	{
		printf("Dequeued %d\n", q[front++]);
	}
	else
	{
		printf("Underflow\n");
		front=-1;rear=-1;
	}
}
void display(int* q)
{
	printf("Queue as:");
	for(int i=0;i<=rear;i++)
		printf("%d\t",q[i]);
	printf("\n");
}

void main()
{
	int q[size];
	char choice, c;
	printf("\n\nOperations:\n");
	printf("Enqueue(p)\t\tDequeue(P)\t\tDisplay(d)\n0 to exit\n");
	do{
		// TODO input here
		printf("\nEnter choice:");
		scanf("%c",&choice);
	switch(choice)
	{
		case 'p':int x;
			 printf("Enter element:");
			 scanf("%d",&x);
			 enqueue(q,x);
			 break;
		case 'P':dequeue(q);
			 break;
		case 'e':if(isEmpty())
				printf("Empty Stack\n");
			 else
				printf("Not Empty\n");
			 break;
		case 'f':if(isFull())
				printf("Stack is full\n");
			 else
				printf("Stack is not full\n");
			 break;
		case 'd':display(q);
			 break;
		case '0': break;
		default: break;
	}
	// Flush stdin
	if((c=getchar())=='\n'||c==EOF){}
	}while(choice!='0');
	printf("\nExiting...\n");
}

