// "Copyright 2022 <Olimpiev Y.>"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Zip.h"

int main(void) {
  FILE* in = fopen("in.txt", "rb");
  assert(in);
  FILE* out = fopen("out.txt", "wb");
  assert(in);

  unsigned char mode = 0;
  if (fscanf(in, "%c", &mode) != 1) {
    fclose(in);
    fclose(out);
    return EXIT_SUCCESS;
  }
  int retCode = Zip(in, out, mode);
  fclose(in);
  fclose(out);
  return retCode;
}
