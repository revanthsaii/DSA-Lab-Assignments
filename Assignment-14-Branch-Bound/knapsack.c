#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Node structure for priority queue
typedef struct {
    int level;
    int profit;
    int weight;
    float bound;
    int* include;
} Node;

int n, capacity;
int* weight;
int* value;
int maxProfit = 0;
int* bestSolution;
int nodesExplored = 0;
int nodesPruned = 0;

// Calculate upper bound using fractional knapsack
float calculateBound(Node* node) {
    if (node->weight >= capacity) return 0;
    
    float bound = node->profit;
    int remainingCapacity = capacity - node->weight;
    
    // Sort items by value/weight ratio for remaining items
    int items[n];
    for (int i = 0; i < n; i++) items[i] = i;
    
    for (int i = node->level; i < n; i++) {
        if (weight[i] <= remainingCapacity) {
            bound += value[i];
            remainingCapacity -= weight[i];
        } else {
            // Take fraction of next item
            bound += (float)value[i] * remainingCapacity / weight[i];
            break;
        }
    }
    
    return bound;
}

void branchAndBound(int level, int profit, int currentWeight, int* include) {
    nodesExplored++;
    
    // Base case: all items considered
    if (level == n) {
        if (profit > maxProfit) {
            maxProfit = profit;
            memcpy(bestSolution, include, n * sizeof(int));
        }
        return;
    }
    
    // Include current item if possible
    if (currentWeight + weight[level] <= capacity) {
        include[level] = 1;
        branchAndBound(level + 1, profit + value[level], 
                      currentWeight + weight[level], include);
        include[level] = 0;
    }
    
    // Exclude current item
    int* newInclude = (int*)malloc(n * sizeof(int));
    memcpy(newInclude, include, n * sizeof(int));
    newInclude[level] = 0;
    
    // Calculate upper bound for this branch
    Node node;
    node.level = level + 1;
    node.profit = profit;
    node.weight = currentWeight;
    float bound = calculateBound(&node);
    
    // Prune if bound is worse than current best
    if (bound > maxProfit) {
        branchAndBound(level + 1, profit, currentWeight, newInclude);
    } else {
        nodesPruned++;
    }
    
    free(newInclude);
}

int main() {
    printf("===== 0/1 KNAPSACK - BRANCH AND BOUND =====\n\n");
    
    // Test case
    n = 5;
    capacity = 15;
    
    weight = (int*)malloc(n * sizeof(int));
    value = (int*)malloc(n * sizeof(int));
    bestSolution = (int*)malloc(n * sizeof(int));
    int* currentInclude = (int*)malloc(n * sizeof(int));
    
    // Initialize
    int w[] = {2, 3, 5, 7, 8};
    int v[] = {10, 20, 30, 40, 50};
    
    for (int i = 0; i < n; i++) {
        weight[i] = w[i];
        value[i] = v[i];
        currentInclude[i] = 0;
        bestSolution[i] = 0;
    }
    
    printf("Capacity: %d\n", capacity);
    printf("Items:\n");
    for (int i = 0; i < n; i++) {
        printf(" Item %d: weight=%d, value=%d\n", i + 1, weight[i], value[i]);
    }
    printf("\nOptimal Solution:\n");
    
    branchAndBound(0, 0, 0, currentInclude);
    
    printf("Items Selected: ");
    int totalWeight = 0, totalValue = 0;
    for (int i = 0; i < n; i++) {
        if (bestSolution[i]) {
            printf("%d, ", i + 1);
            totalWeight += weight[i];
            totalValue += value[i];
        }
    }
    printf("\nTotal Weight: %d\n", totalWeight);
    printf("Total Value: %d\n", totalValue);
    printf("Nodes Explored: %d\n", nodesExplored);
    printf("Nodes Pruned: %d\n", nodesPruned);
    printf("\nTime Complexity: O(2^n)\n");
    printf("Space Complexity: O(n)\n");
    
    free(weight);
    free(value);
    free(bestSolution);
    free(currentInclude);
    
    return 0;
}
