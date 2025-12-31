#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define V 6

int visited[V] = {0};
int stack[V];
int top = -1;

// DFS-based topological sort helper
void dfs(int u, int adj[V][V]) {
    visited[u] = 1;
    
    for (int v = 0; v < V; v++) {
        if (adj[u][v] && !visited[v]) {
            dfs(v, adj);
        }
    }
    
    stack[++top] = u;
}

// Topological sort using DFS
void topoSort(int adj[V][V]) {
    // Visit all unvisited vertices
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            dfs(i, adj);
        }
    }
    
    printf("Topological Order: ");
    while (top >= 0) {
        printf("%d ", stack[top--]);
    }
}

int main() {
    // Directed Acyclic Graph (DAG)
    // Edges: 5->2, 5->0, 4->0, 4->1, 2->3, 1->3
    int adj[V][V] = {
        {0, 0, 0, 0, 0, 0},  // 0
        {0, 0, 0, 1, 0, 0},  // 1 -> 3
        {0, 0, 0, 1, 0, 0},  // 2 -> 3
        {0, 0, 0, 0, 0, 0},  // 3
        {1, 1, 0, 0, 0, 0},  // 4 -> 0, 1
        {1, 0, 1, 0, 0, 0}   // 5 -> 0, 2
    };
    
    printf("\n===== TOPOLOGICAL SORT (DAG) =====\n\n");
    
    printf("Directed Acyclic Graph (DAG):\n");
    printf("Edges: 5->2, 5->0, 4->0, 4->1, 2->3, 1->3\n\n");
    
    topoSort(adj);
    printf("\n\n");
    
    printf("Time Complexity: O(V + E)\n");
    printf("Space Complexity: O(V)\n");
    printf("Approach: DFS-based, Stack-based ordering\n");
    
    return 0;
}
