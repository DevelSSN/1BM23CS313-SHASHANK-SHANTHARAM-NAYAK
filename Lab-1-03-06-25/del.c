#include <stdio.h>
#include <stdbool.h>
int function(int* arr, int n);

void main()
{
	int a[25];
	int n;
	printf("Enter n \'n\' Array:");
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d",&a[i]);
	printf("Deleted. n=%d",function(a, n));
}

int function(int* arr, int n)
{
	int pos;
	printf("Enter pos:");
	scanf("%d",&pos);
	for(int i = pos; i<n-1;i++)
		arr[i]=arr[i+1];
	n--;
}
