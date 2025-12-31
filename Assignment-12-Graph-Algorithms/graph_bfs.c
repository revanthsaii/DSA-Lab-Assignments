#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define V 5
#define QUEUE_SIZE 100

int queue[QUEUE_SIZE];
int front = 0, rear = 0;
int visited[V] = {0};
int distance[V];

// Enqueue operation
void enqueue(int vertex) {
    queue[rear++] = vertex;
}

// Dequeue operation
int dequeue() {
    return queue[front++];
}

// BFS traversal
void bfs(int adj[V][V], int start) {
    // Mark start as visited and initialize distance
    visited[start] = 1;
    distance[start] = 0;
    enqueue(start);
    
    printf("Visit Order: ");
    while (front < rear) {
        int u = dequeue();
        printf("%d ", u);
        
        // Visit all adjacent vertices
        for (int v = 0; v < V; v++) {
            if (adj[u][v] && !visited[v]) {
                visited[v] = 1;
                distance[v] = distance[u] + 1;
                enqueue(v);
            }
        }
    }
}

int main() {
    // Adjacency matrix representation
    int adj[V][V] = {
        {0, 1, 1, 0, 0},  // 0: connected to 1, 2
        {1, 0, 0, 1, 0},  // 1: connected to 0, 3
        {1, 0, 0, 1, 1},  // 2: connected to 0, 3, 4
        {0, 1, 1, 0, 1},  // 3: connected to 1, 2, 4
        {0, 0, 1, 1, 0}   // 4: connected to 2, 3
    };
    
    printf("\n===== BREADTH-FIRST SEARCH (BFS) =====\n\n");
    
    printf("Adjacency Matrix:\n");
    printf("     0 1 2 3 4\n");
    for (int i = 0; i < V; i++) {
        printf("  %d [", i);
        for (int j = 0; j < V; j++) {
            printf(" %d", adj[i][j]);
        }
        printf(" ]\n");
    }
    
    printf("\nBFS from source 0:\n");
    bfs(adj, 0);
    printf("\n\nDistance from source 0:\n");
    for (int i = 0; i < V; i++) {
        printf(" %d: %d\n", i, distance[i]);
    }
    
    printf("\nTime Complexity: O(V + E)\n");
    printf("Space Complexity: O(V)\n");
    
    return 0;
}
