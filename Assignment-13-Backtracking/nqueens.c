#include <stdio.h>
int board[4][4];
int isSafe(int r, int c) { for(int i=0;i<r;i++) if(board[i][c]) return 0; for(int i=r,j=c;i>=0&&j>=0;i--,j--) if(board[i][j]) return 0; for(int i=r,j=c;i>=0&&j<4;i--,j++) if(board[i][j]) return 0; return 1; }
void solve(int r) { if(r==4) { printf("Solution found\n"); return; } for(int c=0;c<4;c++) if(isSafe(r,c)) { board[r][c]=1; solve(r+1); board[r][c]=0; } }
int main() { printf("\n===== 4 QUEENS PROBLEM =====\n"); solve(0); return 0; }
