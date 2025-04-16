#include <stdio.h>
#include <stdlib.h>

#define MAX 10

void floyd(int n, int edge[n][n])
{
	int p[n][n];
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			p[i][j]=edge[i][j];
		}
	}
	for(int k=0;k<n;k++)
	{
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				if(p[i][j]>p[i][k]+p[k][j])
					p[i][j]=p[i][k]+p[k][j];
			}
		}
	}
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
	int n;
	printf("Enter n:");
	scanf("%d",&n);
	int edge[n][n];
	printf("Enter Adjacency Matrix:\n");
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			scanf("%d",&edge[i][j]);
		}
	}
	floyd(n, edge);
}
