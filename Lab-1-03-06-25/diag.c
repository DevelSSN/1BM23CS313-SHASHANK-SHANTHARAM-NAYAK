#include <stdio.h>


int main()
{
    int a[5][5];
    int n;
    printf("Enter the size of the square matrix (n <= 5): ");
    scanf("%d", &n);


    printf("Enter the elements of the %d x %d matrix:\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i][i];
    }
    printf("Sum of the diagonal elements: %d\n", sum);
    
    return 0;
}

