#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
int function(int* arr, int n);

void main()
{
	int arr[25];
	int n;
	printf("Enter n \'n\' Array:");
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d",&arr[i]);
	printf("%d",function(arr, n));
}

int function(int* arr, int n)
{
	int sec=INT_MAX, first=INT_MAX;
	for(int i=0;i<n;i++)
	{
		if(arr[i]<first)
		{
			sec=first;
			first=arr[i];
		}
		else if(arr[i]<sec)
			sec=arr[i];
	}
	return sec;
}
