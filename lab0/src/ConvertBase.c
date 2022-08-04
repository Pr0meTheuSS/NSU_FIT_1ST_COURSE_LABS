#include "ConvertBase.h"

void badInput() {
    printf("bad input\n");
    exit(0);
}

int IsValidNumberFormat(char* numb_str, int base) {
    if (numb_str[0] == '.' || numb_str[strlen(numb_str) - 1] == '.') {
        return false;
    }
    for(size_t i = 0; i < strlen(numb_str); i++) {
      int point_counter = 0;
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


void ConvertFromBaseToBase(char* numb_str, int fromBase, int toBase, char Res[128]) {
  if (!IsValidNumberFormat(numb_str, fromBase)) {
    BadInput();
  }
  TNumber numb = { 0, 0 };
  InitNumber(&numb, numb_str, fromBase);    
  ConvertNumberBase(numb, toBase, &Res[0]);
}
