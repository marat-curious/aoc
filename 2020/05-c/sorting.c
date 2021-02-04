#include <math.h>
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

void comb_sort(int size, int arr[]) {
  const float shrink = 1.3;
  int interval = (int)floor(size / shrink);

  while (interval > 0) {
    for (int i = 0; (i + interval) < size; i++) {
      if (arr[i] > arr[i + interval]) {
        swap(&arr[i], &arr[i + interval]);
      }
    }
    interval = (int)floor(interval / shrink);
  }
}
