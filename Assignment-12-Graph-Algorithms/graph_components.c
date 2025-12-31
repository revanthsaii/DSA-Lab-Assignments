#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define V 8

int visited[V] = {0};
int component[V];
int componentCount = 0;

// DFS to mark all vertices in a component
void dfs(int u, int adj[V][V], int compNum) {
    visited[u] = 1;
    component[u] = compNum;
    
    for (int v = 0; v < V; v++) {
        if (adj[u][v] && !visited[v]) {
            dfs(v, adj, compNum);
        }
    }
}

// Find all connected components
void findComponents(int adj[V][V]) {
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            dfs(i, adj, componentCount);
            componentCount++;
        }
    }
}

int main() {
    // Undirected graph with 3 components
    int adj[V][V] = {
        {0, 1, 1, 0, 0, 0, 0, 0},
        {1, 0, 1, 1, 0, 0, 0, 0},
        {1, 1, 0, 1, 1, 0, 0, 0},
        {0, 1, 1, 0, 1, 0, 0, 0},
        {0, 0, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 1},
        {0, 0, 0, 0, 0, 1, 0, 1},
        {0, 0, 0, 0, 0, 1, 1, 0}
    };
    
    printf("\n===== CONNECTED COMPONENTS =====\n\n");
    
    findComponents(adj);
    
    printf("Total Components: %d\n\n", componentCount);
    
    for (int c = 0; c < componentCount; c++) {
        printf("Component %d: [", c + 1);
        int first = 1;
        for (int i = 0; i < V; i++) {
            if (component[i] == c) {
                if (!first) printf(", ");
                printf("%d", i);
                first = 0;
            }
        }
        printf("]\n");
    }
    
    printf("\nTime Complexity: O(V + E)\n");
    printf("Space Complexity: O(V)\n");
    printf("Approach: DFS-based component detection\n");
    
    return 0;
}
