#include <stdio.h>
#include <stdbool.h>
#define size 5
int front=-1, rear=-1;
bool isEmpty(){return front==-1&rear==front;}
bool isFull(){return (rear+1)%size==front;}

void enqueue(int q[], int x)
{
	if(isEmpty())
	{
		front=0; rear=0;
		q[rear]=x;
		printf("Enqueued %d\n",q[rear]);
	}
	else if(!isFull())
	{
		rear=(rear+1)%size;
		q[rear]=x;
		printf("Enqueued %d\n",q[rear]);
	}
	else
	{
		printf("Overflow\n");
	}
}

int dequeue(int q[])
{
	if(isEmpty())
	{
		printf("Underflow\n");
	}
	else if(front==rear)
	{
		int temp=q[front];
		front=-1;rear=-1;
		return temp;
	}
	else
	{
		int temp=q[front];
		front=(front+1)%size;
		return temp;
	}
}
void display(int* q)
{
	printf("Queue is:");
	for(int i=front;i!=rear;i=(i+1)%size)
		printf("%d\t",q[i]);
	printf("%d\n",q[rear]);
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
		case 'P':if(isEmpty())
					printf("Underflow\n");
				else
					printf("Dequeued %d\n",dequeue(q));
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

