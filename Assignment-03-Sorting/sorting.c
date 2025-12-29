#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) { int t = *a; *a = *b; *b = t; }

void bubbleSort(int arr[], int n) {
    for(int i = 0; i < n-1; i++)
        for(int j = 0; j < n-i-1; j++)
            if(arr[j] > arr[j+1]) swap(&arr[j], &arr[j+1]);
}

void selectionSort(int arr[], int n) {
    for(int i = 0; i < n-1; i++) {
        int min = i;
        for(int j = i+1; j < n; j++)
            if(arr[j] < arr[min]) min = j;
        swap(&arr[i], &arr[min]);
    }
}

void insertionSort(int arr[], int n) {
    for(int i = 1; i < n; i++) {
        int key = arr[i], j = i-1;
        while(j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = 7;
    printf("\n===== SORTING ALGORITHMS =====\n");
    printf("Original: ");
    for(int i = 0; i < n; i++) printf("%d ", arr[i]);
    
    int arr2[7], arr3[7];
    for(int i = 0; i < n; i++) arr2[i] = arr3[i] = arr[i];
    
    bubbleSort(arr, n);
    printf("\nBubble Sort: ");
    for(int i = 0; i < n; i++) printf("%d ", arr[i]);
    
    selectionSort(arr2, n);
    printf("\nSelection Sort: ");
    for(int i = 0; i < n; i++) printf("%d ", arr2[i]);
    
    insertionSort(arr3, n);
    printf("\nInsertion Sort: ");
    for(int i = 0; i < n; i++) printf("%d ", arr3[i]);
    printf("\n");
    return 0;
}
