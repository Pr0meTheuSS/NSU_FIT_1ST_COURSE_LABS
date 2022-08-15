#include "BoyerMooreProtocol.h"

#define _RELEASE
//#define _DEBUG

void BoyerMooreProtocol(FILE* in, unsigned char template[TEMPLATE_MAX_LEN]) {
  size_t templateLen = strlen(template);
  #ifdef _DEBUG
    printf("Template len: %zu\n", templateLen);
  #endif
  size_t offsetTable[256] = { 0 };
  for (size_t i = 0; i < ALPHABET_SIZE; i++) {
    offsetTable[i] = templateLen;
  }

//  memset(offsetTable, templateLen, 256);

  for (size_t i = 1; i < templateLen; i++) {
    unsigned char currSymb = template[templateLen - 1 - i];
      if (offsetTable[currSymb] > i) {
        offsetTable[currSymb] = i;
    }
  }

  size_t currPosInTemplate = templateLen - 1;
  size_t currPosInText = ftell(in) + templateLen;
  size_t matchesAmount = 0;

  int currSymbol = 0;
  fseek(in, currPosInText, SEEK_SET);

  while ((currSymbol = getc(in)) != EOF) {
    currSymbol = (unsigned int)currSymbol;
    #ifdef _DEBUG
      printf("Text curr symbol: %c Template curr symbol: %c Pos: %zu\n", currSymbol, template[currPosInTemplate], 1 + currPosInText);
    #endif
    #ifdef _RELEASE
      printf("%zu ", currPosInText - templateLen - 1);
    #endif
    if (currSymbol == template[currPosInTemplate]) {
      if (currPosInTemplate <= 0) {
        currPosInTemplate = templateLen - 1;
        currPosInText += offsetTable[template[currPosInTemplate]] + matchesAmount;
        matchesAmount = 0;
    } else {
      currPosInTemplate--;
      currPosInText--;
      matchesAmount++;
      }
    } else {
      size_t offset = offsetTable[currSymbol];
      #ifdef _DEBUG
        printf("Offset for: %c  -  %d\n", currSymbol, offset);
      #endif
      if (matchesAmount) {
        offset = offsetTable[template[templateLen - 1]] + matchesAmount;
      }
      currPosInText += offset;
      matchesAmount = 0;
      currPosInTemplate = templateLen - 1;
    }
    fseek(in, currPosInText, SEEK_SET);
  }
}
