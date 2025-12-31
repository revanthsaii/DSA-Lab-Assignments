#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define V 5  // Number of vertices
#define INT_MAX 999999

// Function to find the vertex with minimum distance
int minDistance(int dist[], bool visited[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (visited[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}

// Function to print the solution
void printSolution(int dist[], int parent[]) {
    printf("Vertex\tDistance from Source\tPath\n");
    for (int i = 0; i < V; i++) {
        printf("%d\t%d\t\t\t", i, dist[i]);
        // Print path from source to i
        printf("0");
        int j = i;
        while (parent[j] != -1) {
            printf(" <- %d", parent[j]);
            j = parent[j];
        }
        printf("\n");
    }
}

// Dijkstra's Algorithm
void dijkstra(int graph[V][V], int src) {
    int dist[V];
    int parent[V];
    bool visited[V];
    
    // Initialize
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
        parent[i] = -1;
    }
    
    dist[src] = 0;
    
    // Compute shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited);
        visited[u] = true;
        
        // Update dist values of adjacent vertices
        for (int v = 0; v < V; v++)
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX 
                && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
    }
    
    printSolution(dist, parent);
}

int main() {
    // Graph as adjacency matrix
    // 0: {1:4, 2:2}
    // 1: {0:4, 3:5}
    // 2: {0:2, 3:8, 4:10}
    // 3: {1:5, 2:8, 4:2}
    // 4: {2:10, 3:2}
    
    int graph[V][V] = {
        {0, 4, 2, 0, 0},
        {4, 0, 1, 5, 0},
        {2, 1, 0, 8, 10},
        {0, 5, 8, 0, 2},
        {0, 0, 10, 2, 0}
    };
    
    printf("===== DIJKSTRA'S SHORTEST PATH ALGORITHM =====\n\n");
    dijkstra(graph, 0);
    
    return 0;
}
