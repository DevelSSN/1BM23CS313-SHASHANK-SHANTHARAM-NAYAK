#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct node node;
struct node{
	int value;
	node* prev;node* next;
};

node* createNode(int x)
{
	node* n = (node*)malloc(sizeof(node));
	n->value=x;
	n->prev=NULL;
	n->next=NULL;
}

void instBeg(node** hptr, int x)
{
	node* n = createNode(x);
	if(*hptr == NULL)
	{
		*hptr=n; return;
	}
	n->next=*hptr;
	(*hptr)->prev=n;
	*hptr=n;
}

void instEnd(node** hptr, int x)
{
	if(*hptr==NULL){instBeg(hptr, x);return;}
	node* n = createNode(x);
	node* temp = *hptr;

	while(temp->next!=NULL)
	{temp=temp->next;}

	temp->next=n;
	n->prev=temp;
}

void instPos(node** hptr, int x, int pos)
{
	if(*hptr==NULL||pos==1){instBeg(hptr, x);return;}
	node* n = createNode(x);
	node* tmp=*hptr;

	for(int i=1;tmp!=NULL&&i<pos-1;i++)
	{tmp=tmp->next;}

	if(tmp==NULL){printf("OutOfBounds\n"); return;}
	if(tmp->next==NULL){instEnd(hptr, x);return;}
	n->next=tmp->next;
	n->prev=tmp;
	tmp->next->prev=n;
	tmp->next=n;
}

void display(node* head)
{
	node* temp=head;
	if(head==NULL){printf("Empty List\n");return;}
	while(temp!=NULL)
	{
		printf("%d\t",temp->value);
		temp=temp->next;
	}
	printf("\n");
}

void main()
{
	node* head = NULL;
	int choice;
	printf("1.Inst-beg\n2.Inst-End\n3.Inst-Pos\n4.Display\n0.Exit\n");
	do{
		printf("Enter choice:");
		scanf("%d",&choice);
		int x;
		switch(choice)
		{
			case 1: printf("Enter value:");
				scanf("%d",&x);
				instBeg(&head, x);
				break;
			case 2: printf("Enter value:");
				scanf("%d",&x);
				instEnd(&head, x);
				break;
			case 3: int pos;
				printf("Enter value, pos:");
				scanf("%d%d",&x,&pos);
				instPos(&head, x, pos);
				break;
			case 4: display(head);
				break;
			case 0: break;
			default:printf("Invalid input\n");
		}
	}while(choice!=0);
	printf("Exiting...");
}

