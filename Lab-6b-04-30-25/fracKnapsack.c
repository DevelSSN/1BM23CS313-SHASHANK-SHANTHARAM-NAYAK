#include <stdio.h>
#include <stdlib.h>

typedef struct obj {
    int v;
    int w;
} obj;

int compare(const void *a, const void *b) {
    obj *objA = (obj *)a;
    obj *objB = (obj *)b;
    float ratioA = (float)objA->v / objA->w;
    float ratioB = (float)objB->v / objB->w;
    if (ratioA > ratioB) {
        return -1;
    } else if (ratioA < ratioB) {
        return 1;
    } else {
        return 0;
    }
}

void fracKnap(obj *arr, int n, int max) {
    qsort(arr, n, sizeof(obj), compare);
    float *qty = (float *)malloc(n * sizeof(float));
    for (int i = 0; i < n; i++) {
        qty[i] = 0.0;
    }
    
    int i = 0;
    for (; i < n; i++) {
        if (arr[i].w <= max) {
            qty[i] = 1.0;
            max -= arr[i].w;
        } else {
            break;
        }
    }
    
    if (i < n) {
        qty[i] = (float)max / arr[i].w;
        max = 0;
    }
    
    float val = 0;
    for (int i = 0; i < n; i++) {
        val += qty[i] * arr[i].v;
        printf("Quantity of item %d: %f\n",arr[i].v, qty[i]);
    }

    printf("\nTotal value of knapsack: %f\n", val);
    free(qty);
}

int main() {
    int n;
    printf("Enter the number of items: ");
    scanf("%d", &n);
    
    obj *arr = (obj *)malloc(n * sizeof(obj));
    
    printf("Enter value and weight pairs:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &arr[i].v, &arr[i].w);
    }

    int max;
    printf("Enter the maximum weight of the knapsack: ");
    scanf("%d", &max);

    fracKnap(arr, n, max);
    free(arr);

    return 0;
}
