#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define N 4
#define INF 999

int n = N;
int cost[N][N] = {
    {10, 5, 16, 4},
    {2, 13, 1, 10},
    {14, 12, 19, 8},
    {14, 8, 5, 5}
};

int minCost = INF;
int assignment[N];
int bestAssignment[N];

void solve(int worker, int assignedJobs, int currentCost) {
    // Pruning: if current cost exceeds best found, stop
    if (currentCost >= minCost) {
        return;
    }
    
    // All workers assigned
    if (worker == n) {
        if (currentCost < minCost) {
            minCost = currentCost;
            for (int i = 0; i < n; i++) {
                bestAssignment[i] = assignment[i];
            }
        }
        return;
    }
    
    // Try assigning each job to current worker
    for (int job = 0; job < n; job++) {
        // Check if job is not assigned
        if (!(assignedJobs & (1 << job))) {
            assignment[worker] = job;
            
            // Recursively assign remaining workers
            solve(worker + 1, assignedJobs | (1 << job), 
                  currentCost + cost[worker][job]);
            
            assignment[worker] = -1;
        }
    }
}

int main() {
    printf("===== JOB ASSIGNMENT PROBLEM - BRANCH AND BOUND =====\n\n");
    
    printf("Workers: A, B, C, D\n");
    printf("Jobs: 1, 2, 3, 4\n");
    printf("Cost Matrix:\n");
    printf("    J1 J2 J3 J4\n");
    
    char workers[] = {'A', 'B', 'C', 'D'};
    for (int i = 0; i < n; i++) {
        printf("%c [ ", workers[i]);
        for (int j = 0; j < n; j++) {
            printf("%2d ", cost[i][j]);
        }
        printf("]\n");
    }
    
    // Initialize
    for (int i = 0; i < n; i++) {
        assignment[i] = -1;
        bestAssignment[i] = -1;
    }
    
    // Solve
    printf("\nOptimal Assignment:\n");
    solve(0, 0, 0);
    
    // Print result
    for (int i = 0; i < n; i++) {
        printf("Worker %c -> Job %d (cost %d)\n", workers[i], 
               bestAssignment[i] + 1, cost[i][bestAssignment[i]]);
    }
    
    printf("\nTotal Minimum Cost: %d\n", minCost);
    printf("Time Complexity: O(n!)\n");
    printf("Space Complexity: O(n)\n");
    
    return 0;
}
