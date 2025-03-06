#include <stdio.h>
#include <stdbool.h>

void main()
{
	int a[5][5];
	int n;
	printf("Enter n \'n\' Array:");
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			scanf("%d",&a[i][j]);
	printf("Row-wise:");
	for(int i=0;i<n;i++)
	{
		int sum=0;
		for(int j=0;j<n;j++)
			sum+=a[i][j];
		printf("r%d:%d\t",i+1,sum);
	}
	printf("Col-wise:");
	for(int i=0;i<n;i++)
	{
		int sum=0;
		for(int j=0;j<n;j++)
			sum+=a[j][i];
		printf("c%d:%d\t",i+1,sum);
	}
}

