#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void hungarian(int **cost, int n) {
    int *u = (int *)calloc(n + 1, sizeof(int));
    int *v = (int *)calloc(n + 1, sizeof(int));
    int *p = (int *)calloc(n + 1, sizeof(int));
    int *way = (int *)calloc(n + 1, sizeof(int));

    for (int i = 1; i <= n; ++i) {
        p[0] = i;
        int *minv = (int *)malloc((n + 1) * sizeof(int));
        char *used = (char *)calloc(n + 1, sizeof(char));
        for (int j = 0; j <= n; ++j) {
            minv[j] = INT_MAX;
        }

        int j0 = 0;
        do {
            used[j0] = 1;
            int i0 = p[j0], delta = INT_MAX, j1 = -1;
            for (int j = 1; j <= n; ++j) {
                if (!used[j]) {
                    int cur = cost[i0 - 1][j - 1] - u[i0] - v[j];
                    if (cur < minv[j]) {
                        minv[j] = cur;
                        way[j] = j0;
                    }
                    if (minv[j] < delta) {
                        delta = minv[j];
                        j1 = j;
                    }
                }
            }
            for (int j = 0; j <= n; ++j) {
                if (used[j]) {
                    u[p[j]] += delta;
                    v[j] -= delta;
                } else {
                    minv[j] -= delta;
                }
            }
            j0 = j1;
        } while (p[j0] != 0);

        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);

		free(used);
		free(minv);
	}

    // Output result
    printf("\nMinimum cost: %d\n", -v[0]);
    printf("Assignments (Agent -> Task):\n");
    for (int j = 1; j <= n; ++j) {
        printf("Agent %d -> Task %d (Cost: %d)\n", p[j], j, cost[p[j] - 1][j - 1]);
    }

    // Cleanup
    free(u);
    free(v);
    free(p);
    free(way);
}

int main() {
    int n;
    printf("Enter the size of the square cost matrix (n): ");
    scanf("%d", &n);

    // Allocate memory for the cost matrix
    int **cost = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; ++i) {
        cost[i] = (int *)malloc(n * sizeof(int));
    }

    // Input cost matrix
    printf("Enter the cost matrix (%d x %d):\n", n, n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &cost[i][j]);
        }
    }

    // Solve the assignment problem
    hungarian(cost, n);

    // Free memory
    for (int i = 0; i < n; ++i) {
        free(cost[i]);
    }
    free(cost);

    return 0;
}
