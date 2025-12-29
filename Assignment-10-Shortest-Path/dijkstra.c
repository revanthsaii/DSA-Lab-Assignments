#include <stdio.h>
#include <limits.h>
int minDist(int dist[], int visited[], int n) { int min=INT_MAX, idx=-1; for(int i=0;i<n;i++) if(!visited[i]&&dist[i]<min) min=dist[i], idx=i; return idx; }
int main() { int n=5; int graph[5][5]={{0,4,INT_MAX,2,INT_MAX},{4,0,INT_MAX,1,5},{INT_MAX,INT_MAX,0,3,2},{2,1,3,0,INT_MAX},{INT_MAX,5,2,INT_MAX,0}}; int dist[5], visited[5]={0}; printf("\n===== DIJKSTRA'S SHORTEST PATH =====\n"); for(int i=0;i<n;i++) dist[i]=graph[0][i]; visited[0]=1; for(int i=1;i<n;i++) { int u=minDist(dist,visited,n); visited[u]=1; for(int v=0;v<n;v++) if(dist[u]+graph[u][v]<dist[v]) dist[v]=dist[u]+graph[u][v]; } for(int i=0;i<n;i++) printf("Distance to %d: %d\n",i,dist[i]); return 0; }
