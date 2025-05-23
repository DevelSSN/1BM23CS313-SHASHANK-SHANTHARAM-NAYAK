#include <stdio.h>
#include <stdlib.h>

int left(int i){
	return 2*i;
}

int right(int i){
	return 2*i+1;
}

void maxHeapify(int* arr, int i, int size)
{
	int largest;
	int l = left(i);
	int r = right(i);
	if(l<size && arr[l]>arr[i])
		largest = l;
	else
		largest = i;
	if(r<size && arr[r]>arr[largest])
		largest = r;

	if(largest != i)
	{
		int temp = arr[i];
		arr[i] = arr[largest];
		arr[largest] = temp;
		maxHeapify(arr, largest, size);
	}
}

void build(int* arr, int n)
{
	for(int i=n/2;i>=0;i--)
		maxHeapify(arr, i, n);
}

void heapsort(int* arr, int n)
{
	build(arr, n);
	int size = n;
	for(int i=n-1;i>=1;i--)
	{
		int temp = arr[0];
		arr[0] = arr[i];
		arr[i] = temp;
		size--;
		maxHeapify(arr, 0, size);
	}
}

int main()
{
	int n;
	printf("Enter n:");
	scanf("%d",&n);
	int* a = (int*)malloc(n*sizeof(int));
	printf("Enter elements:");
	for(int i=0;i<n;i++)
		scanf("%d",&a[i]);
	heapsort(a, n);
	printf("Heap:\n");
	for(int i=0;i<n;i++)
		printf("%d ",a[i]);
	printf("\n");
}
