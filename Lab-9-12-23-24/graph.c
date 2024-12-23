#include <stdio.h>
#include <stdbool.h>

#define MAX 10

// Function to enqueue an element into the queue
void enqueue(int* q, int* rear, int x) {
    q[++(*rear)] = x;
}

// Function to dequeue an element from the queue
int dequeue(int* q, int* front, int* rear) {
    if (*front > *rear) return -1; // Queue is empty
    return q[(*front)++];
}

// Function to perform BFS
void bfs(int adj[][MAX], int* q, int* front, int* rear, bool* visited, int node) {
    enqueue(q, rear, node); 
    visited[node] = true;
    *front = 0; // Set front to 0 after the first enqueue

    while (*front <= *rear) {
        int currentNode = dequeue(q, front, rear);
        
        if (currentNode == -1) {
            break;
        }

        printf("%d\t", currentNode); // Display the visited node

        // Check all adjacent nodes
        for (int i = 0; i < MAX; i++) {
            if (adj[currentNode][i] == 1 && !visited[i]) {
                visited[i] = true;
                enqueue(q, rear, i); // Enqueue the unvisited node
            }
        }
    }
    printf("\n");
}

// Function to perform DFS
void dfs(int adj[][MAX], bool* visited, int node) {
    visited[node] = true;
    printf("%d\t", node); // Display the visited node

    // Visit all adjacent unvisited nodes recursively
    for (int i = 0; i < MAX; i++) {
        if (adj[node][i] == 1 && !visited[i]) {
            dfs(adj, visited, i);
        }
    }
}

int main() {
    int adj[MAX][MAX] = {0}; // Adjacency matrix
    bool visited[MAX] = {false}; // Visited array
    int q[MAX]; // Queue for BFS
    int front = -1, rear = -1; // Queue pointers
    int x, y;

    // Input the graph as an undirected graph
    do {
        printf("Enter edge (x y): ");
        scanf("%d%d", &x, &y);
        if (x == y) {
            break;
        }
        adj[x][y] = 1;
        adj[y][x] = 1; // Since it's an undirected graph
    } while (x != y);

    printf("Enter starting node: ");
    scanf("%d", &x);

    // Perform BFS
    printf("BFS traversal: ");
    bfs(adj, q, &front, &rear, visited, x);

    // Reset visited array for DFS
    for (int i = 0; i < MAX; i++) {
        visited[i] = false;
    }

    // Perform DFS
    printf("DFS traversal: ");
    dfs(adj, visited, x);
    printf("\n");

    return 0;
}
