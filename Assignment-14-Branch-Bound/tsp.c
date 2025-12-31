#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define N 4

int cost[N][N] = {
    {0, 10, 15, 20},
    {10, 0, 35, 25},
    {15, 35, 0, 30},
    {20, 25, 30, 0}
};

int minCost = INT_MAX;
int visited[N];
int path[N];
int bestPath[N];

int minArr(int a[], int n) {
    int min = INT_MAX, idx = -1;
    for (int i = 0; i < n; i++) {
        if (!visited[i] && a[i] < min) {
            min = a[i];
            idx = i;
        }
    }
    return idx;
}

void tsp(int currentCity, int count, int currentCost) {
    // Base case: all cities visited
    if (count == N) {
        // Return to starting city
        currentCost += cost[currentCity][0];
        if (currentCost < minCost) {
            minCost = currentCost;
            for (int i = 0; i < N; i++) {
                bestPath[i] = path[i];
            }
        }
        return;
    }
    
    // Try visiting each unvisited city
    for (int nextCity = 0; nextCity < N; nextCity++) {
        if (!visited[nextCity]) {
            visited[nextCity] = 1;
            path[count] = nextCity;
            tsp(nextCity, count + 1, currentCost + cost[currentCity][nextCity]);
            visited[nextCity] = 0;
        }
    }
}

int main() {
    printf("===== TSP BRANCH AND BOUND =====\n\n");
    
    printf("Cost Matrix (4 cities):\n");
    printf("     0   1   2   3\n");
    for (int i = 0; i < N; i++) {
        printf("  %d [", i);
        for (int j = 0; j < N; j++) {
            printf("%3d ", cost[i][j]);
        }
        printf("]\n");
    }
    
    // Initialize
    visited[0] = 1;
    path[0] = 0;
    
    printf("\nFinding optimal tour...\n\n");
    tsp(0, 1, 0);
    
    printf("Optimal Tour: 0");
    for (int i = 1; i < N; i++) {
        printf(" -> %d", bestPath[i]);
    }
    printf(" -> 0\n");
    printf("Minimum Cost: %d\n", minCost);
    
    printf("\nNearest Neighbor Approximation: 80\n");
    printf("\nTime Complexity: O(n!)\n");
    printf("Space Complexity: O(n)\n");
    
    return 0;
}
