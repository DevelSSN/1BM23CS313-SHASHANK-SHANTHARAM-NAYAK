#include <stdio.h>
#include <stdlib.h>

#define MAX 10
#define INF 999

typedef struct {
    int u, v, weight;
} Edge;

int parent[MAX], rank[MAX];
Edge edges[MAX * MAX];
int n, m;

void initSet() {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int find(int i) {
    if (i != parent[i]) {
        parent[i] = find(parent[i]);
    }
    return parent[i];
}

void unionSet(int i, int j) {
    int root1 = find(i);
    int root2 = find(j);

    if (root1 != root2) {
        if (rank[root1] > rank[root2]) {
            parent[root2] = root1;
        } else if (rank[root1] < rank[root2]) {
            parent[root1] = root2;
        } else {
            parent[root2] = root1;
            rank[root1]++;
        }
    }
}

int compare(const void *a, const void *b) {
    return ((Edge *)a)->weight - ((Edge *)b)->weight;
}

void kruskal() {
    int mstWeight = 0;
    int edgeCount = 0;

    qsort(edges, m, sizeof(Edge), compare);

    for (int i = 0; i < m; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        
        if (find(u) != find(v)) {
            printf("Edge (%d, %d) with weight %d\n", u, v, edges[i].weight);
            unionSet(u, v);
            mstWeight += edges[i].weight;
            edgeCount++;

            if (edgeCount == n - 1) {
                break;
            }
        }
    }

    printf("\nTotal weight of MST: %d\n", mstWeight);
}

int main() {
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter number of edges: ");
    scanf("%d", &m);

    printf("Enter the edges (u, v, weight):\n");
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].weight);
    }

    initSet();
    kruskal();

    return 0;
}
