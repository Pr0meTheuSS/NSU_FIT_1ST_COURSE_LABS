// Copyright [2022] Y.Olimpiev
#include <stdlib.h>
#include <stdio.h>
#include "ConvertBase.h"

int main(void) {
  int fromBase = 0;
  int toBase = 0;

  if (scanf("%d %d", &fromBase, &toBase) != 2) {
    BadInput();
  }
  if (fromBase < 2 || fromBase > 16 || toBase < 2 || toBase > 16) {
    BadInput();
  }

  char Number[14] = { 0 };
  if (scanf("%13s", Number) != 1) {
    BadInput();
  }

  char res[128] = { 0 };
  ConvertFromBaseToBase(Number, fromBase, toBase, res);
  printf("%s", res);
  return EXIT_SUCCESS;
}

