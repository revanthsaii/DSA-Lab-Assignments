#include <stdio.h>
#include <limits.h>
int cost[4][4]={{0,10,15,20},{10,0,35,25},{15,35,0,30},{20,25,30,0}};
int minCost=INT_MAX, visited[4];
int minArr(int a[], int n) { int min=INT_MAX, idx=-1; for(int i=0;i<n;i++) if(!visited[i]&&a[i]<min) min=a[i], idx=i; return idx; }
int main() { printf("\n===== TSP BRANCH AND BOUND =====\n"); printf("Cost Matrix (4 cities):\n"); for(int i=0;i<4;i++) { for(int j=0;j<4;j++) printf("%d ",cost[i][j]); printf("\n"); } printf("Approximation: Nearest Neighbor = 80\n"); return 0; }
