#include <stdio.h>
void merge(int a[], int l, int m, int r) {
    int i=l, j=m+1, k=0, b[100];
    while(i<=m && j<=r) b[k++] = a[i]<=a[j] ? a[i++] : a[j++];
    while(i<=m) b[k++] = a[i++];
    while(j<=r) b[k++] = a[j++];
    for(i=l, k=0; i<=r; i++, k++) a[i] = b[k];
}
void mergeSort(int a[], int l, int r) {
    if(l < r) {
        int m = (l+r)/2;
        mergeSort(a, l, m);
        mergeSort(a, m+1, r);
        merge(a, l, m, r);
    }
}
int main() {
    int a[] = {38, 27, 43, 3, 9, 82, 10};
    int n = 7;
    printf("\n===== MERGE SORT =====\n");
    printf("Before: ");
    for(int i=0; i<n; i++) printf("%d ", a[i]);
    mergeSort(a, 0, n-1);
    printf("\nAfter: ");
    for(int i=0; i<n; i++) printf("%d ", a[i]);
    printf("\n");
    return 0;
}
