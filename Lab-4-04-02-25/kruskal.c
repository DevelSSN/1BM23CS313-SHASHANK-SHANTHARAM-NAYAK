#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
typedef struct edgelist edgelist;
struct edgelist{
	int s;
	int d;
	int w; //key
};

void swap(edgelist* a, edgelist* b)
{
	edgelist temp = *a;
	*a = *b;
	*b = temp;
}


int partition(edgelist* arr, int low, int high)
{
	int i=low-1, j=low;
	int x = arr[high].w;
	for(;j < high;j++)
	{
		if(arr[j].w<x)
		{
			i++;
			swap(&arr[j],&arr[i]);
		}
	}
	i++;
	swap(&arr[i],&arr[high]);
	return i;
}


void quicksort(edgelist* arr, int low, int high)
{
	if(low >= high)
		return;
	int mid = partition(arr, low, high);
	quicksort(arr, low, mid-1);
	quicksort(arr, mid+1, high);
}
int root(int* parent, int i)
{
	while(parent[i]!=i)
		i=parent[i];
	return i;
}
int kruskal(int n, int adj[n][n], int m, int sel[m][2])
{
	int l=10;
	edgelist* edges= (edgelist*) malloc(sizeof(edgelist)*l);
	int sum = 0;
	int parent[n];
	for(int i =0;i<n;i++)
		parent[i] = i;
	int k=-1;
	for(int i=0;i<n;i++)
	{
		for(int j=0; j<i;j++)
		{
			if(adj[i][j]>0)
			{
				k++;
				if(k>=l)
				{
					l+=10;
					edges = (edgelist*)realloc(edges, l);
				}
				edges[k].s=i;
				edges[k].d=j;
				edges[k].w=adj[i][j];
			}
		}
	}

	quicksort(edges, 0, k);

	k=0;
	for(int i=0;i<l;i++)
	{
		if(root(parent, edges[i].s) != root(parent, edges[i].d))
		{
			sel[k][0]=edges[i].s;
			sel[k][1]=edges[i].d;
			k++;
			sum+=edges[i].w;
			parent[edges[i].d] = edges[i].s;
		}
	}
	return sum;
}

	


void main()
{
	int n;
	int u,v,w;
	printf("Enter no. of vertices:");
	scanf("%d",&n);
	int adj[n][n];
	printf("Enter u,v,w(-1 to exit):");
	while(true)
	{
		scanf("%d%d%d",&u,&v,&w);
		if( (u!=-1||v!=-1) && u<n && v<n)
		{
			adj[u][v]=w;
			adj[v][u]=w;
		}
		else
		{
			printf("Exiting entries:");
			break;
		}
	}

	int sel[n][2];

	int sum = kruskal(n, adj, n, sel);
}

