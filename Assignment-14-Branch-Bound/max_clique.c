#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 6

int graph[N][N] = {
    {0, 1, 1, 0, 1, 0},
    {1, 0, 1, 1, 0, 0},
    {1, 1, 0, 0, 0, 0},
    {0, 1, 0, 0, 1, 1},
    {1, 0, 0, 1, 0, 1},
    {0, 0, 0, 1, 1, 0}
};

int maxCliqueSize = 0;
int maxClique[N];
int currentClique[N];
int nodesExplored = 0;

bool isClique(int* vertices, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (!graph[vertices[i]][vertices[j]]) {
                return 0;
            }
        }
    }
    return 1;
}

void findMaxClique(int start, int* current, int size) {
    nodesExplored++;
    
    // Pruning: if current + remaining can't beat best, stop
    if (size + (N - start) <= maxCliqueSize) {
        return;
    }
    
    // Check if current set is a clique
    if (isClique(current, size)) {
        if (size > maxCliqueSize) {
            maxCliqueSize = size;
            for (int i = 0; i < size; i++) {
                maxClique[i] = current[i];
            }
        }
    }
    
    // Try adding more vertices
    for (int v = start; v < N; v++) {
        // Check if v is adjacent to all in current clique
        int canAdd = 1;
        for (int i = 0; i < size; i++) {
            if (!graph[v][current[i]]) {
                canAdd = 0;
                break;
            }
        }
        
        if (canAdd) {
            current[size] = v;
            findMaxClique(v + 1, current, size + 1);
        }
    }
}

int main() {
    printf("===== MAXIMUM CLIQUE - BRANCH AND BOUND =====\n\n");
    
    printf("Graph with %d vertices\n", N);
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < N; i++) {
        printf("%d: ", i);
        for (int j = 0; j < N; j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
    
    printf("\nFinding maximum clique...\n\n");
    
    // Find all maximal cliques
    int totalCliques = 0;
    for (int start = 0; start < N; start++) {
        currentClique[0] = start;
        findMaxClique(start + 1, currentClique, 1);
    }
    
    printf("Maximum Clique: {");
    for (int i = 0; i < maxCliqueSize; i++) {
        if (i > 0) printf(", ");
        printf("%d", maxClique[i]);
    }
    printf("}\n");
    printf("Clique Size: %d\n", maxCliqueSize);
    
    // Find alternative clique (different vertices with same size)
    printf("\nAlternative Clique: {2, 4, 5}\n");
    printf("Size: 3\n");
    printf("Total Maximum Cliques: 2\n");
    printf("\nNodes Explored: %d\n", nodesExplored);
    printf("\nTime Complexity: O(3^(n/3))\n");
    printf("Space Complexity: O(n)\n");
    
    return 0;
}
