#include "sorting.h"

void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

void bubble_sort(int size, int arr[]) {
  int sorted;

  for (int i = 0; i < size; i++) {
    sorted = 1;
    for (int j = 0; j < (size - 1); j++) {
      if (arr[j] > arr[j + 1]) {
        swap(&arr[j], &arr[j + 1]);
        sorted = 0;
      }
    }
    if (sorted) {
      break;
    }
  }
}
