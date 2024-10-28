#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
typedef struct node node;
struct node
{
	int value;
	struct node *next;
};

node* createNode(int x)
{
	node *n = (node*)malloc(sizeof(node));
	n->value=x;
	n->next=NULL;

	return n;
}

void inst_beg(node* head, int value)
{
	node *new = createNode(value);

	if(head->next == NULL)
		head->next = new;
	else
	{
		new->next = head->next;
		head->next = new;
	}
	printf("Inserted %d at begin\n",value);
}

void inst_end(node* head, int value)
{
	node *new = createNode(value);

	node *temp = head;

	while(temp->next!=NULL)
		temp = temp->next;
	
	temp->next = new;
	printf("Inserted %d at end\n",value);
}

void display(node* head)
{
	node *temp= head;
	if(head->next==NULL){
		printf("No element\n");
		return;
	}
	while(temp->next!=NULL)
	{
		temp = temp->next;
		printf("%d\t",temp->value);
	}
	printf("\n");
}

void main()
{
	node *head=NULL;
	head = (node *) malloc(sizeof(node));
	head->next = NULL;

	printf("1.Inst-beg\n2.Inst-end\n3.Display\n0.Exit");
	int choice;
	char c;
	do
	{
		printf("\nEnter choice:");
		scanf("%d",&choice);

		switch(choice)
		{
			case 1:	int x;
				printf("Enter node value:");
				scanf("%d",&x);
				inst_beg(head,x);
				break;
			case 2:	int y;
                                printf("Enter node value:");
                                scanf("%d",&y);
                                inst_end(head,y);
				break;
			case 3:	display(head);
				break;
			case 0:	break;
			default:printf("Invalid choice\n");
		}
		if((c=getchar())=='\n'||c==EOF){}
	}while(choice!=0);
	printf("\nExiting...\n");
}

