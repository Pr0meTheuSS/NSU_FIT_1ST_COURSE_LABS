#include <stdlib.h>
#include <stdio.h>
#include "ReversedPolishNotation.h"
#define STR_SIZE 1001


void SyntError(void) {
  printf("syntax error");
  exit(0);
}

void DivByZero(void) {
  printf("division by zero");
  exit(0);
}

int main(void) {
  char str[STR_SIZE] = {0};
  if (scanf("%1000[^\n]s", str) != 1) {
    SyntError();
  }
  int result = 0;

  ETokenStatus status = RPNCalc(str, &result);
  if (status == Success) {
    printf("%d", result);
  } else if (status == SyntaxError) {
    SyntError();
  } else if (status == DivisionByZero) {
    DivByZero();
  }

  return EXIT_SUCCESS;
}

