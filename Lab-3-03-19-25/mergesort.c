#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void display(int* arr, int n) {
    for(int i = 0; i < n; i++) {
        printf("%d\t", arr[i]);
    }
    printf("\n");
}

void merge(int* arr, int low, int mid, int high) {
    int left_size = mid - low + 1;
    int right_size = high - mid;

    int left[left_size];
    int right[right_size];

    for (int i = 0; i < left_size; i++) {
        left[i] = arr[low + i];
    }
    for (int i = 0; i < right_size; i++) {
        right[i] = arr[mid + 1 + i];
    }

    int i = 0, j = 0, k = low;
    while (i < left_size && j < right_size) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < left_size) {
        arr[k] = left[i];
        i++;
        k++;
    }

    while (j < right_size) {
        arr[k] = right[j];
        j++;
        k++;
    }

}

void mergesort(int* arr, int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;

        mergesort(arr, low, mid);
        mergesort(arr, mid + 1, high);

        merge(arr, low, mid, high);
    }
}

void main()
{
	int a[15000],n,i,j,ch,temp;
	clock_t start,end;
	while(1)
	{
		printf("\n1:For manual entry of N value and array elements");
		printf("\n2:To display time taken for sorting number of elements N in the range 500 to 14500");
		printf("\n3:To exit");
		printf("\nEnter your choice:");
		scanf("%d", &ch);
		switch(ch)
		{
			case 1: printf("\nEnter the number of elements: ");
				scanf("%d",&n);
				printf("\nEnter array elements: ");
				for(i=0;i<n;i++)
				{
					scanf("%d",&a[i]);
				}
				start=clock();
				mergesort(a, 0, n-1);
				end=clock();
				printf("\nSorted array is: ");
				for(i=0;i<n;i++)
					printf("%d\t",a[i]);
				printf("\n%d,%f",n, (((double)(end-start))/CLOCKS_PER_SEC));
				break;
			case 2: n=500;
				while(n<=14500) 
				{
					for(i=0;i<n;i++)
					{
						a[i]=n-i;
					}
					start=clock();
					mergesort(a, 0, n-1);
					//Dummy loop to create delay
					for(j=0;j<500000;j++){ temp=38/600;}
					end=clock();
					printf("\n%d,%f",n, (((double)(end-start))/CLOCKS_PER_SEC));
					n=n+1000;
				}
				break;
			case 3: exit(0);
		}
		getchar();
	}
}
