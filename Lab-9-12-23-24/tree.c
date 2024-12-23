#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node node;
struct node
{
	int value;
	node* left;
	node* right;
};

node* createNode(int x)
{
	node* n = (node*)malloc(sizeof(node));
	n->value=x;
	n->left=NULL;
	n->right=NULL;
	return n;
}

void insert(node** rptr, int x)
{
	if(*rptr==NULL)
	{
		node* n = createNode(x);
		*rptr=n;
		return;
	}
	if(x<(*rptr)->value)
	{insert(&((*rptr)->left), x);}
	else
	{insert(&((*rptr)->right), x);}
}

void preorder(node* root)
{
	if(root==NULL){return;}
	printf("%d\t", root->value);
	preorder(root->left);
	preorder(root->right);
}

void inorder(node* root)
{
	if(root==NULL){return;}
	inorder(root->left);
	printf("%d\t", root->value);
	inorder(root->right);
}

void postorder(node* root)
{
	if(root==NULL){return;}
	postorder(root->left);
	postorder(root->right);
	printf("%d\t", root->value);
}

void main()
{
	node* root = NULL;
	int x=0;
	while(x!=-1)
	{
		printf("Enter node:");
		scanf("%d",&x);
		if(x!=-1){insert(&root, x);}
	}
	printf("Preorder:");
	preorder(root);
	printf("\n");
	printf("Inorder:");
	inorder(root);
	printf("\n");
	printf("Postorder:");
	postorder(root);
	printf("\n");
}
