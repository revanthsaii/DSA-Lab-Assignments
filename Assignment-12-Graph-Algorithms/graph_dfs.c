#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define V 5

int visited[V] = {0};

// Depth First Search using recursion
void dfs(int adj[V][V], int v) {
    // Mark current vertex as visited
    visited[v] = 1;
    printf("%d ", v);
    
    // Recur for all adjacent vertices
    for (int i = 0; i < V; i++) {
        if (adj[v][i] && !visited[i]) {
            dfs(adj, i);
        }
    }
}

int main() {
    // Adjacency matrix representation of graph
    // Graph with 5 vertices (0, 1, 2, 3, 4)
    int adj[V][V] = {
        {0, 1, 1, 0, 0},  // Vertex 0: connected to 1, 2
        {1, 0, 1, 1, 0},  // Vertex 1: connected to 0, 2, 3
        {1, 1, 0, 1, 1},  // Vertex 2: connected to 0, 1, 3, 4
        {0, 1, 1, 0, 1},  // Vertex 3: connected to 1, 2, 4
        {0, 0, 1, 1, 0}   // Vertex 4: connected to 2, 3
    };
    
    printf("\n===== GRAPH DFS (DEPTH FIRST SEARCH) =====\n\n");
    
    printf("Adjacency Matrix:\n");
    printf("     0 1 2 3 4\n");
    for (int i = 0; i < V; i++) {
        printf("  %d [", i);
        for (int j = 0; j < V; j++) {
            printf(" %d", adj[i][j]);
        }
        printf(" ]\n");
    }
    
    printf("\nDFS Traversal starting from vertex 0:\n");
    printf("Order: ");
    dfs(adj, 0);
    printf("\n\n");
    
    printf("Time Complexity: O(V + E) where V=vertices, E=edges\n");
    printf("Space Complexity: O(V) for visited array + recursion stack\n");
    
    return 0;
}
