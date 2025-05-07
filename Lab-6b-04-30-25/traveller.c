#include <stdio.h>
#include <limits.h>

#define MAX_CITIES 10  // Maximum number of cities (can be adjusted)
#define INF INT_MAX    // A large value representing infinity

int dist[MAX_CITIES][MAX_CITIES];  // Distance matrix
int n;  // Number of cities

// Function to calculate the total distance of a given path
int calculateCost(int path[]) {
    int totalCost = 0;
    for (int i = 0; i < n - 1; i++) {
        totalCost += dist[path[i]][path[i + 1]];  // Add distance between consecutive cities
    }
    totalCost += dist[path[n - 1]][path[0]];  // Add the distance to return to the starting city
    return totalCost;
}

// Function to generate all permutations of cities and calculate the minimum cost
void permute(int path[], int left, int right, int* minCost) {
    if (left == right) {
        // If the permutation is complete, calculate the cost
        int cost = calculateCost(path);
        if (cost < *minCost) {
            *minCost = cost;  // Update the minimum cost if the current path is better
        }
    } else {
        for (int i = left; i <= right; i++) {
            // Swap to generate the next permutation
            int temp = path[left];
            path[left] = path[i];
            path[i] = temp;
            
            // Recurse to generate the next part of the permutation
            permute(path, left + 1, right, minCost);
            
            // Backtrack to the previous state
            temp = path[left];
            path[left] = path[i];
            path[i] = temp;
        }
    }
}

int main() {
    printf("Enter the number of cities (n): ");
    scanf("%d", &n);

    printf("Enter the distance matrix (dist[i][j]):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &dist[i][j]);
        }
    }

    int path[MAX_CITIES];  // Array to store a permutation of cities
    for (int i = 0; i < n; i++) {
        path[i] = i;  // Initialize the path array with city indices
    }

    int minCost = INF;  // Start with a large value as the minimum cost

    permute(path, 0, n - 1, &minCost);  // Generate all permutations and calculate the minimum cost

    printf("The minimum cost of the TSP tour is: %d\n", minCost);

    return 0;
}
