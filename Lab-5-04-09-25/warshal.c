#include <stdio.h>
#include <stdlib.h>

#define MAX 10
int adj[MAX][MAX], n, p[MAX][MAX];

void init()
{
	printf("Enter n:");
	scanf("%d",&n);
	printf("Enter Adjacency Matrix:\n");
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			scanf("%d",&adj[i][j]);
			if(adj[i][j]==1){
				p[i][j]=1;
			}
			else
			{
				p[i][j]=0;
			}
		}
	}
}

void warshal()
{
	for(int k=0;k<n;k++)
	{
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				if(p[i][k]==1&&p[k][j]==1)
					p[i][j]=1;
			}
		}
	}
}

void print()
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			printf("%d\t",p[i][j]);
		}
		printf("\n");
	}
}

void main()
{
	init();
	warshal();
	print();
}
