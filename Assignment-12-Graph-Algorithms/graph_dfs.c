#include <stdio.h>
int visited[5]={0};
void dfs(int adj[5][5], int v) { visited[v]=1; printf("%d ",v); for(int i=0;i<5;i++) if(adj[v][i]&&!visited[i]) dfs(adj,i); }
int main() { int adj[5][5]={{0,1,1,0,0},{1,0,1,1,0},{1,1,0,1,1},{0,1,1,0,1},{0,0,1,1,0}}; printf("\n===== GRAPH DFS =====\n"); printf("DFS Traversal: "); dfs(adj,0); printf("\n"); return 0; }
