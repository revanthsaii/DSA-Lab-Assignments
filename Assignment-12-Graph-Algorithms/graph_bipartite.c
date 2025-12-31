#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define V 4
#define INF INT_MAX

int color[V];
int queue[V];
int front = 0, rear = 0;

// Check if graph is bipartite using BFS 2-coloring
int isBipartite(int adj[V][V]) {
    // Color all vertices with -1 (uncolored)
    for (int i = 0; i < V; i++) {
        color[i] = -1;
    }
    
    // Assign colors to vertices
    for (int i = 0; i < V; i++) {
        if (color[i] == -1) {
            color[i] = 0;  // Color with 0
            queue[rear++] = i;
            
            while (front < rear) {
                int u = queue[front++];
                
                for (int v = 0; v < V; v++) {
                    if (adj[u][v]) {
                        if (color[v] == -1) {
                            // Assign opposite color
                            color[v] = 1 - color[u];
                            queue[rear++] = v;
                        } else if (color[v] == color[u]) {
                            // Same color adjacent vertices
                            return 0;  // Not bipartite
                        }
                    }
                }
            }
        }
    }
    return 1;  // Bipartite
}

int main() {
    // Bipartite graph
    // Set A: {0, 2}, Set B: {1, 3}
    int adj[V][V] = {
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0}
    };
    
    printf("\n===== BIPARTITE CHECK =====\n\n");
    
    printf("Graph:\n");
    printf("Set A: {0, 2}\n");
    printf("Set B: {1, 3}\n\n");
    
    if (isBipartite(adj)) {
        printf("Is Bipartite: Yes\n\n");
        printf("Coloring:\n");
        for (int i = 0; i < V; i++) {
            printf("Vertex %d -> %s\n", i, color[i] == 0 ? "Red" : "Blue");
        }
    } else {
        printf("Is Bipartite: No\n");
    }
    
    printf("\nTime Complexity: O(V + E)\n");
    printf("Space Complexity: O(V)\n");
    printf("Approach: BFS-based 2-coloring\n");
    
    return 0;
}
