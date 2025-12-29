#include <stdio.h>
struct Activity { int start, end; };
int compareEnd(const void *a, const void *b) { return ((struct Activity*)a)->end - ((struct Activity*)b)->end; }
int main() { struct Activity a[] = {{1,3},{2,5},{4,7},{6,9},{5,8},{8,10}}; int n = 6; printf("\n===== GREEDY: ACTIVITY SELECTION =====\n"); qsort(a, n, sizeof(struct Activity), compareEnd); printf("Selected Activities:\n"); printf("(%d, %d) ", a[0].start, a[0].end); int lastEnd = a[0].end; for(int i=1;i<n;i++) if(a[i].start >= lastEnd) { printf("(%d, %d) ", a[i].start, a[i].end); lastEnd = a[i].end; } printf("\n"); return 0; }
