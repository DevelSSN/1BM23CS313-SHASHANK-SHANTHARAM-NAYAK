#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

int partition(int* arr, int low, int high)
{
	int i=low-1, j=low;
	int x = arr[high];
	for(;j < high;j++)
	{
		if(arr[j]<x)
		{
			i++;
			swap(&arr[j],&arr[i]);
		}
	}
	i++;
	swap(&arr[i],&arr[high]);
	return i;
}


void quicksort(int* arr, int low, int high)
{
	if(low >= high)
		return;
	int mid = partition(arr, low, high);
	quicksort(arr, low, mid-1);
	quicksort(arr, mid+1, high);
}

void main()
{
	int n;
	printf("Enter n:");
	scanf("%d",&n);
	printf("Enter array elements:");
	int arr[n];
	for(int i=0;i<n;i++)
		scanf("%d",&arr[i]);
	quicksort(arr, 0, n-1);
	printf("Sorted array:\n");
	for(int i=0;i<n;i++)
		printf("%d\t",arr[i]);
	printf("\n");
}
