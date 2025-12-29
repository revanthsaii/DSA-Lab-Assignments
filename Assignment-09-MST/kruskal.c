#include <stdio.h>
#include <stdlib.h>
struct Edge { int u,v,w; };
int parent[10];
int find(int x) { if(parent[x]!=x) parent[x]=find(parent[x]); return parent[x]; }
void unite(int x, int y) { x=find(x); y=find(y); if(x!=y) parent[x]=y; }
int compareEdge(const void *a, const void *b) { return ((struct Edge*)a)->w - ((struct Edge*)b)->w; }
int main() { struct Edge edges[] = {{0,1,4},{0,2,2},{1,2,1},{1,3,5},{2,3,8},{2,4,10},{3,4,2}}; int n=7, v=5; printf("\n===== MINIMUM SPANNING TREE (KRUSKAL) =====\n"); qsort(edges,n,sizeof(struct Edge),compareEdge); for(int i=0;i<v;i++) parent[i]=i; int cost=0; printf("MST Edges:\n"); for(int i=0;i<n;i++) { if(find(edges[i].u)!=find(edges[i].v)) { printf("(%d-%d) weight=%d\n",edges[i].u,edges[i].v,edges[i].w); cost+=edges[i].w; unite(edges[i].u,edges[i].v); } } printf("Total Cost: %d\n",cost); return 0; }
