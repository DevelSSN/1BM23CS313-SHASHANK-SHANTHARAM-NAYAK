#include <stdio.h>
#include <stdbool.h>
int function(int* arr, int n);

void main()
{
	int a[5];
	int n;
	printf("Enter n \'n\' Array:");
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d",&a[i]);
	function(a, n);
}

int function(int* arr, int n)
{
	for(int i=0;i<n;i++)
	{
		for(int j=i;j<n;j++)
		{
			if( i!=j &&arr[i]==arr[j])
				printf("Duplicate pair(%d,%d)\n",i,j);
		}
	}
}
