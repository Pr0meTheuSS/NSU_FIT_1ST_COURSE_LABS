// Copyright 2022 Y.Olimpiev
#include "ConvertBase.h"

void BadInput() {
    printf("bad input\n");
    exit(0);
}

int IsValidSymbol(char symbol) {
  return isdigit(symbol) || isalpha(symbol) || symbol == '.' || symbol == '\0';
}

int IsValidNumberFormat(char* numb_str, int base) {
    if (numb_str[0] == '.' || numb_str[strlen(numb_str) - 1] == '.') {
        return false;
    }
    int point_counter = 0;
    for (size_t i = 0; i < strlen(numb_str); i++) {
      if (!IsValidSymbol(numb_str[i])) {
        return false;
      }
      if (numb_str[i] == '.') {
          point_counter++;
      } else {
        if (CharToInt(numb_str[i]) >= base) {
          return false;
        }
      }
      if (point_counter > 1) {
          return false;
      }
    }
    return true;
}

void ConvertFromBaseToBase(char* numb_str,
                           int fromBase,
                           int toBase,
                           char res[128]) {
  if (!IsValidNumberFormat(numb_str, fromBase)) {
    BadInput();
  }
  TNumber numb = { 0, 0 };
  InitNumber(&numb, numb_str, fromBase);
  ConvertNumberBase(numb, toBase, res);
}

