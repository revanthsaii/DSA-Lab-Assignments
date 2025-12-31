#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define V 6
#define MAX_COLORS 4

int graph[V][V] = {
    {0, 1, 1, 0, 0, 0},
    {1, 0, 1, 1, 0, 0},
    {1, 1, 0, 1, 0, 0},
    {0, 1, 1, 0, 1, 1},
    {0, 0, 0, 1, 0, 1},
    {0, 0, 0, 1, 1, 0}
};

int color[V];
int nodesExplored = 0;
int nodesPruned = 0;
int minColors = MAX_COLORS;
int bestColoring[V];

bool isSafe(int vertex, int c) {
    for (int i = 0; i < V; i++) {
        if (graph[vertex][i] && color[i] == c) {
            return 0;
        }
    }
    return 1;
}

void colorGraph(int vertex, int numColors) {
    nodesExplored++;
    
    // Pruning: if using more colors than best found, stop
    if (numColors >= minColors) {
        nodesPruned++;
        return;
    }
    
    // All vertices colored
    if (vertex == V) {
        if (numColors < minColors) {
            minColors = numColors;
            for (int i = 0; i < V; i++) {
                bestColoring[i] = color[i];
            }
        }
        return;
    }
    
    // Try assigning colors to current vertex
    for (int c = 0; c < numColors; c++) {
        if (isSafe(vertex, c)) {
            color[vertex] = c;
            colorGraph(vertex + 1, numColors);
            color[vertex] = -1;
        }
    }
    
    // Try adding a new color
    if (numColors < MAX_COLORS) {
        color[vertex] = numColors;
        colorGraph(vertex + 1, numColors + 1);
        color[vertex] = -1;
    }
}

int main() {
    printf("===== GRAPH COLORING - BRANCH AND BOUND =====\n\n");
    
    printf("Graph:\n");
    printf(" 0 -- 1 -- 2\n");
    printf(" | X |  /\n");
    printf(" 3 -- 4 -- 5\n\n");
    
    // Initialize
    for (int i = 0; i < V; i++) {
        color[i] = -1;
        bestColoring[i] = -1;
    }
    
    printf("Finding minimum colors needed...\n\n");
    color[0] = 0;
    colorGraph(1, 1);
    
    printf("Chromatic Number: %d\n", minColors);
    printf("\nOptimal Coloring:\n");
    
    // Group vertices by color
    for (int c = 0; c < minColors; c++) {
        printf("Color %d: Vertices {", c + 1);
        int first = 1;
        for (int i = 0; i < V; i++) {
            if (bestColoring[i] == c) {
                if (!first) printf(", ");
                printf("%d", i);
                first = 0;
            }
        }
        printf("}\n");
    }
    
    printf("\nNodes Explored: %d\n", nodesExplored);
    printf("Nodes Pruned: %d\n", nodesPruned);
    printf("\nTime Complexity: O(k^n) where k=number of colors\n");
    printf("Space Complexity: O(n)\n");
    
    return 0;
}
