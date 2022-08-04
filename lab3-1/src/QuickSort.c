#include "QuickSort.h"


void swap(int* a, int* b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}


void QuickSort(TArray array) {
  QuickSortInt(array.Array, array.Size);
}

void QuickSortInt(int* array, size_t size) {
  if (size <= 1) {
    return;
  }

  if (size == 2) {
    if (array[0] > array[1]) {
      swap(&array[0], &array[1]);
    }
    return;
  }

  size_t pivot_index = size/2;

  for (size_t i = 0; i < pivot_index; ++i) {
    if (array[i] > array[pivot_index]) {
      // Swap left naighbour of pivot element with bigger element
      swap(&array[pivot_index - 1], &array[i]);
      // Swap pivot element with bigger
      swap(&array[pivot_index], &array[pivot_index - 1]);
      pivot_index--;
      i--;
    }
  }

  for (size_t i = pivot_index + 1; i < size; ++i) {
    if (array[i] < array[pivot_index]) {
      // Swap right naighbour of pivot element with smaller element
      swap(&array[pivot_index + 1], &array[i]);
      // Swap pivot element with smallee
      swap(&array[pivot_index], &array[pivot_index + 1]);
      pivot_index++;
      i--;
    }
  }

  // Sort left half
  QuickSortInt(array, pivot_index + 1);
  // Sort right half
  QuickSortInt(&array[pivot_index + 1], size - (pivot_index + 1));
}

