#include <stdlib.h>
#include <stdio.h>
#include "BoyerMooreProtocol.h"

int main(void) {
  unsigned char template[TEMPLATE_MAX_LEN] = { 0 };
  int currSymbol = 0;
  size_t currPosInTemplate = 0;

  FILE* in = fopen("in.txt", "rb");
  assert(in);
  while ((currSymbol = getc(in)) != '\n' && currSymbol != '\r') {
    template[currPosInTemplate] = currSymbol;
    currPosInTemplate++;
    if (currPosInTemplate >= TEMPLATE_MAX_LEN) {
      perror("Bad input");
      return EXIT_SUCCESS;
    }
  }
  template[currPosInTemplate] = '\0';

  BoyerMooreProtocol(in, template);
  fclose(in);

  return EXIT_SUCCESS;
}
