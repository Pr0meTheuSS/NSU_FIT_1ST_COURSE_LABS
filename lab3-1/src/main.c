#include <stdlib.h>
#include <stdio.h>
#include "QuickSort.h"
#include "Array.h"

int main(void) {
  size_t ArraySize = 0;

  if (scanf("%zu", &ArraySize) != 1) {
    printf("\n[STATUS]:\tError\n[MODULE]\tmain, func scanf()\n[PROBLEM]:\twrong number of entered fields\n");
    exit(0);
  }

  TArray Array = {NULL, 0};
  InitArray(&Array, ArraySize);

  ReadArrayIntFromConsole(Array);
  QuickSort(Array);
  PrintArrayIntToConsole(Array);

  ClearArray(&Array);

  return EXIT_SUCCESS;
}

