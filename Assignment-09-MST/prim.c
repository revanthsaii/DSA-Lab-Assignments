prim.c#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX 100
#define INF INT_MAX

// Adjacency matrix representation
int graph[MAX][MAX];
bool visited[MAX];
int key[MAX];
int parent_node[MAX];

int findMinKey(int n) {
  int min = INF;
  int minIndex = -1;
  
  for (int v = 0; v < n; v++) {
    if (!visited[v] && key[v] < min) {
      min = key[v];
      minIndex = v;
    }
  }
  return minIndex;
}

void primMST(int n) {
  // Initialize all keys as infinite
  for (int i = 0; i < n; i++) {
    key[i] = INF;
    visited[i] = false;
    parent_node[i] = -1;
  }

  // Start from vertex 0
  key[0] = 0;

  // Find MST by selecting edges
  for (int count = 0; count < n - 1; count++) {
    // Pick minimum key vertex not yet visited
    int u = findMinKey(n);
    
    if (u == -1) break;
    
    visited[u] = true;

    // Update key values of adjacent vertices
    for (int v = 0; v < n; v++) {
      if (graph[u][v] && !visited[v] && graph[u][v] < key[v]) {
        parent_node[v] = u;
        key[v] = graph[u][v];
      }
    }
  }
}

int main() {
  // Initialize graph
  for (int i = 0; i < MAX; i++) {
    for (int j = 0; j < MAX; j++) {
      graph[i][j] = 0;
    }
  }

  // Add edges (undirected graph)
  graph[0][1] = graph[1][0] = 10;
  graph[0][2] = graph[2][0] = 15;
  graph[1][2] = graph[2][1] = 35;
  graph[1][3] = graph[3][1] = 25;
  graph[2][3] = graph[3][2] = 30;
  graph[3][4] = graph[4][3] = 5;
  graph[2][4] = graph[4][2] = 20;

  int n = 5;
  printf("===== PRIM'S MINIMUM SPANNING TREE =====\n\n");

  primMST(n);

  printf("MST Edges (Prim's Algorithm):\n");
  int totalWeight = 0;
  for (int i = 1; i < n; i++) {
    printf(" Edge (%d,%d): weight = %d\n", parent_node[i], i, key[i]);
    totalWeight += key[i];
  }

  printf("\nMST Summary:\n");
  printf(" Total Weight: %d\n", totalWeight);
  printf(" Number of Edges: %d\n", n - 1);
  printf(" Number of Vertices: %d\n\n", n);

  printf("Time Complexity: O(V^2)\n");
  printf("Space Complexity: O(V)\n");
  printf("Approach: Greedy - Select minimum weight edge at each step\n");

  return 0;
}
