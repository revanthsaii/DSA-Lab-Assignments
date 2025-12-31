#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Edge structure for Kruskal's algorithm
struct Edge {
  int u, v, weight;
};

// Union-Find (Disjoint Set) data structure
int parent[MAX];
int rank_arr[MAX];

int find(int x) {
  if (parent[x] != x) {
    parent[x] = find(parent[x]);
  }
  return parent[x];
}

void unionSets(int x, int y) {
  int px = find(x);
  int py = find(y);
  
  if (px == py) return;
  
  if (rank_arr[px] < rank_arr[py]) {
    parent[px] = py;
  } else if (rank_arr[px] > rank_arr[py]) {
    parent[py] = px;
  } else {
    parent[py] = px;
    rank_arr[px]++;
  }
}

int compareEdges(const void *a, const void *b) {
  return ((struct Edge *)a)->weight - ((struct Edge *)b)->weight;
}

int main() {
  // Initialize union-find
  for (int i = 0; i < MAX; i++) {
    parent[i] = i;
    rank_arr[i] = 0;
  }

  // Edges: {u, v, weight}
  struct Edge edges[] = {
    {3, 4, 2}, {1, 2, 4}, {2, 3, 5}, {4, 5, 6}, {1, 3, 7}
  };
  int n_edges = 5;
  int n_vertices = 5;

  printf("===== KRUSKAL'S MINIMUM SPANNING TREE =====\n\n");
  printf("Graph Edges (sorted by weight):\n");
  
  // Sort edges by weight
  qsort(edges, n_edges, sizeof(struct Edge), compareEdges);
  for (int i = 0; i < n_edges; i++) {
    printf(" Edge (%d,%d): weight = %d\n", edges[i].u, edges[i].v, edges[i].weight);
  }

  printf("\nMST Edges Selected:\n");
  int total_weight = 0;
  int mst_edges = 0;

  for (int i = 0; i < n_edges && mst_edges < n_vertices - 1; i++) {
    int x = find(edges[i].u);
    int y = find(edges[i].v);

    if (x != y) {
      printf(" Edge (%d,%d): weight = %d\n", edges[i].u, edges[i].v, edges[i].weight);
      unionSets(x, y);
      total_weight += edges[i].weight;
      mst_edges++;
    }
  }

  printf("\nMST Summary:\n");
  printf(" Total Weight: %d\n", total_weight);
  printf(" Number of Edges: %d\n", mst_edges);
  printf(" Number of Vertices: %d\n\n", n_vertices);

  printf("Time Complexity: O(E log E)\n");
  printf("Space Complexity: O(V)\n");
  printf("Approach: Sort edges and use Union-Find\n");

  return 0;
}
