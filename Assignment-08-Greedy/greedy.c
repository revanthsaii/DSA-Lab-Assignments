#include <stdio.h>
#include <string.h>

#define MAX 100

// Activity structure
struct Activity {
  int start, end;
};

// Comparator function to sort activities by end time
int compareActivity(const void *a, const void *b) {
  return ((struct Activity *)a)->end - ((struct Activity *)b)->end;
}

// Greedy Activity Selection Problem
int activitySelection(struct Activity activities[], int n) {
  // Sort activities by end time
  qsort(activities, n, sizeof(struct Activity), compareActivity);

  printf("Activities in order of end time:\n");
  for (int i = 0; i < n; i++) {
    printf(" Activity %d: [%d - %d]\n", i + 1, activities[i].start, activities[i].end);
  }

  printf("\nSelected Activities (Non-overlapping):\n");
  int count = 0;
  int lastEnd = -1;

  for (int i = 0; i < n; i++) {
    if (activities[i].start >= lastEnd) {
      printf(" Activity [%d - %d]\n", activities[i].start, activities[i].end);
      lastEnd = activities[i].end;
      count++;
    }
  }

  return count;
}

int main() {
  // Activities: {start, end}
  struct Activity activities[] = {
    {1, 3}, {2, 5}, {4, 7}, {6, 9}, {5, 8}, {8, 10}
  };
  int n = sizeof(activities) / sizeof(activities[0]);

  printf("===== GREEDY ACTIVITY SELECTION PROBLEM =====\n\n");
  printf("Total Activities: %d\n\n", n);

  int selected = activitySelection(activities, n);

  printf("\nMaximum Activities Selected: %d\n\n", selected);
  printf("Greedy Approach: Select activity with earliest end time\n");
  printf("Always picks next activity that starts after previous one ends\n\n");

  printf("Time Complexity: O(n log n) - due to sorting\n");
  printf("Space Complexity: O(1) - excluding input array\n");
  printf("Approach: Greedy - Always select activity ending earliest\n");

  return 0;
}
