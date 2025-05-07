#include <stdio.h>
#include <stdlib.h>

typedef struct obj {
    int v;  // value
    int w;  // weight
} obj;

int knapsackTopDown(obj* arr, int n, int W, int** memo) {
    if (n == 0 || W == 0) {
        return 0;
    }

    if (memo[n][W] != -1) {
        return memo[n][W];
    }

    if (arr[n - 1].w > W) {
        // Item can't be included in the knapsack
        memo[n][W] = knapsackTopDown(arr, n - 1, W, memo);
    } else {
        // Maximum of including or excluding the current item
        int includeItem = arr[n - 1].v + knapsackTopDown(arr, n - 1, W - arr[n - 1].w, memo);
        int excludeItem = knapsackTopDown(arr, n - 1, W, memo);
        memo[n][W] = (includeItem > excludeItem) ? includeItem : excludeItem;
    }

    return memo[n][W];
}

int main() {
    int n;
    printf("Enter the number of items: ");
    scanf("%d", &n);

    obj* arr = (obj*)malloc(n * sizeof(obj));

    printf("Enter value and weight pairs:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &arr[i].v, &arr[i].w);
    }

    int W;
    printf("Enter the maximum weight of the knapsack: ");
    scanf("%d", &W);

    // Create a memoization table initialized with -1
    int** memo = (int**)malloc((n + 1) * sizeof(int*));
    for (int i = 0; i <= n; i++) {
        memo[i] = (int*)malloc((W + 1) * sizeof(int));
        for (int j = 0; j <= W; j++) {
            memo[i][j] = -1;  // Initialize to -1 (indicating uncomputed)
        }
    }

    int max_value = knapsackTopDown(arr, n, W, memo);
    printf("\nMaximum value of knapsack: %d\n", max_value);

    // Free dynamically allocated memory
    for (int i = 0; i <= n; i++) {
        free(memo[i]);
    }
    free(memo);
    free(arr);

    return 0;
}
